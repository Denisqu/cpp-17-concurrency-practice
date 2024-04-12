#ifndef INC_2_BYPASS_MUTEX_WITH_FUNC_H
#define INC_2_BYPASS_MUTEX_WITH_FUNC_H

namespace chapter_3
{

#include <string>
#include <mutex>

class some_data
{
	int a;
	std::string b;
public:
	void do_something();
};

class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> lockGuard(m);
		func(data);
	}
};

some_data *unprotected;
data_wrapper x;

void malicious_func(some_data &protected_data)
{
	unprotected = &protected_data;
}

void foo()
{
	x.process_data(malicious_func);
	unprotected->do_something(); // trouble. got access to protected data outside the mutex
}

}

#endif //INC_2_BYPASS_MUTEX_WITH_FUNC_H
