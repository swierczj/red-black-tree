#ifndef RBTREE_REDBLACKTREE_H
#define RBTREE_REDBLACKTREE_H

#include <utility>
#include "RBNode.h"

namespace tree_map
{
    template<typename keyType, typename mappedType>
    class RedBlackTree
    {
        using valueType = std::pair<keyType, mappedType>;

        RBNode<keyType, mappedType> *root;
        unsigned int treeSize;
        class test;
//      RBTreeIterator<keyType, mappedType> iterator;
//      RBTreeConstIterator<keyType, mappedType> constIterator;

    };

    template<typename keyType, typename mappedType>
    class test
    {
    private:
        int data;
    public:
        test() : data(9) {}
        int getData() { return data; }
    };
}

#endif //RBTREE_REDBLACKTREE_H
