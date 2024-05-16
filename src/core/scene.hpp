#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include "../camera/perspective.hpp"
#include "../texture/texture.hpp"
#include "../geometry/trimesh.hpp"
#include "../geometry/plane.hpp"
#include "../geometry/sphere.hpp"

class Scene{
public:
    // constructor
    Scene(std::string filename); // loads .scene file
    ~Scene(); // deconstructor
    // attributes
    int numThreads;
    int pathTracingDepth;
    int raysPerPixel;
    int snapshotFreq;
    PerspectiveCam* cam;
    Texture* renderTarget;
    double* renderTargetBuffer;
    std::vector<TriMesh*> objs; // obj files
    std::vector<Plane> planes;
    std::vector<Sphere> spheres;
};

#endif
