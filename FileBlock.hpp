#ifndef FILEBLOCK_HPP
#define FILEBLOCK_HPP

#include <vector>
#include <string>

class fileBlock
{
private:
    int ID;
    std::vector<char> payload;
    int checksum;

    int calculateChecksum();

public:
    fileBlock(int id, const std::string &data = "");
    ~fileBlock();

    void corruptData(const std::string &newData);
    bool validateData() const;
    int getID();
};

#endif
