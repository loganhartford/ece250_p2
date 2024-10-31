#include "ChainNode.hpp"

ChainNode::ChainNode(int id, const std::string &payload)
    : data(id, payload), next(nullptr) {}