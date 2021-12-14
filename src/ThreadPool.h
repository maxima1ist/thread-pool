#pragma once

#include "FunctionPool.h"

#include <thread>
#include <vector>

using std::thread;
using std::vector;

class ThreadPool
{
public:
    explicit ThreadPool(int count = thread::hardware_concurrency()) : functionPool() {
        for (int i = 0; i < count; ++i)
        {
            threads.push_back(thread(&FunctionPool::generateListner, &functionPool));
        }
    }

    ~ThreadPool()
    {
        functionPool.stopListner();
        for (size_t i = 0; i < threads.size(); ++i)
        {
            threads.at(i).join();
        }
    }

    void push(FunctionPool::Functor callable)
    {
        functionPool.push(callable);
    }

private:
    FunctionPool functionPool;
    vector<thread> threads;
};