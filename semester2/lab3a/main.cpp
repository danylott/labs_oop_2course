#define CATCH_CONFIG_MAIN
#include "BubbleSort.h"

#include "catch.hpp"

#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

TEST_CASE("BubbleSort", "[threading]") {
    BubbleSort *bs = nullptr;
    SECTION("SequentialBubbleSort") {
        bs = new SequentialBubbleSort();
    }

    bs->set_array(vector<int>{1, 5, 3, 2});
    bs->sort();
    REQUIRE(bs->get_array() == vector<int>{1, 2, 3, 5});

    bs->set_array(vector<int>{1, 2, 3, 4, 5});
    bs->sort();
    REQUIRE(bs->get_array() == vector<int>{1, 2, 3, 4, 5});
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

