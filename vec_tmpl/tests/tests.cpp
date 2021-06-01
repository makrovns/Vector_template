#include <gtest/gtest.h>
#include "vector_library.hpp"

TEST(vector_tests, algorithm_tests)
{
    mvec::vector<int> vec_test = {5,3,9,5,12,4,6,7};

    std::sort(vec_test.begin(), vec_test.end());

    auto it = std::next(vec_test.begin());

    for(; it != vec_test.end(); ++it)
    {
        ASSERT_LE(*std::prev(it), *it);
    }

    auto it_reverse = std::next(vec_test.rbegin());

    for(; it_reverse != vec_test.rend(); ++it_reverse)
    {
        ASSERT_GE(*std::prev(it_reverse), *it_reverse);
    }

}



int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}