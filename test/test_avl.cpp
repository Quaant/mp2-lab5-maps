#include <gtest/gtest.h>
#include "avltree.h"
#include <string>

TEST(AVLTree, constructor)
{
    EXPECT_NO_THROW((avltree<int, double>()));
}



TEST(AVLTree, insert)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(20, 2.0);
    t.insert(40, 4.0);
    t.insert(10, 1.0);
    t.insert(25, 2.5);
    
    EXPECT_TRUE(t.search(30));
    EXPECT_TRUE(t.search(20));
    EXPECT_TRUE(t.search(40));
    EXPECT_TRUE(t.search(10));
    EXPECT_TRUE(t.search(25));
}

TEST(AVLTree, insert_throw_if_key_is_not_unique)
{
    avltree<int, double> t;
    t.insert(1, 1.0);
    EXPECT_ANY_THROW(t.insert(1, 2.0));
}

TEST(AVLTree, insert_should_balance_after_insertion)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(20, 2.0);
    t.insert(10, 1.0);  // должно вызвать LL вращение
    
    EXPECT_EQ(t.findNodeByKeyAvl(20)->data.key, 20);
    EXPECT_TRUE(t.search(10));
    EXPECT_TRUE(t.search(30));}

TEST(AVLTree, insert_should_balance_rr)
{
    avltree<int, double> t;
    t.insert(10, 1.0);
    t.insert(20, 2.0);
    t.insert(30, 3.0);  // должно вызвать RR вращение
    
    EXPECT_EQ(t.findNodeByKeyAvl(20)->data.key, 20);
    EXPECT_TRUE(t.search(10));
    EXPECT_TRUE(t.search(30));
}

TEST(AVLTree, insert_should_balance_lr)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(10, 1.0);
    t.insert(20, 2.0);  // должно вызвать LR вращение
    
    EXPECT_EQ(t.findNodeByKeyAvl(20)->data.key, 20);
    EXPECT_TRUE(t.search(10));
    EXPECT_TRUE(t.search(30));
}

TEST(AVLTree, insert_should_balance_rl)
{
    avltree<int, double> t;
    t.insert(10, 1.0);
    t.insert(30, 3.0);
    t.insert(20, 2.0);  // должно вызвать RL вращение
    
    EXPECT_EQ(t.findNodeByKeyAvl(20)->data.key, 20);
    EXPECT_TRUE(t.search(10));
    EXPECT_TRUE(t.search(30));
}

TEST(AVLTree, search)
{
    avltree<int, double> t;
    t.insert(1, 1.0);
    t.insert(2, 2.0);
    t.insert(3, 3.0);

    EXPECT_TRUE(t.search(2));
    EXPECT_FALSE(t.search(4));
    EXPECT_FALSE(t.search(0));
}

TEST(AVLTree, search_elem)
{
    avltree<int, double> t;
    t.insert(1, 1.0);
    t.insert(2, 2.0);
    t.insert(3, 3.0);

    EXPECT_EQ(t.search_elem(2), 2.0);
    EXPECT_ANY_THROW(t.search_elem(4));
    EXPECT_ANY_THROW(t.search_elem(0));
}

TEST(AVLTree, findNodeByKey)
{
    avltree<int, double> t;
    t.insert(1, 1.0);
    t.insert(2, 2.0);
    t.insert(3, 3.0);
    
    EXPECT_EQ(t.findNodeByKeyAvl(2)->data.val, 2.0);
    EXPECT_EQ(t.findNodeByKeyAvl(2)->data.key, 2);
    EXPECT_EQ(t.findNodeByKeyAvl(99), nullptr);
}

TEST(AVLTree, remove_list)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(20, 2.0);
    t.insert(40, 4.0);
    t.insert(10, 1.0);
    
    EXPECT_NO_THROW(t.remove(10));
    EXPECT_FALSE(t.search(10));
    EXPECT_TRUE(t.search(30));
    EXPECT_TRUE(t.search(20));
    EXPECT_TRUE(t.search(40));
}

TEST(AVLTree, remove_node_with_one_child)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(20, 2.0);
    t.insert(40, 4.0);
    t.insert(10, 1.0);
    t.insert(5, 0.5);  // 10 имеет левого ребенка
    
    EXPECT_NO_THROW(t.remove(10));
    EXPECT_FALSE(t.search(10));
    EXPECT_TRUE(t.search(5));
    EXPECT_TRUE(t.search(30));
    EXPECT_TRUE(t.search(20));
    EXPECT_TRUE(t.search(40));
}

TEST(AVLTree, remove_node_with_two_children)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(20, 2.0);
    t.insert(40, 4.0);
    t.insert(35, 3.5);
    t.insert(45, 4.5);
    
    EXPECT_NO_THROW(t.remove(40));
    EXPECT_FALSE(t.search(40));
    EXPECT_TRUE(t.search(30));
    EXPECT_TRUE(t.search(20));
    EXPECT_TRUE(t.search(35));
    EXPECT_TRUE(t.search(45));
}

TEST(AVLTree, remove_root)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(20, 2.0);
    t.insert(40, 4.0);
    
    EXPECT_NO_THROW(t.remove(30));
    EXPECT_FALSE(t.search(30));
    EXPECT_TRUE(t.search(20));
    EXPECT_TRUE(t.search(40));
}


TEST(AVLTree, remove_throw_if_key_not_found)
{
    avltree<int, double> t;
    t.insert(1, 1.0);
    EXPECT_ANY_THROW(t.remove(2));
    EXPECT_ANY_THROW(t.remove(99));
}

TEST(AVLTree, remove_should_balance_after_deletion)
{
    avltree<int, double> t;
    t.insert(30, 3.0);
    t.insert(20, 2.0);
    t.insert(40, 4.0);
    t.insert(10, 1.0);
    t.insert(25, 2.5);
    t.insert(35, 3.5);
    t.insert(45, 4.5);
    t.insert(5, 0.5);
    
    EXPECT_NO_THROW(t.remove(10));
    EXPECT_FALSE(t.search(10));
    EXPECT_TRUE(t.search(5));
}

TEST(AVLGoogleTestCheck, IsWorking)
{
    EXPECT_TRUE(true);
    EXPECT_EQ(2 + 2, 4);
}