#include <gtest/gtest.h>
#include <vector>

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

