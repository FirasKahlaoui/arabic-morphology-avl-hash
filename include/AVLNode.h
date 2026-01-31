#ifndef AVLNODE_H
#define AVLNODE_H

#include <string>
#include <vector>

struct DerivedWord
{
    std::string word;
    int frequency;

    DerivedWord(const std::string &w, int freq = 1) : word(w), frequency(freq) {}
};

struct AVLNode
{
    std::string root;
    int height;
    AVLNode *left;
    AVLNode *right;
    std::vector<DerivedWord> derivedWords;

    AVLNode(const std::string &rootValue)
        : root(rootValue), height(1), left(nullptr), right(nullptr) {}

    ~AVLNode()
    {
        delete left;
        delete right;
    }

    void addDerivedWord(const std::string &word)
    {
        for (auto &dw : derivedWords)
        {
            if (dw.word == word)
            {
                dw.frequency++;
                return;
            }
        }
        derivedWords.push_back(DerivedWord(word));
    }
};

#endif
