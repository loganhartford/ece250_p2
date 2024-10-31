#include <iostream>
#include <string>
using namespace std;

#include "HashTable.hpp"

int main()
{
    string cmd;
    int size = 0;
    bool type;
    int ID;
    int chainIndex;
    string charString;
    HashTable *table = nullptr;

    while (cin >> cmd)
    {
        if (cmd == "NEW")
        {
            cin >> size >> type;
            table = new HashTable(size, type);

            cout << "success" << endl;
        }
        else if (cmd == "STORE")
        {
            cin >> ID;
            getline(cin, charString, '!');
            bool storedSuccess = table->store(ID, charString);
            if (storedSuccess)
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        else if (cmd == "SEARCH")
        {
            cin >> ID;
            int foundIndex = table->search(ID);
            if (foundIndex == -1)
            {
                cout << "not found" << endl;
            }
            else
            {
                cout << "found " << ID << " in " << foundIndex << endl;
            }
        }
        else if (cmd == "DELETE")
        {
            cin >> ID;
            bool removedSuccess = table->remove(ID);
            if (removedSuccess)
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        else if (cmd == "CORRUPT")
        {
            cin >> ID;
            getline(cin, charString, '!');
        }
        else if (cmd == "VALIDATE")
        {
            cin >> ID;
        }
        else if (cmd == "PRINT")
        {
            cin >> chainIndex;
        }
        else if (cmd == "EXIT")
        {
            return 0;
        }
    }

    return 0;
}