#include "BubbleSort.h"

#include <utility>

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