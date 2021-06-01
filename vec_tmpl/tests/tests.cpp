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

    auto max_el = std::max_element(vec_test.begin(), vec_test.end());
    auto min_el = std::min_element(vec_test.begin(), vec_test.end());

    ASSERT_EQ(vec_test.back(), *max_el);
    ASSERT_EQ(vec_test.front(), *min_el);

}

TEST(vector_tests, back_front_tests)
{
    mvec::vector<int> vec_test = {5,3,9,5,12,4,6,7};

    std::sort(vec_test.begin(), vec_test.end());

    auto max_el = std::max_element(vec_test.begin(), vec_test.end());
    auto min_el = std::min_element(vec_test.begin(), vec_test.end());

    ASSERT_EQ(vec_test.back(), *max_el);
    ASSERT_EQ(vec_test.front(), *min_el);

}

TEST(vector_tests, insert_tests)
{
    mvec::vector<int> vec_test;
    auto int_insrt = 34;

    vec_test.insert(vec_test.begin(), 5);
    vec_test.insert(vec_test.begin(), int_insrt);
    vec_test.insert(std::next(vec_test.begin()), 9);
    vec_test.insert(vec_test.begin(), 16);
    vec_test.insert(vec_test.begin() + 2, 8);
    vec_test.insert(std::prev(vec_test.end()), 15);
    vec_test.insert(vec_test.end(), 11);

    ASSERT_EQ(vec_test.size(), 7);
    ASSERT_EQ(vec_test[0], 16);
    ASSERT_EQ(vec_test[1], 34);
    ASSERT_EQ(vec_test[2], 8);
    ASSERT_EQ(vec_test[3], 9);
    ASSERT_EQ(vec_test[4], 15);
    ASSERT_EQ(vec_test[5], 5);
    ASSERT_EQ(vec_test[6], 11);
}

TEST(vector_tests, push_back_tests)
{
    mvec::vector<int> vec_source = {1,2,3,4,5,6,7};
    mvec::vector<int> vec_test;
    
    std::sort(vec_source.begin(), vec_source.end(),[](auto& element1, auto& element2)
    {
        return element1 > element2;
    });

    for(auto& element : vec_source)
        vec_test.push_back(element);

    ASSERT_EQ(vec_test, vec_source);
}

TEST(vector_tests, reverse_copy_tests)
{
    mvec::vector<int> vec_source = {1,2,3,4,5,6,7};
    mvec::vector<int> vec_test;
    vec_test.resize(vec_source.size());
    
    std::copy(vec_source.rbegin(), vec_source.rend(), vec_test.begin());

    std::sort(vec_source.begin(), vec_source.end(),[](auto& element1, auto& element2)
    {
        return element1 > element2;
    });

    ASSERT_EQ(vec_test, vec_source);
}



int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}