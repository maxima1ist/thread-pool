#include "ThreadPool.h"

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
    for (int i = 0; i < 30; i++)
    {
        threadPool.push(func);
    }
    return 0;
}