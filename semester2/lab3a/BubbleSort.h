#ifndef LAB3A_BUBBLESORT_H
#define LAB3A_BUBBLESORT_H

#include <utility>
#include <vector>

class BubbleSort {
protected:
    std::vector<int> array;

public:
    BubbleSort() = default;
    explicit BubbleSort(std::vector<int> array) : array(std::move(array)) {};
    virtual void sort()=0;
    std::vector<int> get_array();
    void set_array(std::vector<int> array);
};

class SequentialBubbleSort : public BubbleSort {
public:
    SequentialBubbleSort() = default;
    explicit SequentialBubbleSort(std::vector<int> array) : BubbleSort(std::move(array)) {};
    void sort() override;
};

#endif //LAB3A_BUBBLESORT_H
