#ifndef EXAMPLE_3_H
#define EXAMPLE_3_H

void acquire_fence() {};
void release_fence() {};

bool can_enter = true;

void function_with_lock() {
	//...
	if (can_enter) {
		acquire_fence(); // LoadLoad + LoadStore
		/* All instructions stay
		 * between fences
		 * ... */
		release_fence(); // StoreStore + LoadStore
		can_enter = true;
	}
	//...
}

#endif //EXAMPLE_3_H
