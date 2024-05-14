#include "thread_pool.hpp"

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
    Ray r = s->cam.generateRay(imgPlaneX, imgPlaneY);
    float minT = -1.0f;
    for (TriMesh* mesh : s->meshes) {
        Triangle* hitTrig;
        float t = mesh->octree->intersect(r, &hitTrig);
        if (t == -1.0f) continue;
        if (minT == -1.0f || t < minT) {
            // new nearest hit
            minT = t;
            Vector3 hitPt = r(t);
            // diffuse shading
            Vector3 l = (s->lightLoc - hitPt).normalize();
            float diffuse = std::max(0.0f, dot(hitTrig->n, l));
            Vector3 white(1.0f, 1.0f, 1.0f);
            Color c((diffuse * white + white) / 2.0);
            c.clamp();
            s->renderTarget.setColor(c, row, col);
        }
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
