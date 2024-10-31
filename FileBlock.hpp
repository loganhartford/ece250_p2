#ifndef FILEBLOCK_HPP
#define FILEBLOCK_HPP

#include <vector>
#include <string>

class FileBlock
{
private:
    int ID;
    std::vector<char> payload;
    int checksum;

    int calculateChecksum();

public:
    FileBlock(int id, const std::string &data = "");
    ~FileBlock();

    void corruptData(const std::string &newData);
    bool validateData() const;
    int getID();
};

#endif
