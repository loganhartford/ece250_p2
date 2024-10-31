#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <vector>
#include <optional>
#include "FileBlock.hpp"

class HashTable
{
private:
    int size;
    bool useSeparateChaining;
    std::vector<void *> table;

    int primaryHash(int key) const;
    int secondaryHash(int key) const;

public:
    HashTable(int size, bool useSeparateChaining);
    ~HashTable();

    bool store(int id, const std::string &data);
};

#endif
