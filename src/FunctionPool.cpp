#include "FunctionPool.hpp"

FunctionPool::FunctionPool() : functionsQueue(),
                               globalLocker(),
                               listner(),
                               listnerStopped(false) {}

void FunctionPool::push(FunctionPool::Functor func)
{
    FunctionPool::Locker locker(globalLocker);
    functionsQueue.push_back(func);
    locker.unlock();
    listner.notify_one();
}

void FunctionPool::stopListner()
{
    listnerStopped = true;
    listner.notify_all();
}

void FunctionPool::generateListner()
{
    while(true)
    {
        Functor functor;
        FunctionPool::Locker locker(globalLocker);
        listner.wait(locker, [this]()
        {
            return !functionsQueue.empty() || listnerStopped;
        });
        if (listnerStopped && functionsQueue.empty())
        {
            break;
        }
        functor = functionsQueue.front();
        functionsQueue.pop_front();
        locker.unlock();
        functor();
    }
}