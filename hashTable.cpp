#include "HashTable.hpp"
#include "FileBlock.hpp"

HashTable::HashTable(int size, bool useSeparateChaining)
    : size(size), useSeparateChaining(useSeparateChaining), table(size, nullptr) {}

HashTable::~HashTable()
{
    for (auto &block : table)
    {
        delete block;
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
                table[newIndex] = new fileBlock(id, data);
                return true;
            }
            else if (table[newIndex]->getID() == id)
            {
                return false;
            }
        }
        return false;
    }
    else
    {
        if (table[index] == nullptr)
        {
            table[index] = new fileBlock(id, data);
            return true;
        }
        return false;
    }
}
