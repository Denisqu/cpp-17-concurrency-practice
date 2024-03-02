#ifndef EXAMPLE_4_H
#define EXAMPLE_4_H

#include <cassert>

bool x = true;
bool y = true;

void foo() { // cpu 0
	x = false;
	assert(y);
}

void bar() { // cpu 1
	y = false;
	assert(x);
}

#endif //EXAMPLE_4_H
