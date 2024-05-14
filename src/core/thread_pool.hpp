#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "system.hpp"

class ThreadPool{
public:
    // constructor
    ThreadPool(int numThreads, int numJobs);

    // methods
    void addJob(Job job); // add a job to the queue
    void waitAll(); // wait/block until all jobs to complete
    void stopPool(); // stop the thread pool
private:
    void processJob(Job job);

    // attributes
    std::vector<std::thread> threads;
    std::queue<Job> jobs;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::mutex completionMutex;
    std::condition_variable completionCondition;
    int jobsCompleted;
    int totalJobs;
    bool stop;
};

#endif
