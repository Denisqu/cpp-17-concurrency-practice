#ifndef INC_1_PROTECTING_LIST_WITH_MUTEX_H
#define INC_1_PROTECTING_LIST_WITH_MUTEX_H

#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

namespace chapter_3 {

static std::list<int> some_list;
static std::mutex some_mutex;

void add_to_list(int val)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    some_list.push_back(val);
}

bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(std::begin(some_list), std::end(some_list), value_to_find)
           != std::end(some_list);
}

void execute_example_1()
{
    std::thread thread_1([]() {
        using namespace std::chrono_literals;
        for (auto i = 0; i < 100; ++i) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(0, 100);
            auto val = distr(gen);
            std::cout << "does list contain this value: "
                      << val << " ?:" << list_contains(val)
                      << std::endl;
            std::this_thread::sleep_for(100ms);
        }
    });
    std::thread thread_2([]() {
        using namespace std::chrono_literals;
        for (auto i = 0; i < 100; ++i) {
            add_to_list(i);
            std::cout << "added value to list: " << i << std::endl;
            std::this_thread::sleep_for(50ms);
        }
    });

    thread_1.join();
    thread_2.join();
}

}

#endif //INC_1_PROTECTING_LIST_WITH_MUTEX_H
