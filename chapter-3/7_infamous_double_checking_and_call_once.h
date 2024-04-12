#ifndef INC_7_INFAMOUS_DOUBLE_CHECKING_AND_CALL_ONCE_H
#define INC_7_INFAMOUS_DOUBLE_CHECKING_AND_CALL_ONCE_H

namespace chapter_3 {

#include <memory>
#include <mutex>

static std::shared_ptr<int> resource_ptr = nullptr;
static std::mutex resource_mutex;

/*!
 * @brief Так делать нельзя, большая вероятность
 * наткнуться на data-race, когда один тред читает, а другой пишет,
 * что приводит к UB
 */
void undefined_behaviour_with_double_checked_locking() {
	if (!resource_ptr) {
		std::unique_lock<std::mutex> lock(resource_mutex);
		if (!resource_ptr) {
            /* Компилятор может сначала выделить память и назначить
             * эту память переменной, а зетем уже записать туда 42 => возможна
             * ситуация, когда resource_ptr уже не nullptr, но и не 42
             * => если читать\писать без мьютекса - то это UB
             */
			resource_ptr = std::make_shared<int>(42);
		}
	}
	++(*resource_ptr);
}

// Good code, example 1:
std::once_flag resource_flag;
void init_resource() {
	resource_ptr.reset(new int(42));
}
/*!
 * @brief Хороший код, инициализация ресурса будет вызвана
 * ровно один раз, независимо от того, сколько потоков пытаются
 * сделать это одновременно
 */
void foo() {
	std::call_once(resource_flag, init_resource);
	++(*resource_ptr);
}

// Good code, example 2:
class my_class;
my_class& get_my_class_instance() {
	// Начиная с C++11 данный код будет гарантированно
	// Потокобезопасным, instance будет сконструирован только
	// одним потоком.
	static my_class instance;
	return instance;
}


}

#endif //INC_7_INFAMOUS_DOUBLE_CHECKING_AND_CALL_ONCE_H
