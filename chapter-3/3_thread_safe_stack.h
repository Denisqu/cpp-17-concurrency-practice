#ifndef INC_3_THREAD_SAFE_STACK_H
#define INC_3_THREAD_SAFE_STACK_H

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

namespace chapter_3
{

struct empty_stack: std::exception
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

}

#endif //INC_3_THREAD_SAFE_STACK_H
