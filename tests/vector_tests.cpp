#include <gtest/gtest.h>
#include <vector>
#include "test_counter.h"

// 1. Container creation
TEST(VectorTest, DefaultConstructor)
{
    std::vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, ConstructorWithSize)
{
    std::vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(v[i], 0);
}

// 2. Insert elements at the end
TEST(VectorTest, PushBack)
{
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

// 3. Insert elements at the beginning
TEST(VectorTest, InsertBegin)
{
    std::vector<int> v = {20, 30};
    v.insert(v.begin(), 10);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
}

// 4. Insert elements at the middle
TEST(VectorTest, InsertMiddle)
{
    std::vector<int> v = {10, 40};
    auto it = v.begin() + 1;
    v.insert(it, 20);
    v.insert(v.begin() + 2, 30);
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 30);
    EXPECT_EQ(v[3], 40);
}

// 5. Remove elements from the end
TEST(VectorTest, PopBack)
{
    std::vector<int> v = {10, 20, 30};
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
}

// 6. Remove elemnts from the beginning
TEST(VectorTest, EraseBegin)
{
    std::vector<int> v = {10, 20, 30};
    v.erase(v.begin());
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 20);
    EXPECT_EQ(v[1], 30);
}

// 7. Remove elements from the middle
TEST(VectorTest, EraseMiddle)
{
    std::vector<int> v = {10, 20, 30, 40};
    auto it = v.begin() + 2;
    v.erase(it);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[1], 20);
    EXPECT_EQ(v[2], 40);
}

// 8. Access elements from the container
TEST(VectorTest, AccessElements)
{
    std::vector<int> v = {100, 200, 300};
    EXPECT_EQ(v.at(0), 100);
    EXPECT_EQ(v.at(1), 200);
    EXPECT_EQ(v.front(), 100);
    EXPECT_EQ(v.back(), 300);
}

// 9. Get container size (actual number of elements)
TEST(VectorTest, Size)
{
    std::vector<int> v;
    EXPECT_EQ(v.size(), 0);
    v.push_back(1);
    EXPECT_EQ(v.size(), 1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.size(), 3);
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
}

// 10. Check empty container behavior
TEST(VectorTest, EmptyContainer)
{
    std::vector<int> v;
    EXPECT_TRUE(v.empty());
    v.push_back(42);
    EXPECT_FALSE(v.empty());
    v.pop_back();
    EXPECT_TRUE(v.empty());
}

// 11. Copy container
TEST(VectorTest, CopyConstructor)
{
    std::vector<int> original = {10, 20, 30, 40, 50};
    std::vector<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());
    for (size_t i = 0; i < original.size(); ++i)
        EXPECT_EQ(copy[i], original[i]);

    original[0] = 999;
    EXPECT_EQ(copy[0], 10);

    copy[1] = 888;
    EXPECT_EQ(original[1], 20);
}

// 12. Copy assignment operator
TEST(VectorTest, CopyAssignmentOperator)
{
    std::vector<int> original = {100, 200, 300};
    std::vector<int> copy;
    copy = original;

    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy[0], 100);
    EXPECT_EQ(copy[1], 200);
    EXPECT_EQ(copy[2], 300);

    original[1] = 999;
    EXPECT_EQ(copy[1], 200);
}

// 13. Copy assignment with existing data
TEST(VectorTest, CopyAssignmentWithExistingData)
{
    std::vector<int> original = {1, 2, 3};

    std::vector<int> copy = {10, 20, 30, 40, 50};

    copy = original;

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);

    EXPECT_EQ(original.size(), 3);
    EXPECT_EQ(original[0], 1);
    EXPECT_EQ(original[1], 2);
    EXPECT_EQ(original[2], 3);
}

// DESTRUCTOR TESTS

// Fixture for destructor tests
class VectorDestructorTests : public ::testing::Test
{
protected:
    void SetUp() override { TestCounter::reset_counts(); }
    void TearDown() override { EXPECT_EQ(TestCounter::get_alive(), 0); }
};

// 1. Destructor called on clear()
TEST_F(VectorDestructorTests, Clear)
{
    std::vector<TestCounter> v;
    v.reserve(3);
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);

    EXPECT_EQ(TestCounter::get_alive(), 3);

    v.clear();

    EXPECT_EQ(TestCounter::get_alive(), 0);
    EXPECT_EQ(TestCounter::get_destructor(), 3);
}

// 2. Destructor called on pop_back()
TEST_F(VectorDestructorTests, PopBack)
{
    std::vector<TestCounter> v;
     v.reserve(3);
    v.emplace_back(10);
    v.emplace_back(20);
    v.emplace_back(30);

    EXPECT_EQ(TestCounter::get_alive(), 3);

    v.pop_back();

    EXPECT_EQ(TestCounter::get_destructor(), 1);
    EXPECT_EQ(TestCounter::get_alive(), 2);
}

// 3. Destructor called on erase()
TEST_F(VectorDestructorTests, Erase)
{
    std::vector<TestCounter> v;
    v.reserve(4);
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    v.emplace_back(4);

    EXPECT_EQ(TestCounter::get_alive(), 4);

    v.erase(v.begin() + 2);

    EXPECT_EQ(TestCounter::get_destructor(), 1);
    EXPECT_EQ(TestCounter::get_alive(), 3);
}

// 4. Destructor called on resize() to smaller
TEST_F(VectorDestructorTests, ResizeSmaller)
{
    std::vector<TestCounter> v;
    v.reserve(5);
    for (int i = 1; i <= 5; ++i)
        v.emplace_back(i);

    EXPECT_EQ(TestCounter::get_alive(), 5);

    v.resize(2);

    EXPECT_EQ(TestCounter::get_alive(), 2);
    EXPECT_EQ(TestCounter::get_destructor(), 3);
}

// 5. Destructor called when vector goes out of scope
TEST_F(VectorDestructorTests, OutOfScope)
{
    {
        std::vector<TestCounter> v;
        v.reserve(2);
        v.emplace_back(100);
        v.emplace_back(200);

        EXPECT_EQ(TestCounter::get_alive(), 2);
    }

    EXPECT_EQ(TestCounter::get_alive(), 0);
    EXPECT_EQ(TestCounter::get_destructor(), 2);
}