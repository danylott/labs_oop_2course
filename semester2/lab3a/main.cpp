#define CATCH_CONFIG_MAIN
#include "BubbleSort.h"

#include "catch.hpp"

#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::size_t;

TEST_CASE("bubble_sort", "[threading]") {
    vector<int> vec{1, 5, 3, 2};
    BubbleSort* bs = new SequentialBubbleSort(vec);
    bs->sort();
    REQUIRE(bs->get_array() == vector<int>{1, 2, 3, 5});
}
