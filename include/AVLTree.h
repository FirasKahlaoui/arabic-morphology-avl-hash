#ifndef AVLTREE_H
#define AVLTREE_H

#include "AVLNode.h"
#include <string>
#include <algorithm>

class AVLTree
{
private:
    AVLNode *root;

    int getHeight(AVLNode *node)
    {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(AVLNode *node)
    {
        if (node)
        {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    AVLNode *rotateRight(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode *rotateLeft(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode *rotateLeftRight(AVLNode *node)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    AVLNode *rotateRightLeft(AVLNode *node)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    AVLNode *insert(AVLNode *node, const std::string &key);
    AVLNode *search(AVLNode *node, const std::string &key);
    void inorderTraversal(AVLNode *node);
    void clear(AVLNode *node);
    int size(AVLNode *node);

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree()
    {
        clear(root);
    }

    void insert(const std::string &key)
    {
        root = insert(root, key);
    }

    AVLNode *search(const std::string &key)
    {
        return search(root, key);
    }

    void inorderTraversal()
    {
        inorderTraversal(root);
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    int size()
    {
        return size(root);
    }

    int getHeight()
    {
        return getHeight(root);
    }
};

#endif
