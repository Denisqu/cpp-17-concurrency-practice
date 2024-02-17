#include <iostream>
#include <stdexcept>
#include "chapter-4/3_async_future.h"


int main() {
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
