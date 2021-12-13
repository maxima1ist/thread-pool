#include "ThreadPool.h"

#include <iostream>

int num = 0;

void func()
{
    for (size_t i = 0; i < 1e9; ++i);
    std::cout << num++ << '\n';
}

int main()
{
    ThreadPool threadPool;
    for (int i = 0; i < 50; i++)
    {
        threadPool.push(func);
    }
    return 0;
}