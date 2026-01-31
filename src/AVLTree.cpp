#include "AVLTree.h"
#include <iostream>

AVLNode *AVLTree::insert(AVLNode *node, const std::string &key)
{
    if (!node)
    {
        return new AVLNode(key);
    }

    if (key < node->root)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->root)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        return node;
    }

    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->root)
    {
        return rotateRight(node);
    }

    if (balance < -1 && key > node->right->root)
    {
        return rotateLeft(node);
    }

    if (balance > 1 && key > node->left->root)
    {
        return rotateLeftRight(node);
    }

    if (balance < -1 && key < node->right->root)
    {
        return rotateRightLeft(node);
    }

    return node;
}

AVLNode *AVLTree::search(AVLNode *node, const std::string &key)
{
    if (!node || node->root == key)
    {
        return node;
    }

    if (key < node->root)
    {
        return search(node->left, key);
    }

    return search(node->right, key);
}

void AVLTree::inorderTraversal(AVLNode *node)
{
    if (node)
    {
        inorderTraversal(node->left);
        std::cout << node->root << " (height: " << node->height << ")" << std::endl;
        inorderTraversal(node->right);
    }
}

void AVLTree::clear(AVLNode *node)
{
    if (node)
    {
        clear(node->left);
        clear(node->right);
        node->left = nullptr;
        node->right = nullptr;
        delete node;
    }
}

int AVLTree::size(AVLNode *node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + size(node->left) + size(node->right);
}
