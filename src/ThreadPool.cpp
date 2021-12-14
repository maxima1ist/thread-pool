#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int count) : functionPool()
{
    for (int i = 0; i < count; ++i)
    {
        threads.push_back(thread(&FunctionPool::generateListner, &functionPool));
    }
}

ThreadPool::~ThreadPool()
{
    functionPool.stopListner();
    for (size_t i = 0; i < threads.size(); ++i)
    {
        threads.at(i).join();
    }
}

void ThreadPool::push(FunctionPool::Functor callable)
{
    functionPool.push(callable);
}