#include "HashTable.hpp"
#include "FileBlock.hpp"
#include "Chain.hpp"

FileBlock *const HashTable::TOMBSTONE = reinterpret_cast<FileBlock *>(-1);

HashTable::HashTable(int size, bool useSeparateChaining)
{
    this->size = size;
    this->useSeparateChaining = useSeparateChaining;

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
    for (int i = 0; i < size; ++i)
    {
        if (useSeparateChaining)
        {
            delete static_cast<Chain *>(table[i]);
        }
        else
        {
            if (table[i] != nullptr && table[i] != TOMBSTONE)
            {
                delete static_cast<FileBlock *>(table[i]);
            }
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
        int firstTombstone = -1;

        for (int i = 0; i < size; ++i)
        {
            int newIndex = (index + i * step) % size;

            if (table[newIndex] == nullptr)
            {
                if (firstTombstone != -1)
                {
                    newIndex = firstTombstone;
                }
                table[newIndex] = new FileBlock(id, data);
                return true;
            }
            else if (table[newIndex] == TOMBSTONE)
            {
                if (firstTombstone == -1)
                {
                    firstTombstone = newIndex;
                }
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

            if (table[newIndex] == nullptr) // ID is not in the table
            {
                return -1;
            }
            else if (table[newIndex] != TOMBSTONE && static_cast<FileBlock *>(table[newIndex])->getID() == id)
            {
                return newIndex;
            }
            // If table[newIndex] is a tombstone, continue searching
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

bool HashTable::remove(int id)
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
                return false; // ID is not in the table
            }
            else if (table[newIndex] != TOMBSTONE && static_cast<FileBlock *>(table[newIndex])->getID() == id)
            {
                delete static_cast<FileBlock *>(table[newIndex]);
                table[newIndex] = TOMBSTONE;
                return true;
            }
        }
        return false;
    }
    else
    {
        Chain *chain = static_cast<Chain *>(table[index]);
        return chain->remove(id);
    }
}

bool HashTable::corrupt(int id, const std::string &newData)
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
                return false;
            }
            else if (table[newIndex] != TOMBSTONE && static_cast<FileBlock *>(table[newIndex])->getID() == id)
            {
                static_cast<FileBlock *>(table[newIndex])->corruptData(newData);
                return true;
            }
        }
        return false;
    }
    else
    {
        Chain *chain = static_cast<Chain *>(table[index]);
        ChainNode *node = chain->find(id);
        if (node != nullptr)
        {
            node->data.corruptData(newData);
            return true;
        }
        return false;
    }
}

int HashTable::validate(int id) const
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
            else if (table[newIndex] != TOMBSTONE && static_cast<FileBlock *>(table[newIndex])->getID() == id)
            {
                return static_cast<FileBlock *>(table[newIndex])->validateData();
            }
        }
        return -1;
    }
    else
    {
        Chain *chain = static_cast<Chain *>(table[index]);
        ChainNode *node = chain->find(id);
        if (node != nullptr)
        {
            return node->data.validateData();
        }
        return -1;
    }
}

void HashTable::print(int index) const
{
    Chain *chain = static_cast<Chain *>(table[index]);
    if (chain == nullptr || chain->isEmpty())
    {
        cout << "chain is empty" << endl;
    }
    else
    {
        chain->printChain();
    }
}
