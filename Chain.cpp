#include <iostream>
using namespace std;

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

bool Chain::insert(int id, const string &payload)
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

void merge(vector<int> &ids, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArray(n1);
    vector<int> rightArray(n2);

    for (int i = 0; i < n1; ++i)
    {
        leftArray[i] = ids[left + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        rightArray[j] = ids[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
        {
            ids[k] = leftArray[i];
            ++i;
        }
        else
        {
            ids[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        ids[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        ids[k] = rightArray[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int> &ids, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(ids, left, mid);
        mergeSort(ids, mid + 1, right);
        merge(ids, left, mid, right);
    }
}

void Chain::printChain() const
{
    vector<int> ids;
    ChainNode *current = head;

    while (current != nullptr)
    {
        ids.push_back(current->data.getID());
        current = current->next;
    }

    mergeSort(ids, 0, ids.size() - 1);

    for (size_t i = 0; i < ids.size(); ++i)
    {
        if (i > 0)
        {
            cout << " ";
        }
        cout << ids[i];
    }
    cout << endl;
}

bool Chain::isEmpty() const
{
    return head == nullptr;
}
