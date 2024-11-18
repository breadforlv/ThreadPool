#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(size_t threadCount) 
    : isRunning(true), activeThreads(0) {
    resize(threadCount);
}

ThreadPool::~ThreadPool() {
    stop();
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::resize(size_t newSize) {
    size_t currentSize = workers.size();

    if (newSize > currentSize) {
        // 增加线程
        for (size_t i = 0; i < newSize - currentSize; ++i) {
            workers.emplace_back([this] { worker(); });
        }
    } else if (newSize < currentSize) {
        // 减少线程
        stop();
        workers.resize(newSize);
    }
}

void ThreadPool::stop() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        isRunning = false;
    }
    condition.notify_all();
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return !isRunning || !tasks.empty(); });

            if (!isRunning && tasks.empty()) {
                return; // 退出线程
            }

            task = std::move(tasks.front());
            tasks.pop();
        }

        if (task) {
            activeThreads.fetch_add(1);
            task();
            activeThreads.fetch_sub(1);
        }
    }
}
