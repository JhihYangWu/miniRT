#include "system.hpp"
#include <iostream>
#include "thread_pool.hpp"

void System::render() {
    ThreadPool pool(scene.numThreads, renderTarget.width * renderTarget.height);
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
