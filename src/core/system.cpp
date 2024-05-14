#include "system.hpp"
#include <iostream>
#include "thread_pool.hpp"

System::System(int numThreads, Timer& timer, PerspectiveCam& cam, Texture& renderTarget, Vector3 lightLoc) : timer(timer), cam(cam), renderTarget(renderTarget) {
    this->lightLoc = lightLoc;
    this->numThreads = numThreads;
}

void System::render() {
    ThreadPool pool(numThreads, renderTarget.width * renderTarget.height);
    timer.reset();
    for (int row = 0; row < renderTarget.height; row++) {
        for (int col = 0; col < renderTarget.width; col++) {
            Job j;
            j.row = row;
            j.col = col;
            j.system = this;
            pool.addJob(j);
        }
    }
    pool.waitAll();
    pool.stopPool();
    std::cout << "Render took " + std::to_string(timer.getElapsedTime()) + " ms" << std::endl;
}

void System::addTriMesh(TriMesh* mesh) {
    meshes.push_back(mesh);
}
