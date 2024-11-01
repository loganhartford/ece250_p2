#include "FileBlock.hpp"

FileBlock::FileBlock(int id, const string &data)
{
    ID = id;
    payload.resize(500, 0);
    checksum = 0;

    // Copy charstring into the payload
    size_t length = min(data.size(), payload.size());
    copy(data.begin(), data.begin() + length, payload.begin());

    // Compute and update checksum
    checksum = calculateChecksum();
}

FileBlock::~FileBlock()
{
}

int FileBlock::calculateChecksum()
{
    int checksum = 0;
    for (char byte : payload)
    {
        checksum += static_cast<unsigned char>(byte);
    }
    return checksum % 256;
}

void FileBlock::corruptData(const string &newData)
{
    // Fill the payload with 0s
    fill(payload.begin(), payload.end(), 0);
    // Copy the new data into the payload, but don't compute checksum
    size_t length = min(newData.size(), payload.size());
    copy(newData.begin(), newData.begin() + length, payload.begin());
}

bool FileBlock::validateData() const
{
    int currentChecksum = 0;
    for (char byte : payload)
    {
        currentChecksum += static_cast<unsigned char>(byte);
    }
    currentChecksum %= 256;
    return currentChecksum == checksum;
}

int FileBlock::getID() const
{
    return ID;
}
