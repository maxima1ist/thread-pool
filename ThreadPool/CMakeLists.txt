cmake_minimum_required(VERSION 3.16.3)

project(ThreadPool)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
find_package(Boost 1.71.0 REQUIRED)

file(GLOB SOURCES Sourses/*)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE:Includes>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Includes>
            ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Boost_LIBRARIES}
            Threads::Threads)