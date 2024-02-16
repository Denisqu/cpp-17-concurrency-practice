#ifndef INC_6_GET_LOCK_H
#define INC_6_GET_LOCK_H

#include <mutex>

namespace chapter_3
{
void prepare_data();
void do_something();

/*!
 * @brief Данная ф-ия выступает в качестве
 * шлюза к данным, оберегаемым мьютексом.
 * В данном случае по данными подразумевается
 * внутренний вызов prepare_data()
 */
std::unique_lock<std::mutex> get_lock()
{
	extern std::mutex some_mutex;
	std::unique_lock<std::mutex> lock(some_mutex);
	prepare_data();

	return lock;
}

void process_data() {
	std::unique_lock<std::mutex> lock(get_lock());
	do_something();
}

}
#endif //INC_6_GET_LOCK_H
