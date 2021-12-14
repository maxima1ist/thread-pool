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
    FunctionPool() : functionsQueue(),
                     globalLocker(),
                     listner(),
                     listnerStopped(false) {}

    void push(Functor func)
    {
        Locker locker(globalLocker);
        functionsQueue.push_back(func);
        locker.unlock();
        listner.notify_one();
    }

    void stopListner()
    {
        listnerStopped = true;
        listner.notify_all();
    }

    void generateListner()
    {
        while(true)
        {
            Functor functor;
            Locker locker(globalLocker);
            listner.wait(locker, [this]() { return !functionsQueue.empty() || listnerStopped; });
            if (listnerStopped && functionsQueue.empty())
            {
                return;
            }
            functor = functionsQueue.front();
            functionsQueue.pop_front();
            locker.unlock();
            functor();
        }
    }

private:
    deque<Functor> functionsQueue;
    mutex globalLocker;
    condition_variable listner;
    atomic<bool> listnerStopped;
};