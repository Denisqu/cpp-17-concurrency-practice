#ifndef EXAMPLE_5_H
#define EXAMPLE_5_H

namespace example_5
{

int *GlobalPointer = nullptr;

int main() {
	/* ... */
	int *ptr = GlobalPointer;
	if (ptr) {
		int value = *ptr;
	}
}

enum memory_order {
	memory_order_relaxed,
	memory_order_consume,
	memory_order_acquire,
	memory_order_release,
	memory_order_acq_rel,
	memory_order_seq_cst
};

#include <atomic>

template<typename T>
T load(memory_order order = memory_order_seq_cst);

template<typename T>
void store(T desired, memory_order = memory_order_seq_cst);

void atomic_thread_fence(memory_order order);

}

#endif //EXAMPLE_5_H
