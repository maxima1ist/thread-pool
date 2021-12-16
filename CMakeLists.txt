cmake_minimum_required(VERSION 3.5)

project(ThreadPool)

# sourses files
set(SOURCES 
        src/main.cpp
        src/ThreadPool.cpp
        src/FunctionPool.cpp
)
set(HEADERS
        src/ThreadPool.hpp
        src/FunctionPool.hpp
)
add_executable(ThreadPool ${SOURCES} ${HEADERS})

# specify c++ version
set_target_properties(
        ThreadPool PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

# enable multithreading
find_package(Threads)
target_link_libraries(ThreadPool Threads::Threads)

# enable boost::asio
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.77.0 REQUIRED COMPONENTS system thread regex)
if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})
target_link_libraries(ThreadPool ${USED_LIBS})