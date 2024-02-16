cmake_minimum_required(VERSION 3.27)
project(cpp17_concurrency_practice)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp17_concurrency_practice main.cpp
        chapter-1/1_hello_world.h
        chapter-2/1_read_danglign_reference_from_detached_thread.h
        chapter-2/2_thread_guard.h
        chapter-2/3_call_member_func_from_thread.h
        chapter-2/4_scoped_thread.h
        chapter-2/5_master_and_slave_threads.h
        chapter-3/1_protecting_list_with_mutex.h
        chapter-3/2_bypass_mutex_with_func.h
        chapter-3/3_thread_safe_stack.h
        chapter-3/4_lock_two_mutexes_simultaneous.h
        chapter-3/5_hierarchical_mutex.h
)
