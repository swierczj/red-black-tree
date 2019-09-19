#ifndef RBTREE_REDBLACKTREE_H
#define RBTREE_REDBLACKTREE_H

#define BLACK 1
#define RED 0

#include <utility>
#include <bits/unique_ptr.h>
#include <bits/shared_ptr.h>
#include "RBNode.h"

namespace tree_map
{
    template<typename keyType, typename mappedType>
    class RedBlackTree
    {
    public:
        using valueType = std::pair<keyType, mappedType>;
        enum Color{ RED, BLACK };
        // using unsigned char = color; //its wrong, look on the enum
    private:
        /*
         * Definition of nested class representing node of tree, hidden implementation needed
         */
        struct RBNode //struct(?)
        {
            valueType nodeData;
            std::unique_ptr<RBNode> rightChild;
            std::unique_ptr<RBNode> leftChild;
            std::shared_ptr<RBNode> parent; // changed raw pointers to smart pointers
            Color nodeColor; //added enum

            RBNode( valueType dataPair = std::make_pair( keyType(), mappedType() ), RBNode* rightC = nullptr, RBNode* leftC = nullptr, RBNode* pParent = nullptr )
                    : nodeData(dataPair), rightChild(rightC), leftChild(leftC), parent(pParent), nodeColor(RED)
            {} // def ctor with no args

            RBNode( keyType key = keyType(), mappedType mapped = mappedType(), RBNode* rightC = nullptr, RBNode* leftC = nullptr, RBNode* pParent = nullptr )
                    : nodeData(std::make_pair(key, mapped)), rightChild(rightC), leftChild(leftC), parent(pParent), nodeColor(RED)
            {} // ctor with no args so maybe ambiguous and should be deleted(?)

            RBNode( valueType dataPair, RBNode* rightC = nullptr, RBNode* leftC = nullptr, RBNode* pParent = nullptr )
                : nodeData(dataPair), rightChild(rightC), leftChild(leftC), parent(pParent), nodeColor(RED)
            {} //ctor

            RBNode( keyType key, mappedType mapped, RBNode* rightC = nullptr, RBNode* leftC = nullptr, RBNode* pParent = nullptr )
                    : nodeData(std::make_pair(key, mapped)), rightChild(rightC), leftChild(leftC), parent(pParent), nodeColor(RED)
            {} //ctor with making pair from key and mapped value
        }; // RBNode

        std::unique_ptr<RBNode> root;
        std::unique_ptr<RBNode> sentinel;
        unsigned int treeSize;
//      class test;
//      RBTreeIterator<keyType, mappedType> iterator;
//      RBTreeConstIterator<keyType, mappedType> constIterator;

    };
}

#endif //RBTREE_REDBLACKTREE_H
