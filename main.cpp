#include <iostream>
#include <stdexcept>
#include "chapter-1/1_hello_world.h"
#include "chapter-4/3_async_future.h"
#include "chapter-2/2_thread_guard.h"
#include "chapter-3/1_protecting_list_with_mutex.h"
#include "chapter-3/3_thread_safe_stack.h"
#include "chapter-4/3_async_future.h"

namespace {
    int oldMain() {
        std::cout << "hardware_concurrency() = " << std::thread::hardware_concurrency() << std::endl;
        if (true) {
            std::cout << "true..." << std::endl;
        }

        auto futer_1 = chapter_4::getFuture(2);
        auto futer_2 = chapter_4::getFuture(4);

        using namespace std::literals::chrono_literals;

        futer_1.wait();
        futer_2.wait();

        return 0;
    }

}

int main() {
    chapter_4::execute_example_3();
}
