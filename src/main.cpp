#include "ThreadPool.hpp"

#include <iostream>

using std::cout;

int num = 0;

void func()
{
    for (size_t i = 0; i < 1e9; ++i);
    cout << num++ << '\n';
}

int main()
{
    ThreadPool threadPool;
    for (int i = 0; i < 15; i++)
    {
        threadPool.push(func);
    }
    threadPool.stop();

    for (int i = 0; i < 30; i++)
    {
        threadPool.push(func);
    }
    threadPool.start();

    return 0;
}