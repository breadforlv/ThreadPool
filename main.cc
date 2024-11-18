#include "ThreadPool.h"
#include "Logger.h"
#include "ConcurrentThread.h"
#include <iostream>
#include <vector>
#include <memory>

int main() {
    // 创建线程池，假设线程池大小为4
    ThreadPool pool(4);
    
    // 创建Logger实例，用于记录日志
    Logger logger;
    
    // 模拟任务，创建10个ConcurrentThread任务
    std::vector<std::future<void>> results;

    for (int i = 0; i < 10; ++i) {
        // 提交任务给线程池执行
        results.push_back(pool.enqueue([i, &logger]() {
            logger.log("Task " + std::to_string(i) + " is starting.");
            ConcurrentThread task(i);
            task();  // 执行任务
            logger.log("Task " + std::to_string(i) + " has finished.");
        }));
    }

    // 等待所有任务完成
    for (auto& result : results) {
        result.get();
    }

    return 0;
}
