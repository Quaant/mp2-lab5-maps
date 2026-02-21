#include <gtest/gtest.h>
#include "order-map.h"
#include "unorder-map.h"
#include <string>

// poisk vstavka udalenie

// ostalos search and check sorted in orderMap

// ORDER MAP TESTS

TEST(orderMap, constructor)
{
    ASSERT_NO_THROW((orderMap<int, double>()));
}

TEST(orderMap, insert)
{
    orderMap<int, double> map;

    ASSERT_NO_THROW(map.insert(1, 1.0));
    EXPECT_EQ(map[0].val, 1.0);
    EXPECT_EQ(map[0].key, 1);
}
TEST(orderMap, insert_throw_if_key_isnot_unique)
{
    orderMap<int, double> map;
    map.insert(1, 2.0);
    EXPECT_ANY_THROW(map.insert(1, 1.0));
    map.print();
}
TEST(orderMap, remove)
{
    orderMap<int, double> map;
    map.insert(1, 1.0);
    EXPECT_NO_THROW(map.remove(1));
}

TEST(orderMap, remove_throw_if_key_isnot_in_map)
{
    orderMap<int, double> map;
    map.insert(1, 1.0);
    EXPECT_ANY_THROW(map.remove(2));
}

TEST(orderMap, search_and_search_elem)
{
    orderMap<int, double> map;
    map.insert(1, 1.0);
    map.insert(2, 2.0);
    map.insert(3, 3.0);

    EXPECT_EQ(map.search(2), true);
    EXPECT_EQ(map.search(4), false);
    EXPECT_EQ(map.search_elem(2), 2.0);
    EXPECT_ANY_THROW(map.search_elem(4));
}

TEST(orderMap, check_sorted)
{
    orderMap<int, double> map;
    map.insert(2, 2.0);
    map.insert(3, 3.0);
    map.insert(1, 1.0);

    EXPECT_EQ(map[0].val, 1.0);
    EXPECT_EQ(map[1].val, 2.0);
    EXPECT_EQ(map[2].val, 3.0);
}
TEST(orderMap, simple_test)
{
    orderMap<int, double> map;
    ASSERT_NO_THROW(map.insert(1, 1.0)); // (vrode fix) problema v binsearch

    ASSERT_NO_THROW(map.search(1));
    ASSERT_NO_THROW(map.remove(1));
}

// UNORDER MAP TESTS

TEST(unorderMap, constructor)
{
    ASSERT_NO_THROW((unorderMap<int, double>()));
}

TEST(unorderMap, insert)
{
    unorderMap<int, double> map;
    ASSERT_NO_THROW(map.insert(1, 1.0));
    EXPECT_EQ(map[0].val, 1.0);
    EXPECT_EQ(map[0].key, 1);
}

TEST(unorderMap, insert_throw_if_key_isnot_unique)
{
    unorderMap<int, double> map;
    map.insert(1, 2.0);
    EXPECT_ANY_THROW(map.insert(1, 1.0));
    map.print();
}

TEST(unorderMap, remove)
{
    unorderMap<int, double> map;
    map.insert(1, 1.0);
    EXPECT_NO_THROW(map.remove(1));
    map.print();
}

TEST(unorderMap, remove_throw_if_key_isnot_in_map)
{
    unorderMap<int, double> map;
    map.insert(1, 1.0);
    EXPECT_ANY_THROW(map.remove(2));
}
TEST(unorderMap, search_and_search_elem)
{
    orderMap<int, double> map;
    map.insert(1, 1.0);
    map.insert(2, 2.0);
    map.insert(3, 3.0);

    EXPECT_EQ(map.search(2), true);
    EXPECT_EQ(map.search(4), false);

    EXPECT_EQ(map.search_elem(2), 2.0);
    EXPECT_ANY_THROW(map.search_elem(4));
}

TEST(unorderMap, simple_test)
{
    unorderMap<int, double> map;
    ASSERT_NO_THROW(map.insert(1, 1.0));
    map.print();
    ASSERT_NO_THROW(map.search(1));
    ASSERT_NO_THROW(map.remove(1));
    map.print();
}

TEST(GoogleTestCheck, IsWorking)
{
    EXPECT_TRUE(true);
    EXPECT_EQ(2 + 2, 4);
}