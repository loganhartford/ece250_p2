#include "FileBlock.hpp"
#include <algorithm> // For std::copy

fileBlock::fileBlock(int id, const std::string &data)
    : ID(id), payload(500, 0), checksum(0)
{
    std::size_t length = std::min(data.size(), payload.size());
    std::copy(data.begin(), data.begin() + length, payload.begin());

    checksum = calculateChecksum();
}

fileBlock::~fileBlock()
{
}

int fileBlock::calculateChecksum()
{
    int checksum = 0;
    for (char byte : payload)
    {
        checksum += static_cast<unsigned char>(byte);
    }
    return checksum % 256;
}

void fileBlock::corruptData(const std::string &newData)
{
    // Fill the payload with 0s
    std::fill(payload.begin(), payload.end(), 0);
    // Copy the new data into the payload, but don't compute checksum
    std::size_t length = std::min(newData.size(), payload.size());
    std::copy(newData.begin(), newData.begin() + length, payload.begin());
}

bool fileBlock::validateData() const
{
    int currentChecksum = 0;
    for (char byte : payload)
    {
        currentChecksum += static_cast<unsigned char>(byte);
    }
    currentChecksum %= 256;
    return currentChecksum == checksum;
}

int fileBlock::getID()
{
    return ID;
}
