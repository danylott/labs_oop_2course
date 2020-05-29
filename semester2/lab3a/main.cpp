#include <iostream>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

void bubble_sort(vector<int> &vec) {
    for (size_t i = 0; i < vec.size() - 1; i++)
        for (size_t j = 0; j < vec.size() - i - 1; j++)
            if (vec[j] > vec[j+1])
                std::swap(vec[j], vec[j+1]);
}

TEST_CASE("bubble_sort", "[threading]") {
    vector<int> vec{1, 5, 3, 2};
    bubble_sort(vec);
    REQUIRE(vec == vector<int>{1, 2, 3, 5});
}
