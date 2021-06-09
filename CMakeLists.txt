cmake_minimum_required(VERSION 3.13)
project(Timer_)

set(CMAKE_CXX_STANDARD 11)

add_executable(Timer_ main.cpp Timer.cpp Timer.h)

find_package(Threads REQUIRED)
target_link_libraries(Timer_ Threads::Threads)