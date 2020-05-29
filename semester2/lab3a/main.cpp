#define CATCH_CONFIG_MAIN
#include "BubbleSort.h"

#include "catch.hpp"

#include <vector>
#include <random>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

int rand_num(int max) {
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(0, max);
    return dist(gen);
}

vector<int> create_random_vector(size_t size, int max_num) {
    vector<int> result;
    for(size_t i = 0; i < size; i++) {
        result.push_back(rand_num(max_num));
    }
    return result;
}

TEST_CASE("BubbleSort", "[threading]") {
    BubbleSort *bs = nullptr;
    SECTION("SequentialBubbleSort") {
        bs = new SequentialBubbleSort();
    }

    SECTION("ParallelBubbleSort") {
        bs = new ParallelBubbleSort();
    }

    bs->set_array(vector<int>{1, 5, 3, 2});
    bs->sort();
    REQUIRE(bs->get_array() == vector<int>{1, 2, 3, 5});

    bs->set_array(vector<int>{1, 2, 3, 4, 5});
    bs->sort();
    REQUIRE(bs->get_array() == vector<int>{1, 2, 3, 4, 5});

    vector<int> vec{1, 2, 10, 1234, 1332, 123, 839, 9485, 1234, 984988, 234, 5};
    bs->set_array(vec);
    auto sorted = vec;
    std::sort(sorted.begin(), sorted.end());
    bs->sort();
    REQUIRE(bs->get_array() == sorted);

    vec = create_random_vector(100, 1000);
    bs->set_array(vec);
    sorted = vec;
    std::sort(sorted.begin(), sorted.end());
    bs->sort();
    REQUIRE(bs->get_array() == sorted);
}

TEST_CASE("split_array", "[threading]") {
    auto pbs = new ParallelBubbleSort(vector<int>{1, 2, 3, 4, 5});
    REQUIRE(pbs->split_array(3) == vector<vector<int>>{vector<int>{1,2}, vector<int>{3,4}, vector<int>{5}});
}


TEST_CASE("merge_array", "[threading]") {
    auto pbs = new ParallelBubbleSort();
    pbs->merge_array(vector<vector<int>>{vector<int>{1,2}, vector<int>{3,4}, vector<int>{5}});
    REQUIRE(pbs->get_array() == vector<int>{1, 2, 3, 4, 5});
}

