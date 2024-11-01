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
            bool corruptedSuccess = table->corrupt(ID, charString);
            if (corruptedSuccess)
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        else if (cmd == "VALIDATE")
        {
            cin >> ID;
            int validated = table->validate(ID);
            if (validated == 1)
            {
                cout << "valid" << endl;
            }
            else if (validated == 0)
            {
                cout << "invalid" << endl;
            }
            else if (validated == -1)
            {
                cout << "failure" << endl;
            }
        }
        else if (cmd == "PRINT")
        {
            cin >> chainIndex;
            table->print(chainIndex);
        }
        else if (cmd == "EXIT")
        {
            if (table)
            {
                delete table;
            }
            return 0;
        }
    }

    if (table)
    {
        delete table;
    }
    return 0;
}