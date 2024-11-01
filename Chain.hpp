#ifndef CHAIN_HPP
#define CHAIN_HPP

#include "ChainNode.hpp"

class Chain
{
private:
    ChainNode *head;

public:
    Chain();
    ~Chain();

    bool insert(int id, const string &payload);
    ChainNode *find(int id) const;
    bool remove(int id);
    void printChain() const;
    bool isEmpty() const;
};

#endif
