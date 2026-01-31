#include <iostream>
#include <cmath>
#include "../include/AVLTree.h"
#include "../include/UnicodeHelper.h"

void testBasicOperations()
{
    std::cout << "=== Test 1: Basic Operations ===" << std::endl;
    AVLTree tree;

    tree.insert("كتب");
    tree.insert("درس");
    tree.insert("خرج");

    std::cout << "Tree size: " << tree.size() << std::endl;
    std::cout << "Tree height: " << tree.getHeight() << std::endl;

    std::cout << "\nInorder traversal:" << std::endl;
    tree.inorderTraversal();
    std::cout << std::endl;
}

void testSearch()
{
    std::cout << "=== Test 2: Search Operations ===" << std::endl;
    AVLTree tree;

    tree.insert("كتب");
    tree.insert("درس");
    tree.insert("خرج");

    AVLNode *found = tree.search("درس");
    if (found)
    {
        std::cout << "Found: " << found->root << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }

    AVLNode *notFound = tree.search("علم");
    if (notFound)
    {
        std::cout << "Found: " << notFound->root << std::endl;
    }
    else
    {
        std::cout << "Not found: علم" << std::endl;
    }
    std::cout << std::endl;
}

void testRotations()
{
    std::cout << "=== Test 3: Rotation Cases ===" << std::endl;

    std::cout << "\nLL Rotation (sequential insert):" << std::endl;
    AVLTree tree1;
    tree1.insert("ج");
    tree1.insert("ب");
    tree1.insert("أ");
    std::cout << "Height after LL: " << tree1.getHeight() << std::endl;
    tree1.inorderTraversal();

    std::cout << "\nRR Rotation (sequential insert):" << std::endl;
    AVLTree tree2;
    tree2.insert("أ");
    tree2.insert("ب");
    tree2.insert("ج");
    std::cout << "Height after RR: " << tree2.getHeight() << std::endl;
    tree2.inorderTraversal();

    std::cout << "\nLR Rotation:" << std::endl;
    AVLTree tree3;
    tree3.insert("ج");
    tree3.insert("أ");
    tree3.insert("ب");
    std::cout << "Height after LR: " << tree3.getHeight() << std::endl;
    tree3.inorderTraversal();

    std::cout << "\nRL Rotation:" << std::endl;
    AVLTree tree4;
    tree4.insert("أ");
    tree4.insert("ج");
    tree4.insert("ب");
    std::cout << "Height after RL: " << tree4.getHeight() << std::endl;
    tree4.inorderTraversal();
    std::cout << std::endl;
}

void testDerivedWords()
{
    std::cout << "=== Test 4: Derived Words Tracking ===" << std::endl;
    AVLTree tree;

    tree.insert("كتب");
    AVLNode *node = tree.search("كتب");

    if (node)
    {
        node->addDerivedWord("كاتب");
        node->addDerivedWord("مكتوب");
        node->addDerivedWord("كاتب");

        std::cout << "Root: " << node->root << std::endl;
        std::cout << "Derived words:" << std::endl;
        for (const auto &dw : node->derivedWords)
        {
            std::cout << "  " << dw.word << " (frequency: " << dw.frequency << ")" << std::endl;
        }
    }
    std::cout << std::endl;
}

void testLargeDataset()
{
    std::cout << "=== Test 5: Large Dataset ===" << std::endl;
    AVLTree tree;

    std::string roots[] = {
        "كتب", "درس", "خرج", "علم", "فهم", "قرأ", "سمع", "نظر",
        "ذهب", "جلس", "قام", "نام", "أكل", "شرب", "لعب", "عمل"};

    for (const auto &root : roots)
    {
        tree.insert(root);
    }

    std::cout << "Inserted " << tree.size() << " roots" << std::endl;
    std::cout << "Tree height: " << tree.getHeight() << std::endl;
    std::cout << "Expected max height for balanced tree: ~log2(" << tree.size() << ") = ~" << (int)(std::log2(tree.size()) + 1) << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::cout << "AVL Tree Test Suite" << std::endl;
    std::cout << "===================" << std::endl << std::endl;

    testBasicOperations();
    testSearch();
    testRotations();
    testDerivedWords();
    testLargeDataset();

    std::cout << "All tests completed!" << std::endl;
    return 0;
}
