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
}

void ThreadPool::processJob(Job job) {
    
}
