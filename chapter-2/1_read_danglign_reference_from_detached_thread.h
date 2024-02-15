#ifndef INC_1_READ_DANGLIGN_REFERENCE_FROM_DETACHED_THREAD_H
#define INC_1_READ_DANGLIGN_REFERENCE_FROM_DETACHED_THREAD_H

#include <iostream>
#include <thread>

namespace chapter_2
{

struct func
{
	int &i;
	func(int &i_)
		: i(i_)
	{}
	void operator()()
	{
		for (unsigned j = 0; j < 1000000; ++j) {
			std::cout << ++i << std::endl;
		}
	}
};

void oops()
{
	int local_variable = 12345;
	func f(local_variable);
	std::thread my_thread(f);
	my_thread.detach();
}

}

#endif //INC_1_READ_DANGLIGN_REFERENCE_FROM_DETACHED_THREAD_H
