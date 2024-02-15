#ifndef INC_1_PROTECTING_LIST_WITH_MUTEX_H
#define INC_1_PROTECTING_LIST_WITH_MUTEX_H

#include <list>
#include <mutex>
#include <algorithm>

static std::list<int> some_list;
static std::mutex some_mutex;

void add_to_list(int val) {
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(val);
}

bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	return std::find(std::begin(some_list), std::end(some_list), value_to_find)
		!= std::end(some_list);
}

#endif //INC_1_PROTECTING_LIST_WITH_MUTEX_H
