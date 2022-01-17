#pragma once

#include <deque>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>

class FunctionPool
{
    friend class ThreadPool;

private:
    using Functor = std::function<void()>;
    using Locker = std::unique_lock<std::mutex>;

public:
    FunctionPool();

    void push(Functor func);
    void stopListner();
    void startListner();
    void endListner();
    void generateListner();

private:
    std::deque<Functor> functionsQueue;
    std::mutex globalLocker;
    std::condition_variable listner;
    std::atomic<bool> listnerEnded;
    std::atomic<bool> listnerStopped;
};