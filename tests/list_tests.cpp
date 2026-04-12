#include <gtest/gtest.h>
#include <list>

// 1. Container creation
TEST(ListTest, DefaultConstructor)
{
    std::list<int> l;
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, ConstructorWithSize)
{
    std::list<int> l(5);
    EXPECT_EQ(l.size(), 5);
    for (int val : l)
        EXPECT_EQ(val, 0);
}

// 2. Insert elements at the end
TEST(ListTest, PushBack)
{
    std::list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    EXPECT_EQ(l.size(), 3);
    auto it = l.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

// 3. Insert elements at the beginning
TEST(ListTest, PushFront)
{
    std::list<int> l;
    l.push_front(30);
    l.push_front(20);
    l.push_front(10);
    EXPECT_EQ(l.size(), 3);
    auto it = l.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

// 4. Insert elements in the middle
TEST(ListTest, InsertMiddle)
{
    std::list<int> l = {10, 40};
    auto it = l.begin();
    ++it;
    l.insert(it, 20);
    l.insert(it, 30);
    EXPECT_EQ(l.size(), 4);
    auto check = l.begin();
    EXPECT_EQ(*check, 10);
    ++check;
    EXPECT_EQ(*check, 20);
    ++check;
    EXPECT_EQ(*check, 30);
    ++check;
    EXPECT_EQ(*check, 40);
}

// 5. Remove elements from the end
TEST(ListTest, PopBack)
{
    std::list<int> l = {10, 20, 30};
    l.pop_back();
    EXPECT_EQ(l.size(), 2);
    auto it = l.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
}

// 6. Remove elements from the beginning
TEST(ListTest, PopFront)
{
    std::list<int> l = {10, 20, 30};
    l.pop_front();
    EXPECT_EQ(l.size(), 2);
    auto it = l.begin();
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

// 7. Remove elements from the middle
TEST(ListTest, EraseMiddle)
{
    std::list<int> l = {10, 20, 30, 40};
    auto it = l.begin();
    ++it;
    ++it;
    l.erase(it);
    EXPECT_EQ(l.size(), 3);
    auto check = l.begin();
    EXPECT_EQ(*check, 10);
    ++check;
    EXPECT_EQ(*check, 20);
    ++check;
    EXPECT_EQ(*check, 40);
}

// 8. Access elements from the container
TEST(ListTest, AccessElements)
{
    std::list<int> l = {100, 200, 300};
    EXPECT_EQ(l.front(), 100);
    EXPECT_EQ(l.back(), 300);
    auto it = l.begin();
    EXPECT_EQ(*it, 100);
    ++it;
    EXPECT_EQ(*it, 200);
    ++it;
    EXPECT_EQ(*it, 300);
}

// 9. Get container size (actual number of elements)
TEST(ListTest, Size)
{
    std::list<int> l;
    EXPECT_EQ(l.size(), 0);
    l.push_back(1);
    EXPECT_EQ(l.size(), 1);
    l.push_back(2);
    l.push_back(3);
    EXPECT_EQ(l.size(), 3);
    l.pop_back();
    EXPECT_EQ(l.size(), 2);
}

// 10. Check empty container behavior
TEST(ListTest, EmptyContainer)
{
    std::list<int> l;
    EXPECT_TRUE(l.empty());
    l.push_back(42);
    EXPECT_FALSE(l.empty());
    l.pop_back();
    EXPECT_TRUE(l.empty());
}