#pragma once

#include "function_pool.h"

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
            threads.push_back(thread(&Function_pool::infinite_loop_func, &functionPool));
        }
    }

    ~ThreadPool()
    {
        functionPool.done();
        for (unsigned int i = 0; i < threads.size(); i++)
        {
            threads.at(i).join();
        }
    }

    template<typename Functor>
    void push(Functor callable)
    {
        functionPool.push(callable);
    }
private:
    Function_pool functionPool;
    vector<thread> threads;
};