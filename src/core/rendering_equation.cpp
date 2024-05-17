#include "rendering_equation.hpp"
#include <iostream>
#include <cmath>
#include <random>

#define EPSILON_RAY_OFFSET 0.001

Vector3 renderingEq(Vector3 prevPoint, int maxDepth, Scene& scene, Vector3 hitPt, Color hitColor, Vector3 hitNormal, BRDF& hitBRDF) {
    // Intro to Graphics 17 - The Rendering Equation https://www.youtube.com/watch?v=GOfzX7kRwys
    // How Ray Tracing (Modern CGI) Works And How To Do It 600x Faster https://www.youtube.com/watch?v=gsZiJeaMO48
    Vector3 wo = (prevPoint - hitPt).normalize();
    Vector3 wi = randomHemisphereDirection(hitNormal);
    float cosThetaI = dot(wi, hitNormal);
    
    if (hitColor.luminance != 0.0f) {
        // hit light source, stop recursing
        return hitColor.luminance * Vector3(hitColor.r, hitColor.g, hitColor.b);
    } else if (maxDepth <= 0) {
        // can't recurse anymore and didn't hit light source so no color
        return Vector3(); // black
    } else {
        if (hitColor.isMirror) {
            // special case for mirrors
            // don't just shoot ray in random direction, shoot in reflected direction
            wi = -wo + 2 * dot(wo, hitNormal) * hitNormal; // reflection formula
        } else if (hitColor.a < 1.0f) {
            // special case for semi-transparent surfaces
            // don't just shoot ray in random direction, shoot ray in refracted direction or reflected direction
            // TODO: randomly choose between refracted and reflected using Fresnel equations
            bool refracted = true;
            bool insideObject = dot(wo, hitNormal) < 0.0f;
            if (insideObject) hitNormal = -hitNormal; // normal always similar direction to wo easier to think about
            if (refracted) { // refraction
                float n1; // incident index
                float n2; // refracted index
                if (insideObject) {
                    n1 = hitColor.refractiveIndex; // from inside object
                    n2 = 1.0; // back to air
                } else {
                    n1 = 1.0; // from air
                    n2 = hitColor.refractiveIndex; // to inside object
                }
                float cosIncidentAng = dot(wo, hitNormal);
                float sinIncidentAng = sqrtf(1 - cosIncidentAng * cosIncidentAng); // pythagorean identity
                float sinRefractedAng = n1 / n2 * sinIncidentAng;
                if (sinRefractedAng > 1.0f) { // total internal reflection
                    wi = -wo + 2 * dot(wo, hitNormal) * hitNormal; // reflection formula
                } else {
                    // calculate refracted wi
                    float cosRefractedAng = sqrtf(1 - sinRefractedAng * sinRefractedAng); // pythagorean identity
                    Vector3 wiParallel = n1 / n2 *(-wo + cosIncidentAng * hitNormal); // cosIncidentAng * hitNormal = dot(wo, normal) * normal = projection of wo on normal
                    // wiParallel is parallel to the surface
                    Vector3 wiPerp = -cosRefractedAng * hitNormal; // dot(wi, -normal) * -normal = projection of wi on -normal
                    // wiPerp is perp to the surface
                    wi = (wiParallel + wiPerp).normalize();
                }
            } else { // reflection
                wi = -wo + 2 * dot(wo, hitNormal) * hitNormal; // reflection formula
            }
        }
        // recurse by shooting a ray (path tracing)
        // trace ray in wi direction
        Ray nextRay(hitPt + wi * EPSILON_RAY_OFFSET, wi); // create a ray that moves slightly in wi direction to not intersect with shape at hitPt
        Vector3 nextHitPt;
        Color nextHitColor;
        Vector3 nextHitNormal;
        float t = traceRay(nextRay, &nextHitPt, &nextHitColor, &nextHitNormal, scene);
        if (t == -1.0f) return Vector3(); // didn't hit anything so black
        Vector3 thisColor(hitColor.r, hitColor.g, hitColor.b);
        if (hitColor.isMirror) return thisColor * renderingEq(hitPt, maxDepth - 1, scene, nextHitPt, nextHitColor, nextHitNormal, hitBRDF);
        if (hitColor.a < 1.0f) return thisColor * renderingEq(hitPt, maxDepth - 1, scene, nextHitPt, nextHitColor, nextHitNormal, hitBRDF);
        return thisColor * renderingEq(hitPt, maxDepth - 1, scene, nextHitPt, nextHitColor, nextHitNormal, hitBRDF) * cosThetaI * hitBRDF.reflectance(wi, wo, hitNormal);
    }
}

float randomFloat() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0f, 1.0f);
    return dis(gen);
}

Vector3 randomHemisphereDirection(Vector3 normal) {
    // just generate a random unit vector and flip if in wrong hemisphere
    float phi = 2 * M_PI * randomFloat();
    float cosTheta = 2 * randomFloat() - 1;
    float sinTheta = std::sqrt(1 - cosTheta * cosTheta);
    
    Vector3 randomVector = Vector3(
        sinTheta * std::cos(phi),
        sinTheta * std::sin(phi),
        cosTheta
    );

    if (dot(randomVector, normal) < 0.0f) {
        // opposite hemisphere so flip
        randomVector = -randomVector;
    }
    return randomVector.normalize();
}

float traceRay(Ray r, Vector3* hitPt, Color* hitColor, Vector3* hitNormal, Scene& scene) {
    float minT = -1.0f;
    for (TriMesh* mesh : scene.objs) { // intersect with all meshes
        Triangle* hitTrig;
        float t = mesh->octree->intersect(r, &hitTrig);
        if (t == -1.0f) continue;
        if (minT == -1.0f || t < minT) {
            // new nearest hit
            minT = t;
            *hitPt = r(t);
            *hitColor = hitTrig->c;
            *hitNormal = hitTrig->n;
        }
    }
    for (Plane& p : scene.planes) { // intersect with all planes
        float t = p.intersect(r);
        if (t == -1.0f) continue;
        if (minT == -1.0f || t < minT) {
            // new nearest hit
            minT = t;
            *hitPt = r(t);
            *hitColor = p.c;
            *hitNormal = p.n;
        }
    }
    for (Sphere& sphere : scene.spheres) { // intersect with all spheres
        float t = sphere.intersect(r);
        if (t == -1.0f) continue;
        if (minT == -1.0f || t < minT) {
            // new nearest hit
            minT = t;
            *hitPt = r(t);
            *hitColor = sphere.c;
            *hitNormal = sphere.getNormal(*hitPt);
        }
    }
    return minT;
}
