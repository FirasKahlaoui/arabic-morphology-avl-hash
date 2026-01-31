#include "HashTable.h"
#include <iostream>

HashTable::HashTable() : elementCount(0), collisionCount(0)
{
    buckets = new SchemeEntry *[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        buckets[i] = nullptr;
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        delete buckets[i];
    }
    delete[] buckets;
}

void HashTable::insert(const std::string &name, const std::string &pattern)
{
    int index = hashFunction(name);

    if (buckets[index] != nullptr)
    {
        collisionCount++;
    }

    SchemeEntry *newEntry = new SchemeEntry(name, pattern);
    newEntry->next = buckets[index];
    buckets[index] = newEntry;
    elementCount++;
}

SchemeEntry *HashTable::search(const std::string &name)
{
    int index = hashFunction(name);
    SchemeEntry *current = buckets[index];

    while (current != nullptr)
    {
        if (current->name == name)
        {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

bool HashTable::remove(const std::string &name)
{
    int index = hashFunction(name);
    SchemeEntry *current = buckets[index];
    SchemeEntry *prev = nullptr;

    while (current != nullptr)
    {
        if (current->name == name)
        {
            if (prev == nullptr)
            {
                buckets[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            current->next = nullptr;
            delete current;
            elementCount--;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false;
}

bool HashTable::update(const std::string &name, const std::string &newPattern)
{
    SchemeEntry *entry = search(name);
    if (entry)
    {
        entry->pattern = newPattern;
        return true;
    }
    return false;
}

void HashTable::display()
{
    std::cout << "Hash Table Contents:" << std::endl;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (buckets[i] != nullptr)
        {
            std::cout << "Bucket " << i << ": ";
            SchemeEntry *current = buckets[i];
            while (current != nullptr)
            {
                std::cout << "[" << current->name << " -> " << current->pattern << "] ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
    std::cout << "Total elements: " << elementCount << std::endl;
    std::cout << "Load factor: " << getLoadFactor() << std::endl;
    std::cout << "Collisions: " << collisionCount << std::endl;
}

double HashTable::getLoadFactor()
{
    return static_cast<double>(elementCount) / TABLE_SIZE;
}

int HashTable::getCollisionCount()
{
    return collisionCount;
}

std::vector<SchemeEntry *> HashTable::getAllSchemes()
{
    std::vector<SchemeEntry *> schemes;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        SchemeEntry *current = buckets[i];
        while (current != nullptr)
        {
            schemes.push_back(current);
            current = current->next;
        }
    }
    return schemes;
}
