#include "thread_pool.hpp"
#include "rendering_equation.hpp"

ThreadPool::ThreadPool(int numThreads, int numJobs) {
    stop = false;
    jobsCompleted = 0;
    totalJobs = numJobs;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back([this] {
            // code that each thread runs
            while (true) {
                Job job;
                { // get job
                    std::unique_lock<std::mutex> lock(queueMutex); // get lock for queueMutex
                    condition.wait(lock, [this] { return stop || !jobs.empty(); }); // wait for new job condition
                    if (stop && jobs.empty()) return;
                    job = jobs.front();
                    jobs.pop();
                } // automatically unlock queueMutex
                processJob(job); // process the job
                { // record down that you finished a job
                    std::lock_guard<std::mutex> lock(completionMutex); // lock completionMutex
                    jobsCompleted++;
                    if (jobsCompleted % 1000 == 0) printProgressBar(jobsCompleted, totalJobs);
                } // automatically unlock completionMutex
                completionCondition.notify_one(); // notify anything waiting on completionCondition
            }
        });
    }
}

void ThreadPool::addJob(Job job) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        jobs.push(job);
    }
    condition.notify_one(); // notify a thread to start working
}

void ThreadPool::waitAll() {
    std::unique_lock<std::mutex> lock(completionMutex);
    completionCondition.wait(lock, [this] { return jobsCompleted == totalJobs; });
}

void ThreadPool::stopPool() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& thread : threads) {
        thread.join();
    }
    std::cout << std::endl;
}

void ThreadPool::processJob(Job job) {
    // fill in color of this pixel by shooting ray into scene
    int row = job.row;
    int col = job.col;
    System* s = job.system;
    float imgPlaneX = (col - s->renderTarget.width / 2.0f) / (s->renderTarget.height / 2.0f);
    float imgPlaneY = -(row - s->renderTarget.height / 2.0f) / (s->renderTarget.height / 2.0f);
    Ray r = s->cam.generateRay(imgPlaneX, imgPlaneY); // primary ray
    Vector3 hitPt;
    Color hitColor;
    Vector3 hitNormal;
    float t = traceRay(r, &hitPt, &hitColor, &hitNormal, s->scene);
    if (t == -1.0f) return; // primary ray hit nothing so black
    BlinnPhongBRDF hitBRDF;
    Vector3 unmappedColor = renderingEq(s->cam.loc, s->scene.pathTracingDepth, s->scene, hitPt, hitColor, hitNormal, hitBRDF);

    // store unmappedColor in buffer
    double* addr = s->scene.renderTargetBuffer + (row * s->scene.renderTarget->width + col) * 3;
    double frac = 1.0 * job.rayIter / (job.rayIter + 1);
    addr[0] *= frac;
    addr[1] *= frac;
    addr[2] *= frac;
    addr[0] += unmappedColor[0] * (1 - frac);
    addr[1] += unmappedColor[1] * (1 - frac);
    addr[2] += unmappedColor[2] * (1 - frac);

    // store color in texture/renderTarget at last iter
    if (job.rayIter == s->scene.raysPerPixel - 1) {
        Vector3 tmp(addr[0], addr[1], addr[2]);
        Color c(tmp);
        c.clamp();
        s->renderTarget.setColor(c, row, col);
    }
}

void printProgressBar(int progress, int total, int barWidth) {
    float percent = 1.0 * progress / total;
    int width = percent * barWidth;
    std::cout << "[";
    for (int i = 0; i < barWidth; i++) {
        if (i < width) std::cout << "=";
        else std::cout << " ";
    }
    std::cout << "] " << int(percent * 100.0f) << "%\r";
    std::cout.flush();
}
