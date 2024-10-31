#include "HashTable.hpp"
#include "FileBlock.hpp"
#include "Chain.hpp"

HashTable::HashTable(int size, bool useSeparateChaining)
    : size(size), useSeparateChaining(useSeparateChaining)
{
    if (useSeparateChaining)
    {
        table.resize(size, nullptr);
        for (int i = 0; i < size; ++i)
        {
            table[i] = new Chain();
        }
    }
    else
    {
        table.resize(size, nullptr);
    }
}

HashTable::~HashTable()
{
    for (auto &entry : table)
    {
        if (useSeparateChaining)
        {
            delete static_cast<Chain *>(entry);
        }
        else
        {
            delete static_cast<FileBlock *>(entry);
        }
    }
}

int HashTable::primaryHash(int key) const
{
    return key % size;
}

int HashTable::secondaryHash(int key) const
{
    int hashValue = (key / size) % size;
    return (hashValue % 2 == 0) ? hashValue + 1 : hashValue;
}

bool HashTable::store(int id, const std::string &data)
{
    int index = primaryHash(id);

    if (!useSeparateChaining)
    {
        int step = secondaryHash(id);
        for (int i = 0; i < size; ++i)
        {
            int newIndex = (index + i * step) % size;
            if (table[newIndex] == nullptr)
            {
                table[newIndex] = new FileBlock(id, data);
                return true;
            }
            else if (static_cast<FileBlock *>(table[newIndex])->getID() == id)
            {
                return false;
            }
        }
        return false;
    }
    else
    {
        Chain *chain = static_cast<Chain *>(table[index]);
        return chain->insert(id, data);
    }
}

int HashTable::search(int id) const
{
    int index = primaryHash(id);

    if (!useSeparateChaining)
    {
        int step = secondaryHash(id);
        for (int i = 0; i < size; ++i)
        {
            int newIndex = (index + i * step) % size;
            if (table[newIndex] == nullptr)
            {
                return -1;
            }
            else if (static_cast<FileBlock *>(table[newIndex])->getID() == id)
            {
                return newIndex;
            }
        }
        return -1;
    }
    else
    {
        Chain *chain = static_cast<Chain *>(table[index]);
        if (chain->find(id) != nullptr)
        {
            return index;
        }
        else
        {
            return -1;
        }
    }
}
