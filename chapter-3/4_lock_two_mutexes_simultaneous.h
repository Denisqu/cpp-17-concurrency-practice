#ifndef INC_4_LOCK_TWO_MUTEXES_SIMULTANEOUS_H
#define INC_4_LOCK_TWO_MUTEXES_SIMULTANEOUS_H

#include <mutex>
namespace chapter_3 {

class some_big_object;
void swap(some_big_object& lhs, some_big_object& rhs);

class X {
public:
	explicit X(const some_big_object &someDetail)
		: some_detail(someDetail) {}

	friend void swap(X& lhs, X& rhs) {
		if (&lhs==&rhs)
			return;
		std::lock(lhs.m, rhs.m);
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
		swap(lhs.some_detail, rhs.some_detail);
	}

private:
	some_big_object some_detail;
	std::mutex m;

};

}

#endif //INC_4_LOCK_TWO_MUTEXES_SIMULTANEOUS_H
