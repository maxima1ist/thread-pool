#pragma once

#include <deque>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>

using std::deque;
using std::mutex;
using std::atomic;
using std::condition_variable;

class FunctionPool
{
    friend class ThreadPool;
private:
    using Functor = std::function<void()>;
    using Locker = std::unique_lock<mutex>;
public:
    FunctionPool();

    void push(Functor func);
    void stopListner();
    void startListner();
    void endListner();
    void generateListner();
private:
    deque<Functor> functionsQueue;
    mutex globalLocker;
    condition_variable listner;
    atomic<bool> listnerEnded;
    atomic<bool> listnerStopped;
};