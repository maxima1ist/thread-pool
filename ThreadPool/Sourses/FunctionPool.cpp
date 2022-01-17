#include "FunctionPool.hpp"

FunctionPool::FunctionPool() : functionsQueue(),
                               globalLocker(),
                               listner(),
                               listnerStopped(false),
                               listnerEnded(false) {}

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
}

void FunctionPool::startListner()
{
    listnerStopped = false;
}

void FunctionPool::endListner()
{
    listnerEnded = true;
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
            return !listnerStopped && (!functionsQueue.empty() || listnerEnded);
        });
        if (listnerEnded && functionsQueue.empty())
        {
            break;
        }
        functor = functionsQueue.front();
        functionsQueue.pop_front();
        locker.unlock();
        functor();
    }
}