#ifndef RBTREE_REDBLACKTREE_H
#define RBTREE_REDBLACKTREE_H

#include <utility>
#include <memory>
//#include <bits/unique_ptr.h>
//#include <bits/shared_ptr.h>
//#include "RBNode.h"

namespace tree_map
{
    template<typename keyType, typename mappedType>
    class RedBlackTree
    {
    public:
        using valueType = std::pair<keyType, mappedType>;
        //enum color_t { RED = 0, BLACK };
    private:
        /*
         * Definition of nested class representing node of tree, hidden implementation needed
         */
        enum color_t { RED = 0, BLACK };
        struct RBNode
        {
            valueType nodeData;
            std::shared_ptr<RBNode> rightChild; // unique ptrs changed to shared ptrs due to recursive algorithms
            std::shared_ptr<RBNode> leftChild;
            std::shared_ptr<RBNode> parent; // changed raw pointers to smart pointers
            color_t nodeColor; //added enum

            explicit RBNode( valueType dataPair = std::make_pair( keyType(), mappedType() ), RBNode* rightC = nullptr, RBNode* leftC = nullptr, RBNode* pParent = nullptr )
                : nodeData(dataPair), rightChild(rightC), leftChild(leftC), parent(pParent), nodeColor(RED)
            {} // def ctor
        }; // RBNode

        std::shared_ptr<RBNode> root;
        std::shared_ptr<RBNode> sentinel;
        unsigned int treeSize;
//      class test;
//      RBTreeIterator<keyType, mappedType> iterator;
//      RBTreeConstIterator<keyType, mappedType> constIterator;
        void addNode( const keyType& key, const mappedType& mapped = mappedType() /*const valueType& node_data = std::make_pair( keyType(), mappedType() )*/ )
        {
            auto nodeValue = std::make_pair(key, mapped);
            std::shared_ptr<RBNode> nodePtr( new RBNode(nodeValue) );

            if(!root) // if tree's empty
            {
                root = nodePtr;
                nodePtr->leftChild = sentinel;
                nodePtr->rightChild = sentinel;
                nodePtr->nodeColor = BLACK;
                ++treeSize;
            }
            else
            {
                auto newNodePlace = findNode(key);
            }
        }

        /**
         * Looking for a node in tree with given key, if not found then nullptr is returned.
         * @param key
         * @return pointer to node containing key
         */
        RBNode* findNode( const keyType& key )
        {
            RBNode* temp = root;
            
            while( temp || temp != sentinel )
            {
                if( key > temp->nodeData.first )
                    temp = temp->rightChild;
                else if( key < temp->nodeData.first )
                    temp = temp->leftChild;
            }

            return temp;
        }
    public:
        RedBlackTree()
            : root(nullptr), sentinel( new RBNode() ), treeSize(0)
        {
//          sentinel -> rightChild = std::move(sentinel);
//          sentinel -> leftChild = std::move(sentinel);
//            if( sentinel -> parent == nullptr )
//                std::cout << "test";
            sentinel -> nodeColor = BLACK;
        }

        ~RedBlackTree() { treeSize = 0; } // set tree empty, smart pointers take care of root and sentinel TODO: recursive call deleteTree()

        void test( const keyType& k, const mappedType& m = mappedType() )
        {
            addNode(k,m); // works for adding first node
        }

        //void addNode
    };
}

#endif //RBTREE_REDBLACKTREE_H
