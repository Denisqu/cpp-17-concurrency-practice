#ifndef INC_9_BARRIERS_H
#define INC_9_BARRIERS_H

#include <barrier>
#include <vector>
#include <thread>
#include <string>
#include <iostream>
#include <algorithm>
#include <mutex>

namespace chapter_4 {

using data_type = std::string;
using data_chunk = data_type; using result_chunk = data_type;
using data_block = data_type;
using joining_thread = std::jthread;

struct data_source {
    std::string get_next_data_block() {
        if (data_blocks.empty()) {
            return "";
        }
        auto data_block = std::move(data_blocks.back());
        data_blocks.pop_back();
        return data_block;
    }
    bool done() {
        return data_blocks.empty();
    }
    std::vector<data_type> data_blocks;
};
struct result_block {
    void set_chunk(int id, int thread_count, data_type result) {
        std::lock_guard<std::mutex> guard(mut);
        result_chunks[id] = std::move(result);
    }

    std::mutex mut;
    std::vector<data_type> result_chunks;
};
struct data_sink {
    void write_data(result_block&& result) {
        for (const auto& chunk : result.result_chunks) {
            std::cout << chunk << std::endl;
        }
    }

};
result_chunk process(data_chunk data)
{
    std::cout << "processing data: " << data << std::endl;
    return data;
}
std::vector<data_chunk> divide_into_chunks(data_block data, unsigned num_threads)
{
    std::vector<data_chunk> chunks;
    for (int i = 0; i < num_threads; ++i) {
        auto string = std::string();
        auto offset = (data.size() / num_threads);
        auto endOffset = offset;
        string.insert(string.cend(), data.begin() + offset * i, data.begin() + endOffset * (i+1));
        std::cout << "chunk " << i << " = " << string << std::endl;
        chunks.push_back(string);
    }
    return chunks;
}

void process_data(data_source &source, data_sink &sink) {
	unsigned const concurrency = std::thread::hardware_concurrency();
	unsigned const num_threads = (concurrency > 0) ? concurrency : 2;
	std::barrier sync(num_threads);
	std::vector<joining_thread> threads(num_threads);
	std::vector<data_chunk> chunks;
	result_block result;
	for (unsigned i = 0; i < num_threads; ++i) {
		threads[i] = joining_thread([&, i] {
			while (!source.done()) {
				if (!i) {
					data_block current_block =
						source.get_next_data_block();
					chunks = divide_into_chunks(
						current_block, num_threads);
                    result.result_chunks.resize(num_threads + 1);
				}
				sync.arrive_and_wait();
				result.set_chunk(i, num_threads, process(chunks[i]));
				sync.arrive_and_wait();
				if (!i) {
					sink.write_data(std::move(result));
				}
			}
		});
	}
}

void execute_example_9()
{
    auto source = data_source();
    source.data_blocks.emplace_back("asdasaosk19r1inaj");
    source.data_blocks.emplace_back("120912j4mawdjkawd");
    source.data_blocks.emplace_back("iasd9320rk3m2dk2");
    auto sink = data_sink();
    process_data(source, sink);
}

}

#endif //INC_9_BARRIERS_H
