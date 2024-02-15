#ifndef INC_5_MASTER_AND_SLAVE_THREADS_H
#define INC_5_MASTER_AND_SLAVE_THREADS_H

#include <thread>
#include <iostream>

namespace chapter_2
{

static std::thread::id master_thread_id;

void some_core_part_of_algorithm()
{
	if (std::this_thread::get_id() == master_thread_id) {
		std::cout << "doMasterWork() ..." << std::endl;
	}

	std::cout << "do common (slave/master) work" << std::endl;
}

}

#endif //INC_5_MASTER_AND_SLAVE_THREADS_H
