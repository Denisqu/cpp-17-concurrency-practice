#ifndef EXAMPLE_1_H
#define EXAMPLE_1_H
#include <mutex>

class Singleton {};
Singleton* instance;
std::mutex lock;

namespace before
{

Singleton *get() {
	if (instance == nullptr) {
		std::lock_guard<std::mutex> guard(lock);
		if (instance == nullptr) {
			instance = new Singleton();
		}
	}
	return instance;
}



}

namespace after
{

// after compiler optimization
Singleton *get() {
	if (instance == nullptr) {
		std::lock_guard<std::mutex> guard(lock);
		if (instance == nullptr) {
			instance = static_cast<Singleton*>(operator new(sizeof(Singleton)));
			new (instance) Singleton();
		}
	}
	return instance;
}

}
#endif //EXAMPLE_1_H
