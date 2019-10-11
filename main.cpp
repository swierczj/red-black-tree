#include <iostream>
#include "RedBlackTree.h"
#include "RBTreeIterator.h"

int main()
{
    //std::cout << "Hello, World!" << std::endl;
    tree_map::RedBlackTree<int, char> testObj;
    testObj.test(20);
    testObj.test(12);
    testObj.test(25);
    return 0;
}