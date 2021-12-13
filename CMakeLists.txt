
cmake_minimum_required(VERSION 3.5)

project(ThreadPool)

set(SOURCES 
        src/main.cpp 
        src/function_pool.cpp
)
set(HEADERS
        src/ThreadPool.h
        src/function_pool.h
)
add_executable(ThreadPool ${SOURCES} ${HEADERS})

set_target_properties(
        ThreadPool PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
)

find_package(Threads)
target_link_libraries(ThreadPool Threads::Threads)