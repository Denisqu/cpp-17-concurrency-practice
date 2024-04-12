#ifndef INC_8_LATCHES_H
#define INC_8_LATCHES_H

#include <latch>
#include <vector>
#include <future>
#include <thread>
#include <iostream>

namespace chapter_4 {

using my_data = std::vector<unsigned int>;
void do_more_stuff() { std::cout << "do_more_stuff()"; }
my_data make_data(unsigned int i)
{
    return { 1 * i, 2 * i, 3 * i,
             4 * i, 5 * i, 6 * i };
}
void process_data(my_data* data, unsigned int thread_count) { /* ... */ }

void foo()
{
	unsigned const thread_count = 8;
	std::latch done(thread_count);
	my_data data[thread_count];
	std::vector<std::future<void>> threads;
	for (unsigned i = 0; i < thread_count; ++i)
		threads.push_back(std::async(std::launch::async, [&, i]
		{
			data[i] = make_data(i);
			done.count_down();
			do_more_stuff();
		}));
	done.wait();
	process_data(data, thread_count);
}

}

#endif //INC_8_LATCHES_H
