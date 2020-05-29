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
}
