#include "BubbleSort.h"

#include <algorithm>

std::vector<int> BubbleSort::get_array() {
    return this->array;
}

void BubbleSort::set_array(std::vector<int> arr) {
    this->array = std::move(arr);
}

void SequentialBubbleSort::sort() {
    for (size_t i = 0; i < array.size() - 1; i++)
        for (size_t j = 0; j < array.size() - i - 1; j++)
            if (array[j] > array[j+1])
                std::swap(array[j], array[j+1]);
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
