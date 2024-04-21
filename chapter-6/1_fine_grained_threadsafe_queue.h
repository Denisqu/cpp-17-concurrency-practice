#ifndef CPP17_CONCURRENCY_PRACTICE_1_FINE_GRAINED_THREADSAFE_QUEUE_H
#define CPP17_CONCURRENCY_PRACTICE_1_FINE_GRAINED_THREADSAFE_QUEUE_H

#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <iostream>

namespace chapter_6 {

template<typename T>
class threadsafe_queue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node* tail;
    std::condition_variable data_cond;

public:
    threadsafe_queue()
        : head(new node)
        , tail(head.get())
    {
    }
    threadsafe_queue(const threadsafe_queue& other) = delete;
    threadsafe_queue& operator=(const threadsafe_queue& other) = delete;

    void push(T new_value)
    {
        auto new_data = std::make_shared<T>(std::move(new_value));
        std::unique_ptr<node> p(new node);
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->data = new_data;
            node* const new_tail = p.get();
            tail->next = std::move(p);
            tail = new_tail;
        }
    }
    node* get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }
    std::unique_ptr<node> pop_head()
    {
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }
    std::unique_lock<std::mutex> wait_for_data()
    {
        std::unique_lock<std::mutex> head_lock(head_mutex);
        data_cond.wait(head_lock, [&] { return head.get() != get_tail(); });
        return std::move(head_lock);
    }
    std::unique_ptr<node> wait_pop_head()
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        return pop_head();
    }
    std::unique_ptr<node> wait_pop_head(T& value)
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        value = std::move(*head->data);
        return pop_head();
    }
};

void execute_example_1()
{
    threadsafe_queue<std::string> string_queue;
    string_queue.push("first");
    string_queue.push("second");
    string_queue.push("third");

    std::jthread thread1([&string_queue]() {
       std::cout << std::endl << "thread1: " << *string_queue.wait_pop_head()->data;
    });

    std::jthread thread2([&string_queue]() {
        std::cout << std::endl << "thread2: " << *string_queue.wait_pop_head()->data;
    });

    std::jthread thread3([&string_queue]() {
        std::cout << std::endl << "thread3: " << *string_queue.wait_pop_head()->data;
    });

    std::jthread thread4([&string_queue]() {
        std::cout << std::endl << "thread4: " << *string_queue.wait_pop_head()->data;
    });
}

}
#endif // CPP17_CONCURRENCY_PRACTICE_1_FINE_GRAINED_THREADSAFE_QUEUE_H
