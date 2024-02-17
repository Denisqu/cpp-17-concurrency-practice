#ifndef INC_1_WAIT_FOR_DATA_WITH_CONDIITONAL_VARIABLE_H
#define INC_1_WAIT_FOR_DATA_WITH_CONDIITONAL_VARIABLE_H

#include <mutex>
#include <queue>
#include <condition_variable>

namespace chapter_3 {

using data_chunk = std::array<int, 5>;

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;
int data_to_prepare = 3;

void process(data_chunk data);
int more_data_to_prepare() { return data_to_prepare--; }

void data_preparation_thread() {
	while(more_data_to_prepare()) {
		const data_chunk data = {0, 1, 2, 3, 4};
		{
			std::lock_guard<std::mutex> lk(mut);
			data_queue.push(data);
		}
		data_cond.notify_one();
	}
}

void data_processing_thread() {
	while (true) {
		/* Нужно использовать
		 * именно unique_lock,
		 * чтобы мьютекс освободился
		 * при ожидании conditional_varialbe*/
		std::unique_lock<std::mutex> lock(mut);
		data_cond.wait(lock,[]{return !data_queue.empty();});
		data_chunk data = data_queue.front();
		data_queue.pop();
		lock.unlock();
		process(data);
	}
}

}

#endif //INC_1_WAIT_FOR_DATA_WITH_CONDIITONAL_VARIABLE_H
