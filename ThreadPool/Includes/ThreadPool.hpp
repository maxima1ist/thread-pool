#pragma once

#include "FunctionPool.hpp"

#include <vector>
#include <thread>

class ThreadPool
{
public:
    explicit ThreadPool(int count = std::thread::hardware_concurrency());
    ~ThreadPool();

    int getCount() const;
    void push(FunctionPool::Functor callable);
    void stop();
    void start();
    
private:
    FunctionPool functionPool;
    std::vector<std::thread> threads;
    int count;
};