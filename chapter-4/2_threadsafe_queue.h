#ifndef INC_2_THREADSAFE_QUEUE_H
#define INC_2_THREADSAFE_QUEUE_H

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

namespace chapter_4 {

/*!
 * @brief Потокобезопасный контейнер, который обеспечивает удобный
 * интерфейс.
 * wait_and_pop() и try_pop() - главные функции удобного интерфейса
 */
template<typename T>
class threadsafe_queue {
private:
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;

public:
	threadsafe_queue() = default;

	threadsafe_queue(const threadsafe_queue& other) {
		std::lock_guard<std::mutex> lock(other.mut);
		data_queue = other.data_queue;
	}

	void push(T new_value) {
		std::lock_guard<std::mutex> lock(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}

	/*!
	 * @brief Отправляем поток в сон, если очередь пустая,
	 * ждём сигнал от std::conditional_variable data_cond
	 */
	void wait_and_pop(T& value) {
		std::unique_lock<std::mutex> lock(mut);
		data_cond.wait(lock, [this]() {return !data_queue.empty();});
		value = data_queue.front();
		data_queue.pop;
	}

	/*!
	 * @brief Сразу выходим из ф-ии, если очередь пустая
	 * @param value - возвращаемое значение
	 * @return Вернули/Не вернули value
	 */
	bool try_pop(T& value) {
		std::lock_guard<std::mutex> lock(mut);
		if (data_queue.empty()) {
			return false;
		}
		value = data_queue.front();
		data_queue.pop();
		return true;
	}

	bool empty() const {
		std::lock_guard<std::mutex> lock(mut);
		return data_queue.empty();
	}

};

}

#endif //INC_2_THREADSAFE_QUEUE_H
