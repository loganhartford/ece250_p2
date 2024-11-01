#include "FileBlock.hpp"

class ChainNode
{
public:
    FileBlock data;
    ChainNode *next;

    ChainNode(int id, const string &payload);
};