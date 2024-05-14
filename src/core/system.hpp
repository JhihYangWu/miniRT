#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "../camera/perspective.hpp"
#include "../texture/texture.hpp"
#include "../geometry/trimesh.hpp"
#include "timer.hpp"

class System{
public:
    // constructor
    System(int numThreads, Timer& timer, PerspectiveCam& cam, Texture& renderTarget, Vector3 lightLoc);

    // methods
    void render(); // render the scene using ray tracing and put it in renderTarget
    void addTriMesh(TriMesh* mesh);

    // attributes
    int numThreads;
    Timer& timer;
    PerspectiveCam& cam;
    Texture& renderTarget;
    std::vector<TriMesh*> meshes;
    Vector3 lightLoc;
};

struct Job {
    int row;
    int col;
    System* system;
};

#endif
