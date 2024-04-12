cmake_minimum_required(VERSION 3.27)
project(cpp17_concurrency_practice)

set(CMAKE_CXX_STANDARD 20)

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
        chapter-3/6_get_lock.h
        chapter-3/7_infamous_double_checking_and_call_once.h
        chapter-3/8_shared_mutex_dns_cache.h
        chapter-4/1_wait_for_data_with_condiitonal_variable.h
        chapter-4/2_threadsafe_queue.h
        chapter-4/3_async_future.h
        chapter-4/4_packaged_task.h
        chapter-4/5_parallel_quick_sort.h
        chapter-4/6_message_passing_atm_architecture.h
        chapter-4/7_future_continuation.h
        chapter-4/8_latches.h
        chapter-4/9_barriers.h
        chapter-4/10_flex_barriers.h
        presentation-examples/example_1.h
        presentation-examples/example_2.h
        presentation-examples/example_3.h
        presentation-examples/example_4.h
        presentation-examples/example_5.h
)
