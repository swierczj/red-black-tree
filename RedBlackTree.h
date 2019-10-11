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
            RBNode* parent; // changed to raw pointer since children don't manage their parents' lifetime  //std::shared_ptr<RBNode> parent;
            color_t nodeColor;

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
            std::shared_ptr<RBNode> nodePtr( new RBNode(nodeValue) ); // pointer to node which is being added

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
                auto newNodePlace = findNode(key); // find place for node or check if it's already in tree
                if( newNodePlace == sentinel.get() ) // if not found node with such a key
                {
                    auto newNodeParent = getParent(key);

                    if( key > newNodeParent->nodeData.first ) // if node to be added has to be right child
                    {
                        newNodeParent->rightChild = nodePtr;
                        nodePtr->parent = newNodeParent; //std::make_shared<RBNode>(*newNodeParent); <- this one definitely wrong
                        nodePtr->leftChild = nodePtr->rightChild = sentinel;
                    }
                    else if( key < newNodeParent->nodeData.first ) // if node to be added appears to be left child
                    {
                        newNodeParent->leftChild = nodePtr;
                        nodePtr->parent = newNodeParent; //std::make_shared<RBNode>(*newNodeParent); <- this one wrong too
                        nodePtr->leftChild = nodePtr->rightChild = sentinel;
                    }

                    ++treeSize;
                    // TODO: treeRebalance()
                }
            }
        }

        /**
         * Looking for a node in tree with given key, if not found then nullptr is returned.
         * @param key
         * @return pointer to node containing key
         */
        RBNode* findNode( const keyType& key )
        {
            RBNode* temp = root.get();
            
            while( temp && temp != sentinel.get() && temp->nodeData.first != key )
            {
                if( key > temp->nodeData.first )
                    temp = temp->rightChild.get();
                else if( key < temp->nodeData.first )
                    temp = temp->leftChild.get();
            }

            return temp;
        }

        RBNode* getParent( const keyType& key )
        {
            RBNode* childNode = findNode(key);

            if( childNode && childNode != sentinel.get() ) // if given key appears in the tree then return its parent
                return childNode->parent;

            // if childNode is null or sentinel then return the pointer to node which could be its parent
            childNode = root.get(); // use childNode which was null as a temp pointer
            RBNode* parentNode = nullptr;
            while( childNode && childNode != sentinel.get() && childNode->nodeData.first != key )
            {
                parentNode = childNode;
                if( key > childNode->nodeData.first )
                    childNode = childNode->rightChild.get();
                else if( key < childNode->nodeData.first )
                    childNode = childNode->leftChild.get();
            }
            return parentNode; // if tree is empty then child and parent null as returning from func
        }

        void treeRebalance( RBNode* start_node )
        {
            if( start_node->parent->nodeColor == RED ) // if parent of new added node is red
            {
                // this can be changed in future depends on changes in isUncleValid function
                if( isUncleValid(start_node) && getUncleColor(start_node) == RED ) // if uncle exists
                {
                    //if( getUncleColor(start_node) == RED )
                    //{
                        changeEldersColors(start_node); // change colors of parent, grandparent and uncle
                        if( start_node->parent->parent == root.get() ) // if grandparent of start_node is root then give back black color
                            start_node->parent->parent->nodeColor = BLACK;
                        // this else could be redundant, will see since recursive call can be put at the end of whole func
                        else // else if grandparent of new node isn't root
                            treeRebalance(start_node->parent->parent); // check tree correctness starting from grandpa
                    //}

                }
                else if( getUnclePtr(start_node) == sentinel.get() || ( isUncleValid(start_node) && getUncleColor(start_node) == BLACK ) ) // if uncle of new node is phantom or it's black
                {
                    if( start_node == start_node->parent->rightChild && start_node->parent == start_node->parent->parent->leftChild ) // if start_node is right child and its parent is left child
                    {
                        //TODO: rotate_left

                    }
                    else if( start_node == start_node->parent->leftChild && start_node->parent == start_node->parent->parent->rightChild ) // if start_node is left child and its parent is right child
                }
            }
            else // everything is ok

        }

        void rotateLeft( RBNode* node_to_rotate )
        {
            RBNode* temp = node_to_rotate->rightChild;
            if( !temp || temp == sentinel.get() )
                throw std::out_of_range("not valid node");
            //else
            temp->parent = node_to_rotate->parent;
            node_to_rotate->rightChild = temp->leftChild;

            if( node_to_rotate->rightChild && node_to_rotate->rightChild != sentinel ) // if left child of old right child was a proper node
                node_to_rotate->rightChild->parent = node_to_rotate;

            if( isParentValid(node_to_rotate) )
            {
                if( node_to_rotate->parent->leftChild.get == node_to_rotate ) // if param node is left child
                    node_to_rotate->parent->leftChild = temp;
                else // else if param node is right child
                    node_to_rotate->parent->rightChild = temp;
            }

            node_to_rotate->parent = temp;
            temp->leftChild = node_to_rotate;
        }

        void changeEldersColors( RBNode* node )
        {
            !node->parent->nodeColor; // change color of parent
            !node->parent->parent->nodeColor; // change color of grandparent
            auto uncle = getUnclePtr(node);
            !uncle->nodeColor;
        }

        color_t getUncleColor( const RBNode* node )
        {
           //if( !isUncleValid(node) ) isUncleValid checks whether node its parent, grandparent and uncle exist
           // func will be called in program only if isUncleValid result is true
           auto uncle = getUnclePtr(node);
           return uncle->nodeColor;
        }

        RBNode* getUnclePtr( RBNode* node ) // to avoid if else statements about uncle of node
        {
            if( node->parent == node->parent->parent->leftChild ) // if parent of node is left child of grandparent
                return node->parent->parent->rightChild;
            else if( node->parent == node->parent->parent->rightChild )
                return node->parent->parent->leftChild;
        }

        bool isParentValid( RBNode* node )
        {
            if( node )
                return( node->parent && (node->parent != sentinel.get()) );
            // if node is null
            return false;
        }

        bool isGrandParentValid( RBNode* node )
        {
            if( node )
                return( isParentValid(node->parent) );
            // if node is null
            return false;
        }

        bool isUncleValid( RBNode* node )
        {
            if( node )
            {
                if( isGrandParentValid(node) )
                {
                    auto uncle = getUnclePtr(node);
                    return( uncle || uncle != sentinel.get() );
//                    if( node->parent == node->parent->parent->leftChild ) // if parent of param node is left child then check right child of grandparent
//                        return( node->parent->parent->rightChild || node->parent->parent->rightChild != sentinel );
//                    else // if parent of param node is right child
//                        return( node->parent->parent->leftChild || node->parent->parent->leftChild != sentinel );
                }
            }
            // if node is null
            return false;
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

        ~RedBlackTree() { treeSize = 0; } // set tree empty, smart pointers take care of root and sentinel TODO: recursive call deleteTree() or its handled with smart ptrs?

        void test( const keyType& k, const mappedType& m = mappedType() )
        {
            getUncleColor(nullptr);
            //addNode(k,m); // works for adding first node
        }
    };
}

#endif //RBTREE_REDBLACKTREE_H
