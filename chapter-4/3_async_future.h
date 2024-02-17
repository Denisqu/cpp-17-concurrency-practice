#ifndef INC_3_ASYNC_FUTURE_H
#define INC_3_ASYNC_FUTURE_H

#include <future>
#include <iostream>

namespace chapter_4 {

std::future<double> getFuture(int multiplier) {
	auto future = std::async(std::launch::async,
							 [multiplier]{
								 double result = 1;
								 for (int i = 0; i < 10000; ++i) {
									 result += multiplier;
									 std::cout << multiplier << "_" << result << std::endl;
								 }
								 return result;
							 });
	return future;
}

}

#endif //INC_3_ASYNC_FUTURE_H
