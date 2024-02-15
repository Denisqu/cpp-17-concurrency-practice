#include <iostream>
#include <stdexcept>
#include "chapter-1/1_hello_world.h"
#include "chapter-2/1_read_danglign_reference_from_detached_thread.h"
#include "chapter-2/2_thread_guard.h"


int main() {
	std::cout << "hardware_concurrency() = " << std::thread::hardware_concurrency() << std::endl;

    return 0;
}
