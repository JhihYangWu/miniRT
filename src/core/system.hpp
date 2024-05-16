#ifndef SYSTEM_H
#define SYSTEM_H

#include "scene.hpp"
#include "timer.hpp"

class System{
public:
    // constructor
    System(Scene& scene) : cam(*scene.cam), renderTarget(*scene.renderTarget), scene(scene) {}

    // methods
    void render(); // render the scene using ray tracing and put it in renderTarget

    // attributes
    Timer timer;
    PerspectiveCam& cam; // from scene obj
    Texture& renderTarget; // from scene obj
    Scene& scene;
};

struct Job {
    int row;
    int col;
    System* system;
    int rayIter;
};

#endif
