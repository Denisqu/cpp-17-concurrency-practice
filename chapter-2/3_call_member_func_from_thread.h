#ifndef INC_3_CALL_MEMBER_FUNC_FROM_THREAD_H
#define INC_3_CALL_MEMBER_FUNC_FROM_THREAD_H

namespace chapter_2 {

#include <iostream>
#include <thread>

class X {
public:
	void member_func(int x) {
		std::cout << x << std::endl;
	}
};

std::thread call_member_func_from_thread() {
	X x;
	std::thread t(&X::member_func, x, 100);

	return t;
}

}

#endif //INC_3_CALL_MEMBER_FUNC_FROM_THREAD_H
