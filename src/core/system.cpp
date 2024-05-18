#include "system.hpp"
#include <iostream>
#include "thread_pool.hpp"

void System::render() {
    ThreadPool pool(scene.numThreads, scene.raysPerPixel * renderTarget.width * renderTarget.height);
    std::cout << "Preprocess done, starting to render" << std::endl;
    timer.reset();
    for (int rayIter = 0; rayIter < scene.raysPerPixel; rayIter++) {
        for (int row = 0; row < renderTarget.height; row++) {
            for (int col = 0; col < renderTarget.width; col++) {
                Job j;
                j.row = row;
                j.col = col;
                j.system = this;
                j.rayIter = rayIter;
                pool.addJob(j);
            }
        }
    }
    pool.waitAll();
    pool.stopPool();
    std::cout << "Render took " + std::to_string(timer.getElapsedTime()) + " ms" << std::endl;
}
