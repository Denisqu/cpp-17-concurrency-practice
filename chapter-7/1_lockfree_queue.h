#ifndef CPP17_CONCURRENCY_PRACTICE_1_LOCKFREE_QUEUE_H
#define CPP17_CONCURRENCY_PRACTICE_1_LOCKFREE_QUEUE_H

#include <atomic>
#include <assert.h>

template<typename T>
class mpsc_queue_t
{
public:
    mpsc_queue_t() : _head(new buffer_node_t), _tail(_head.load(std::memory_order_relaxed))
    {
        buffer_node_t* front = _head.load(std::memory_order_relaxed);
        front->next.store(NULL, std::memory_order_relaxed);
    }

    ~mpsc_queue_t()
    {
        T output;
        while (this->dequeue(output)) {}
        buffer_node_t* front = _head.load(std::memory_order_relaxed);
        delete front;
    }

    void enqueue(const T& input)
    {
        buffer_node_t* node = new buffer_node_t;
        node->data = input;
        node->next.store(NULL, std::memory_order_relaxed);

        buffer_node_t* prev_head = _head.exchange(node, std::memory_order_acq_rel);
        prev_head->next.store(node, std::memory_order_release);
    }

    bool dequeue(T& output)
    {
        buffer_node_t* tail = _tail.load(std::memory_order_relaxed);
        buffer_node_t* next = tail->next.load(std::memory_order_acquire);

        if (next == NULL) {
            return false;
        }

        output = next->data;
        _tail.store(next, std::memory_order_release);
        delete tail;
        return true;
    }

private:
    struct buffer_node_t
    {
        T                           data;
        std::atomic<buffer_node_t*> next;
    };

    typedef char cache_line_pad_t[64];

    cache_line_pad_t            _pad0;
    std::atomic<buffer_node_t*> _head;

    cache_line_pad_t            _pad1;
    std::atomic<buffer_node_t*> _tail;

    mpsc_queue_t(const mpsc_queue_t&) {}
    void operator=(const mpsc_queue_t&) {}
};


#endif // CPP17_CONCURRENCY_PRACTICE_1_LOCKFREE_QUEUE_H
