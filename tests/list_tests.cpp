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

// 11. Copy container
TEST(ListTest, CopyConstructor)
{
    std::list<int> original = {10, 20, 30, 40, 50};
    std::list<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());

    auto it_orig = original.begin();
    auto it_copy = copy.begin();
    while (it_orig != original.end() && it_copy != copy.end())
    {
        EXPECT_EQ(*it_copy, *it_orig);
        ++it_orig;
        ++it_copy;
    }

    *original.begin() = 999;
    EXPECT_EQ(*copy.begin(), 10);

    auto it_copy_second = copy.begin();
    ++it_copy_second;
    *it_copy_second = 888;

    auto  it_orig_second = original.begin();
    ++it_orig_second;
    EXPECT_EQ(*it_orig_second, 20);
}

// 12. Copy assignment operator
TEST(ListTest, CopyAssignmentOperator)
{
    std::list<int> original = {100, 200, 300};

    std::list<int> copy;
    copy= original;

    EXPECT_EQ(copy.size(), original.size());

    auto it_orig = original.begin();
    auto it_copy = copy.begin();
    EXPECT_EQ(*it_copy, 100);
    ++it_copy;
    ++it_orig;
    EXPECT_EQ(*it_copy, 200);
    ++it_copy;
    ++it_orig;
    EXPECT_EQ(*it_copy, 300);

    auto it_orig_second = original.begin();
    ++it_orig_second;
    *it_orig_second = 999;

    auto it_copy_second = copy.begin();
    ++it_copy_second;
    EXPECT_EQ(*it_copy_second, 200);
}

// 13. Copy assignment with existing data
TEST(ListTest, CopyAssignmentWithExistingData)
{
    std::list<int> original = {1, 2, 3};

    std::list<int> copy = {10, 20, 30, 40, 50};

    copy = original;

    EXPECT_EQ(copy.size(), 3);

    auto it_copy = copy.begin();
    EXPECT_EQ(*it_copy, 1); ++it_copy;
    EXPECT_EQ(*it_copy, 2); ++it_copy;
    EXPECT_EQ(*it_copy, 3); ++it_copy;

    EXPECT_EQ(original.size(), 3);
    auto it_orig = original.begin();
    EXPECT_EQ(*it_orig, 1);
}