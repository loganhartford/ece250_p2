#include <iostream>
#include <string>
using namespace std;

int main()
{
    string cmd;
    int size = 0;
    bool type;
    int ID;
    int chainIndex;
    string charString;

    while (cin >> cmd)
    {
        if (cmd == "NEW")
        {
            cin >> size >> type;

            cout << "success" << endl;
        }
        else if (cmd == "STORE")
        {
            cin >> ID;
            getline(cin, charString, '!');
        }
        else if (cmd == "SEARCH")
        {
            cin >> ID;
        }
        else if (cmd == "DELETE")
        {
            cin >> ID;
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