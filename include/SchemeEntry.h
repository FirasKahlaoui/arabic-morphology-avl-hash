#ifndef SCHEMEENTRY_H
#define SCHEMEENTRY_H

#include <string>

struct SchemeEntry
{
    std::string name;
    std::string pattern;
    SchemeEntry *next;

    SchemeEntry(const std::string &n, const std::string &p)
        : name(n), pattern(p), next(nullptr) {}

    ~SchemeEntry()
    {
        delete next;
    }
};

#endif
