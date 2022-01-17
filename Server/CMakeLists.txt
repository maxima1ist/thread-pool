cmake_minimum_required(VERSION 3.16.3)

project(Server)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
        PUBLIC
            ThreadPool)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ThreadPool)