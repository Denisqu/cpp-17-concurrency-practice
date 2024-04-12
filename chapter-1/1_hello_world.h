#ifndef CPP17_CONCURRENCY_PRACTICE_1_HELLO_WORLD_H
#define CPP17_CONCURRENCY_PRACTICE_1_HELLO_WORLD_H

#include <iostream>
#include <thread>

namespace chapter_1
{

inline void hello()
{
	std::cout << "Hello concurrent world!" << std::endl;
};

inline std::thread call_hello_concurrently()
{
	std::thread t(hello);
	return t;
}

void execute_example_1() {
    std::cout << "hello from main thread!" << std::endl;
    auto thread = call_hello_concurrently();
    thread.join();
}

}
#endif //CPP17_CONCURRENCY_PRACTICE_1_HELLO_WORLD_H