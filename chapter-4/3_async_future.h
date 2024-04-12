#ifndef INC_3_ASYNC_FUTURE_H
#define INC_3_ASYNC_FUTURE_H

#include <future>
#include <iostream>
#include <chrono>

namespace chapter_4 {

std::future<int> getFuture(int multiplier)
{
    auto future = std::async(std::launch::async,[multiplier] {
                                 int result = 1;
                                 for (int i = 0; i < 1000000000; ++i) {
                                     result += multiplier;
                                 }
                                 return result;
                             });
    return future;
}

void execute_example_3() {
    using namespace std::chrono_literals;
    auto fut_1 = getFuture(11111111);
    int val_1 = 0;
    while (fut_1.wait_for(0.1s) != std::future_status::ready) {
        std::cout << "waiting for future..." << std::endl;
    }
    val_1 = fut_1.get();
    std::cout << val_1 << std::endl;
}

}

#endif //INC_3_ASYNC_FUTURE_H
