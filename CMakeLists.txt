cmake_minimum_required(VERSION 4.1)
project(task3 C)

set(CMAKE_C_STANDARD 11)

add_executable(task3 main.c
        can_queue.h
        can_queue.c)
