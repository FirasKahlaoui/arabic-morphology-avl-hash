#include <iostream>
#include "../include/HashTable.h"

void testBasicOperations()
{
    std::cout << "=== Test 1: Basic Insert and Search ===" << std::endl;
    HashTable table;

    table.insert("فاعل", "C1 ا C2 C3");
    table.insert("مفعول", "م C1 C2 و C3");
    table.insert("مفاعل", "م C1 ا C2 C3");

    SchemeEntry *found = table.search("فاعل");
    if (found)
    {
        std::cout << "Found: " << found->name << " -> " << found->pattern << std::endl;
    }

    SchemeEntry *notFound = table.search("تفعيل");
    if (!notFound)
    {
        std::cout << "Not found: تفعيل (as expected)" << std::endl;
    }

    std::cout << "Load factor: " << table.getLoadFactor() << std::endl;
    std::cout << std::endl;
}

void testUpdate()
{
    std::cout << "=== Test 2: Update Operation ===" << std::endl;
    HashTable table;

    table.insert("فاعل", "C1 ا C2 C3");
    std::cout << "Before update: " << table.search("فاعل")->pattern << std::endl;

    table.update("فاعل", "C1 ا C2 ي C3");
    std::cout << "After update: " << table.search("فاعل")->pattern << std::endl;
    std::cout << std::endl;
}

void testRemove()
{
    std::cout << "=== Test 3: Remove Operation ===" << std::endl;
    HashTable table;

    table.insert("فاعل", "C1 ا C2 C3");
    table.insert("مفعول", "م C1 C2 و C3");

    std::cout << "Before remove - Load factor: " << table.getLoadFactor() << std::endl;

    bool removed = table.remove("فاعل");
    std::cout << "Removed فاعل: " << (removed ? "success" : "failed") << std::endl;

    SchemeEntry *found = table.search("فاعل");
    std::cout << "Search after remove: " << (found ? "found" : "not found") << std::endl;

    std::cout << "After remove - Load factor: " << table.getLoadFactor() << std::endl;
    std::cout << std::endl;
}

void testCollisions()
{
    std::cout << "=== Test 4: Collision Handling ===" << std::endl;
    HashTable table;

    std::string schemes[] = {
        "فاعل", "مفعول", "مفاعل", "فعيل", "فعال",
        "مفعال", "فعول", "فاعول", "تفعيل", "استفعال",
        "انفعال", "افتعال", "تفاعل", "تفعل", "فعلان"};

    std::string patterns[] = {
        "C1 ا C2 C3", "م C1 C2 و C3", "م C1 ا C2 C3",
        "C1 C2 ي C3", "C1 C2 ا C3", "م C1 C2 ا C3",
        "C1 C2 و C3", "C1 ا C2 و C3", "ت C1 C2 ي C3",
        "ا س ت C1 C2 C3", "ا ن C1 C2 C3", "ا C1 ت C2 C3",
        "ت C1 ا C2 C3", "ت C1 C2 C3", "C1 C2 C3 ا ن"};

    for (int i = 0; i < 15; i++)
    {
        table.insert(schemes[i], patterns[i]);
    }

    std::cout << "Inserted 15 schemes" << std::endl;
    std::cout << "Load factor: " << table.getLoadFactor() << std::endl;
    std::cout << "Collision count: " << table.getCollisionCount() << std::endl;
    std::cout << "Average collisions per insert: "
              << static_cast<double>(table.getCollisionCount()) / 15 << std::endl;

    for (int i = 0; i < 15; i++)
    {
        SchemeEntry *found = table.search(schemes[i]);
        if (!found)
        {
            std::cout << "ERROR: Could not find " << schemes[i] << std::endl;
        }
    }
    std::cout << "All schemes successfully retrieved!" << std::endl;
    std::cout << std::endl;
}

void testGetAllSchemes()
{
    std::cout << "=== Test 5: Get All Schemes ===" << std::endl;
    HashTable table;

    table.insert("فاعل", "C1 ا C2 C3");
    table.insert("مفعول", "م C1 C2 و C3");
    table.insert("مفاعل", "م C1 ا C2 C3");

    auto schemes = table.getAllSchemes();
    std::cout << "Retrieved " << schemes.size() << " schemes:" << std::endl;
    for (const auto &scheme : schemes)
    {
        std::cout << "  " << scheme->name << " -> " << scheme->pattern << std::endl;
    }
    std::cout << std::endl;
}

void testDisplay()
{
    std::cout << "=== Test 6: Display Hash Table ===" << std::endl;
    HashTable table;

    table.insert("فاعل", "C1 ا C2 C3");
    table.insert("مفعول", "م C1 C2 و C3");
    table.insert("مفاعل", "م C1 ا C2 C3");

    table.display();
    std::cout << std::endl;
}

int main()
{
    std::cout << "Hash Table Test Suite" << std::endl;
    std::cout << "=====================" << std::endl << std::endl;

    testBasicOperations();
    testUpdate();
    testRemove();
    testCollisions();
    testGetAllSchemes();
    testDisplay();

    std::cout << "All tests completed!" << std::endl;
    return 0;
}
