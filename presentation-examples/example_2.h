
#ifndef EXAMPLE_2_H
#define EXAMPLE_2_H

#include <cassert>
#include <atomic>

namespace before
{

int data;
volatile bool ready = false;

void foo() {        // cpu 0
	data = 42;
	// _________
	ready = true;
}

void bar() {
	if (ready) {    // cpu 1
		// _________
		assert(data == 42);
	}
}


}

namespace after
{

int data;
volatile bool ready = false;

void foo() {        // cpu 0
	ready = true;
	data = 42;
}

void bar() {
	if (ready) {    // cpu 1
		assert(data == 42);
	}
}

}

namespace after_2
{


int data;
std::atomic<bool> ready = false;
void foo() {        // cpu 0
	ready.store(true);
	data = 42;
}
void bar() {
	if (ready.load()) {    // cpu 1
		assert(data == 42);
	}
}

}

namespace after_3 {


int data;
std::atomic<bool> ready = false;
void foo() {        // cpu 0
	data = 42;
	std::atomic_thread_fence(std::memory_order_release);
	ready.store(true, std::memory_order_relaxed);
}
void bar() {
	if (ready.load(std::memory_order_relaxed)) {    // cpu 1
		std::atomic_thread_fence(std::memory_order_acquire);
		assert(data == 42);
	}
}

}


#endif //EXAMPLE_2_H
