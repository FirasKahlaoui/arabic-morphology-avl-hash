#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "SchemeEntry.h"
#include <string>
#include <vector>

class HashTable
{
private:
    static const int TABLE_SIZE = 101;
    SchemeEntry **buckets;
    int elementCount;
    int collisionCount;

    int hashFunction(const std::string &key)
    {
        unsigned long hash = 0;
        for (char c : key)
        {
            hash += static_cast<unsigned char>(c);
        }
        return hash % TABLE_SIZE;
    }

public:
    HashTable();
    ~HashTable();

    void insert(const std::string &name, const std::string &pattern);
    SchemeEntry *search(const std::string &name);
    bool remove(const std::string &name);
    bool update(const std::string &name, const std::string &newPattern);
    void display();
    double getLoadFactor();
    int getCollisionCount();
    std::vector<SchemeEntry *> getAllSchemes();
};

#endif
