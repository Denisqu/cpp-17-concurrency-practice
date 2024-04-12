#ifndef INC_3_THREAD_SAFE_STACK_H
#define INC_3_THREAD_SAFE_STACK_H

#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <chrono>
#include <iostream>

namespace chapter_3
{

struct empty_stack : std::exception
{
	[[nodiscard]] const char *what() const noexcept override {
		return "Empty stack!";
	}
};

template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m;

public:
	threadsafe_stack() = default;
	threadsafe_stack(const threadsafe_stack& other) {
		std::lock_guard<std::mutex> lockGuard(other.m);
		data = other.data;
	}
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;

	void push(T new_value) {
		std::lock_guard<std::mutex> lock(m);
		data.push(std::move(new_value));
	}

	std::shared_ptr<T> pop() {
		std::lock_guard<std::mutex> lock(m);
		if(data.empty()) {
			throw empty_stack();
		}
		/* Возвращаем результат в виде поинтера
		 * т.к в таком случае не возникнет
		 * потери данных после броска исключения в
		 * копи-конструкторе T */
		auto result = std::make_shared<T>(data.top());
		data.pop();
		return result;
	}

	void pop(T& value) {
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) {
			throw empty_stack();
		}

		value = data.top;
		data.pop;
	}

	bool empty() const {
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}

};

void execute_example_3() {
    using namespace std::chrono_literals;
    threadsafe_stack<int> stack;

    auto thread_1 = std::thread([&stack](){
        for (auto i = 0; i < 10; ++i) {
            stack.push(i);
            std::this_thread::sleep_for(50ms);
        }
    });

    auto thread_2 = std::thread([&stack](){
        while(true) {
            try {
                std::this_thread::sleep_for(100ms);
                auto value = stack.pop();
                std::cout << "got value: " << *value << std::endl;
            }
            catch (std::exception& err) {
                std::cout << err.what();
                break;
            }
        }
    });

    thread_1.join();
    thread_2.join();
}

}
/*
got value: 1
got value: 3
got value: 5
got value: 6
got value: 8
got value: 9
got value: 7
got value: 4
got value: 2
got value: 0
Empty stack!
*/


#endif //INC_3_THREAD_SAFE_STACK_H
