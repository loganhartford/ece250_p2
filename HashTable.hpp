#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "FileBlock.hpp"

class HashTable
{
private:
    int size;
    bool useSeparateChaining;
    vector<void *> table; // void* is used to store either Chain* or FileBlock*

    int primaryHash(int key) const;
    int secondaryHash(int key) const;

public:
    HashTable(int size, bool useSeparateChaining);
    ~HashTable();

    bool store(int id, const string &data);
    int search(int id) const;
    bool remove(int id);
    bool corrupt(int id, const string &newData);
    int validate(int id) const;
    void print(int index) const;
};

#endif
