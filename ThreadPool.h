#ifndef THREADPOOL
#define THREADPOOL

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <future>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "Task.h"

class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount = std::thread::hardware_concurrency());
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 将模板函数定义放在头文件
    template <typename Func, typename... Args>
    auto enqueue(Func&& func, Args&&... args) -> std::future<decltype(func(args...))>;

    void resize(size_t newSize);

private:
    void worker();
    void stop();

    std::vector<std::thread> workers;                      // 工作线程
    std::queue<std::function<void()>> tasks;               // 任务队列
    std::mutex queueMutex;                                 // 任务队列的互斥锁
    std::condition_variable condition;                     // 条件变量用于线程间通信
    std::atomic<bool> isRunning;                           // 线程池运行标志
    std::atomic<size_t> activeThreads;                     // 当前活跃线程数
};


template <typename Func, typename... Args>
auto ThreadPool::enqueue(Func&& func, Args&&... args) -> std::future<decltype(func(args...))> {
    using ReturnType = decltype(func(args...)); // 推断返回值类型

    // 创建一个 packaged_task，用于包装任务
    auto task = std::make_shared<std::packaged_task<ReturnType()>>(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
    );

    std::future<ReturnType> result = task->get_future();
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!isRunning) {
            throw std::runtime_error("线程池已停止，无法添加新任务！");
        }
        // 将任务包装为 std::function 并添加到任务队列
        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one(); // 唤醒一个线程处理任务
    return result;
}

#endif
