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
    ThreadPool(int numThreads, long long numJobs);

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
    long long jobsCompleted;
    long long totalJobs;
    bool stop;
};

void printProgressBar(long long progress, long long total, int barWidth = 40);

#endif
