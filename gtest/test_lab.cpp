#include <gtest/gtest.h>
#include "BinaryTree.hpp"
#include "KnightTourBoard.hpp"
#include "Player.hpp"

//bst tests
TEST(bstTest, simpleAddElements)
{
    BinaryTree<int> list(BinaryTree<int>::TreeType::BST);
    for(int i = 0; i < 3; i++)
        list.insert(i);
    
    EXPECT_EQ(list.findMin(),0);
    EXPECT_EQ(list.getHeight(),2);
}

TEST(bstTest, complexAddElements)
{
    BinaryTree<int> list(BinaryTree<int>::TreeType::BST);
    for(int i = 0; i < 100; i++)
        list.insert(i);
    
    EXPECT_EQ(list.findMin(),0);
    EXPECT_EQ(list.getHeight(),100);
}

//llrb tests
TEST(llrbTest, simpleAddElements)
{
    BinaryTree<int> list(BinaryTree<int>::TreeType::LLRB);
    for(int i = 0; i < 3; i++)
        list.insert(i);
    
    EXPECT_EQ(list.findMin(),0);
    EXPECT_EQ(list.getHeight(),2);
}

TEST(llrbTest, complexAddElements)
{
    BinaryTree<int> list(BinaryTree<int>::TreeType::LLRB);
    for(int i = 0; i < 100; i++)
        list.insert(i);
    
    EXPECT_EQ(list.findMin(),0);
    EXPECT_EQ(list.getHeight(),7);  //log2(100) = 6.5
}


