#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include "huffman_node.h"
#include "constants.h"

template <typename T>
class QueueMin {
public:
    explicit QueueMin(std::vector<T> number_entry);
    T GetMinValue();
    void AddValue(T value);
    size_t Size();

private:
    std::queue<T> queue_min_start_;
    std::queue<T> queue_min_added_;
};

template <typename T>
QueueMin<T>::QueueMin(std::vector<T> number_entry) {
    std::sort(number_entry.begin(), number_entry.end());
    for (const auto &i : number_entry) {
        queue_min_start_.emplace(i);
    }
}

template <typename T>
T QueueMin<T>::GetMinValue() {
    if (!queue_min_start_.empty() &&
        (queue_min_added_.empty() || queue_min_start_.front() < queue_min_added_.front())) {
        auto result = queue_min_start_.front();
        queue_min_start_.pop();
        return result;
    } else {
        auto result = queue_min_added_.front();
        queue_min_added_.pop();
        return result;
    }
}

template <typename T>
void QueueMin<T>::AddValue(T value) {
    queue_min_added_.emplace(value);
}

template <typename T>
size_t QueueMin<T>::Size() {
    return queue_min_added_.size() + queue_min_start_.size();
}
