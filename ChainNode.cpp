#include "ChainNode.hpp"

ChainNode::ChainNode(int id, const string &payload)
    : data(id, payload), next(nullptr)
{
}