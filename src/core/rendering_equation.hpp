#ifndef RENDERING_EQUATION_H
#define RENDERING_EQUATION_H

#include "../color/color.hpp"
#include "scene.hpp"
#include "../color/brdf.hpp"

// main rendering equation
Vector3 renderingEq(Vector3 prevPoint, int maxDepth, Scene& scene, Vector3 hitPt, Color hitColor, Vector3 hitNormal, BRDF& hitBRDF);

// helper functions
float randomFloat();
Vector3 randomHemisphereDirection(Vector3 normal); // returns a random vector in the hemisphere that normal is pointing in
float traceRay(Ray r, // in params
               Vector3* hitPt, Color* hitColor, Vector3* hitNormal, // out params
               Scene& scene); // figures out what ray r hits (if anything)
                              // returns time of intersection

#endif
