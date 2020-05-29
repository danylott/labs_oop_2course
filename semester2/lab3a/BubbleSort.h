#ifndef LAB3A_BUBBLESORT_H
#define LAB3A_BUBBLESORT_H

#include <utility>
#include <vector>

class BubbleSort {
protected:
    std::vector<int> array;
    static void simple_bubble_sort(std::vector<int>& vec);

public:
    BubbleSort() = default;
    explicit BubbleSort(std::vector<int> array) : array(std::move(array)) {};
    virtual void sort()=0;
    virtual std::vector<int> get_array();
    virtual void set_array(std::vector<int> array);
};

class SequentialBubbleSort : public BubbleSort {
public:
    SequentialBubbleSort() = default;
    explicit SequentialBubbleSort(std::vector<int> array) : BubbleSort(std::move(array)) {};
    void sort() override;
};

class ParallelBubbleSort : public BubbleSort {
public:
    ParallelBubbleSort() = default;
    explicit ParallelBubbleSort(std::vector<int> array) : BubbleSort(std::move(array)) {};
    void sort() override;

    // should be private, but here for tests - public
public:
    std::vector<std::vector<int>> split_array(size_t n);
    void merge_array(std::vector<std::vector<int>> vectors);
};

#endif //LAB3A_BUBBLESORT_H
