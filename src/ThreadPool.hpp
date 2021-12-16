#pragma once

#include "FunctionPool.hpp"

#include <vector>
#include <thread>

using std::thread;
using std::vector;

class ThreadPool
{
public:
    explicit ThreadPool(int count = thread::hardware_concurrency());
    ~ThreadPool();

    int getCount() const;

    void push(FunctionPool::Functor callable);

    void stop();
    void start();
private:
    FunctionPool functionPool;
    vector<thread> threads;
    int count;
};