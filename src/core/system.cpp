#include "system.hpp"
#include <iostream>

System::System(Timer& timer, PerspectiveCam& cam, Texture& renderTarget, Vector3 lightLoc) : timer(timer), cam(cam), renderTarget(renderTarget) {
    this->lightLoc = lightLoc;
}

void System::render() {
    timer.reset();
    for (int row = 0; row < renderTarget.height; row++) {
        for (int col = 0; col < renderTarget.width; col++) {
            // fill in color of this pixel by shooting ray into scene
            float imgPlaneX = (col - renderTarget.width / 2.0f) / (renderTarget.height / 2.0f);
            float imgPlaneY = -(row - renderTarget.height / 2.0f) / (renderTarget.height / 2.0f);
            Ray r = cam.generateRay(imgPlaneX, imgPlaneY);
            float minT = -1.0f;
            for (TriMesh* mesh : meshes) {
                for (Triangle& triangle : (*mesh).triangles) {
                    float t = triangle.intersect(r);
                    if (t == -1.0f) continue;
                    if (minT == -1.0f || t < minT) {
                        // new nearest hit
                        minT = t;
                        Vector3 hitPt = r(t);
                        // diffuse shading
                        Vector3 l = (lightLoc - hitPt).normalize();
                        float diffuse = std::max(0.0f, dot(triangle.getNormal(), l));
                        Vector3 white(1.0f, 1.0f, 1.0f);
                        Color c((diffuse * white + white) / 2.0);
                        c.clamp();
                        renderTarget.setColor(c, row, col);
                    }
                }
            }
        }
    }
    std::cout << "Render took " + std::to_string(timer.getElapsedTime()) + " ms" << std::endl;
}

void System::addTriMesh(TriMesh* mesh) {
    meshes.push_back(mesh);
}
