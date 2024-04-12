//
// Created by user on 15.02.2024.
//

#ifndef INC_4_SCOPED_THREAD_H
#define INC_4_SCOPED_THREAD_H

#include <thread>
#include <stdexcept>
namespace chapter_2 {
class scoped_thread {
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) : t(std::move(t_)) {
		if (!t.joinable()) {
			throw std::logic_error("No thread");
		}
	}
	~scoped_thread() {
		t.join();
	}
	scoped_thread(const scoped_thread&) = delete;
	scoped_thread& operator=(const scoped_thread&) = delete;
};
}

#endif //INC_4_SCOPED_THREAD_H
