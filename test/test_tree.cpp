#include <gtest/gtest.h>
#include "tree.h"
#include <string>

TEST(Tree, constructor)
{
    EXPECT_NO_THROW((Tree<int, double>()));
}

TEST(Tree, insert)
{
    Tree<int, double> t;
    EXPECT_NO_THROW(t.insert(1, 1.0));
    EXPECT_EQ(t.findNodeByPos(0)->data.val, 1.0);
    EXPECT_EQ(t.findNodeByPos(0)->data.key, 1);
}
TEST(Tree, insert_throw_if_key_isnot_unique)
{
    Tree<int, double> t;
    t.insert(1, 2.0);
    EXPECT_ANY_THROW(t.insert(1, 1.0));
}
TEST(Tree, remove)
{
    Tree<int, double> t;
    t.insert(1, 1.0);
    EXPECT_NO_THROW(t.remove(1));
}

// дописать проверку удаления с разными случаями

TEST(Tree, remove_throw_if_key_isnot_in_map)
{
    Tree<int, double> t;
    t.insert(1, 1.0);
    EXPECT_ANY_THROW(t.remove(2));
}
TEST(Tree, search_and_search_elem)
{
    Tree<int, double> t;
    t.insert(1, 1.0);
    t.insert(2, 2.0);
    t.insert(3, 3.0);

    EXPECT_EQ(t.search(2), true);

    EXPECT_EQ(t.search(4), false);

    EXPECT_EQ(t.search_elem(2), 2.0);
    EXPECT_ANY_THROW(t.search_elem(4));
}
TEST(Tree, remove_with_1_kids)
{
    Tree<int, double> t;
    t.insert(4, 4.0);
    t.insert(6, 6.0);
    t.insert(3, 3.0);
    t.insert(2, 2.0);
    t.insert(1, 1.0);
    t.insert(5, 5.0);
    t.insert(7, 7.0);
    //t.printTree(t.GetHead());
    EXPECT_NO_THROW(t.remove(2));
    //t.printTree(t.GetHead()); 
}
TEST(Tree, remove_with_2_kids)
{
    Tree<int, double> t;
    t.insert(4, 4.0);
    t.insert(6, 6.0);
    t.insert(3, 3.0);
    t.insert(2, 2.0);
    t.insert(1, 1.0);
    t.insert(5, 5.0);
    t.insert(7, 7.0);
    //t.printTree(t.GetHead());
    EXPECT_NO_THROW(t.remove(6));
    //t.printTree(t.GetHead()); 
}
TEST(Tree, remove_head)
{
    Tree<int, double> t;
    t.insert(4, 4.0);
    t.insert(6, 6.0);
    t.insert(3, 3.0);
    t.insert(2, 2.0);
    t.insert(1, 1.0);
    t.insert(5, 5.0);
    t.insert(7, 7.0);
    t.printTree(t.GetHead());
    EXPECT_NO_THROW(t.remove(4));
    t.printTree(t.GetHead()); 
}
TEST(GoogleTestCheck, IsWorking)
{
    EXPECT_TRUE(true);
    EXPECT_EQ(2 + 2, 4);
}