#include <iostream>
#include "chapter-1/1_hello_world.h"

int main() {

    auto thread = chapter_1::call_hello_concurrently();
	std::cout << "This string is from other thread" << std::endl;
	thread.join();

    return 0;
}
