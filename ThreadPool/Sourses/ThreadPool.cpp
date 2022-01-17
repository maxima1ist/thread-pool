#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int count) : functionPool(), count(count)
{
    for (int i = 0; i < count; ++i)
    {
        threads.push_back(std::thread(&FunctionPool::generateListner, &functionPool));
    }
}

ThreadPool::~ThreadPool()
{
    functionPool.endListner();
    for (size_t i = 0; i < threads.size(); ++i)
    {
        threads.at(i).join();
    }
}

int ThreadPool::getCount() const
{
    return count;
}

void ThreadPool::push(FunctionPool::Functor callable)
{
    functionPool.push(callable);
}

void ThreadPool::stop()
{
    functionPool.stopListner();
}

void ThreadPool::start()
{
    functionPool.startListner();
}