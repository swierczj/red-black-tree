#ifndef RBTREE_REDBLACKTREE_H
#define RBTREE_REDBLACKTREE_H

#define BLACK 1
#define RED 0

#include <utility>
#include "RBNode.h"

namespace tree_map
{
    template<typename keyType, typename mappedType>
    class RedBlackTree
    {
    public:
        using valueType = std::pair<keyType, mappedType>;
        using unsigned char = color;
    private:
        /*
         * Definition of nested class representing node of tree, hidden implementation needed
         */
        struct RBNode //struct(?)
        {
            valueType nodeData;
            RBNode* rightChild;
            RBNode* leftChild;
            RBNode* parent;
            color nodeColor;

            RBNode( valueType dataPair, RBNode* rightC = nullptr, RBNode* leftC = nullptr, RBNode* pParent = nullptr )
                : nodeData(dataPair), rightChild(rightC), leftChild(leftC), parent(pParent)
            {} //ctor

            RBNode( keyType key, mappedType mapped, RBNode* rightC = nullptr, RBNode* leftC = nullptr, RBNode* pParent = nullptr )
                    : nodeData(std::make_pair(key, mapped)), rightChild(rightC), leftChild(leftC), parent(pParent)
            {} //ctor
        };

        RBNode *root;
        RBNode *sentinel;
        unsigned int treeSize;
//      class test;
//      RBTreeIterator<keyType, mappedType> iterator;
//      RBTreeConstIterator<keyType, mappedType> constIterator;

    };
}

#endif //RBTREE_REDBLACKTREE_H
