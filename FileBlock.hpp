#ifndef FILEBLOCK_HPP
#define FILEBLOCK_HPP

#include <algorithm> // For copy
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class FileBlock
{
private:
    int ID;
    vector<char> payload;
    int checksum;

    int calculateChecksum();

public:
    FileBlock(int id, const string &data = "");
    ~FileBlock();

    void corruptData(const string &newData);
    bool validateData() const;
    int getID() const;
};

#endif
