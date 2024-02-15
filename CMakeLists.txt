cmake_minimum_required(VERSION 3.27)
project(cpp17_concurrency_practice)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp17_concurrency_practice main.cpp
        chapter-1/1_hello_world.h
        chapter-2/1_read_danglign_reference_from_detached_thread.h
        chapter-2/2_thread_guard.h
        chapter-2/3_call_member_func_from_thread.h
        chapter-2/4_scoped_thread.h)
