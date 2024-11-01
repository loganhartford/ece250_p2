#include "Chain.hpp"

Chain::Chain()
{
    head = nullptr;
}

Chain::~Chain()
{
    ChainNode *current = head;
    while (current != nullptr)
    {
        ChainNode *toDelete = current;
        current = current->next;
        delete toDelete;
    }
}

bool Chain::insert(int id, const std::string &payload)
{
    // Don't insert if the ID already exists
    if (find(id) != nullptr)
    {
        return false;
    }
    ChainNode *newNode = new ChainNode(id, payload);
    newNode->next = head;
    head = newNode;
    return true;
}

ChainNode *Chain::find(int id) const
{
    ChainNode *current = head;
    while (current != nullptr)
    {
        if (current->data.getID() == id)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool Chain::remove(int id)
{
    ChainNode *current = head;
    ChainNode *prev = nullptr;

    while (current != nullptr)
    {
        if (current->data.getID() == id)
        {
            if (prev == nullptr)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}
