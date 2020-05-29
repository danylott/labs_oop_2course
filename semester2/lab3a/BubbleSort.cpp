#include "BubbleSort.h"

#include <algorithm>
#include <thread>
#include <iostream>

std::vector<int> BubbleSort::get_array() {
    return this->array;
}

void BubbleSort::set_array(std::vector<int> arr) {
    this->array = std::move(arr);
}

void BubbleSort::simple_bubble_sort(std::vector<int> &vec) {
    for (size_t i = 0; i < vec.size() - 1; i++)
        for (size_t j = 0; j < vec.size() - i - 1; j++)
            if (vec[j] > vec[j+1])
                std::swap(vec[j], vec[j+1]);
}

void SequentialBubbleSort::sort() {
    simple_bubble_sort(array);
}

std::vector<std::vector<int>> ParallelBubbleSort::split_array(size_t n) {
    std::vector<std::vector<int>> result;
    size_t length = array.size() / n;
    size_t remain = array.size() % n;
    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, array.size()); i++) {
        end += (remain > 0) ? (length + ((remain--) != 0)) : length;
        result.emplace_back(array.begin() + begin, array.begin() + end);
        begin = end;
    }

    return result;
}

void ParallelBubbleSort::sort() {
    size_t thread_count = std::thread::hardware_concurrency();
    auto vectors = split_array(thread_count);
    std::vector<std::thread> threads;
    threads.reserve(vectors.size());
    for(auto & vec : vectors) {
        threads.emplace_back(simple_bubble_sort, std::ref(vec));
    }
    for(auto& th : threads) {
        th.join();
    }
    merge_array(vectors);
}

void ParallelBubbleSort::merge_array(std::vector<std::vector<int>> vectors) {
    if(vectors.empty()) {
        array = {};
        return;
    }
    if(vectors.size() == 1) {
        array = vectors[0];
        return;
    }
    std::vector<int> result;
    std::merge(vectors[0].begin(), vectors[0].end(), vectors[1].begin(), vectors[1].end(), std::back_inserter(result));

    for(std::size_t i = 2; i < vectors.size(); i++) {
        std::vector<int> temp;
        std::merge(result.begin(), result.end(), vectors[i].begin(), vectors[i].end(), std::back_inserter(temp));
        result = temp;
    }

    array = result;
}
