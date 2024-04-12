//
// Created by user on 15.02.2024.
//

#ifndef INC_2_THREAD_GUARD_H
#define INC_2_THREAD_GUARD_H

#include <iostream>
#include <thread>

namespace chapter_2 {

class thread_guard {
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) : t(t_) {}
	~thread_guard() {
		if (t.joinable()) {
			t.join();
		}
	}
	thread_guard(const thread_guard&) = delete;
	thread_guard& operator= (const thread_guard&) = delete;
};

void execute_example_2() {
    std::thread thread([](){
        for (int i = 0; i < 10e4; ++i) {
            std::cout << i;
        }
    });
    thread_guard guard(thread); // NO UB HERE :)
}

}

#endif //INC_2_THREAD_GUARD_H
