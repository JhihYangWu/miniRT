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
    System(Timer& timer, PerspectiveCam& cam, Texture& renderTarget, Vector3 lightLoc);

    // methods
    void render(); // render the scene using ray tracing and put it in renderTarget
    void addTriMesh(TriMesh* mesh);

    // attributes
    Timer& timer;
    PerspectiveCam& cam;
    Texture& renderTarget;
    std::vector<TriMesh*> meshes;
    Vector3 lightLoc;
};

#endif
