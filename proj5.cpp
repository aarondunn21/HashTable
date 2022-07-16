#include <iostream>
#include "hashtable.h"
#include "string"
#include "passserver.h"
#include "cstring"

using namespace std;
using namespace cop4530;

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}

int main() {

    cout << "Enter desired size of hash table" << endl;
    int size;
    cin >> size;
    PassServer ps1(size);
    pair<string, string> p;

    char choice = ' ';
    while (choice != 'x'){
        Menu();
        cin >> choice;
        cout << endl;

        if(choice == 'l'){
            cout << "Enter name of file to open: ";
            string name;
            cin >> name;
            cout << endl;
            const char * cStr = name.c_str();

            ps1.load(cStr);
        }
        else if(choice == 'a'){
            string temp;
            cout << "Enter username: ";
            cin >> temp;
            cout << endl;
            p.first = temp;
            cout << "Enter password: ";
            cin >> temp;
            cout << endl;
            p.second = temp;

            ps1.addUser(p);
        }
        else if(choice == 'r'){
            string temp;
            cout << "Enter username of user to remove: ";
            cin >> temp;
            cout << endl;
            ps1.removeUser(temp);
        }
        else if(choice == 'c'){
            string temp;
            cout << "Enter username: ";
            cin >> temp;
            cout << endl;
            p.first = temp;
            cout << "Enter password: ";
            cin >> temp;
            cout << endl;
            p.second = temp;

            string newPass;
            cout << "Enter new password" << endl;
            cin >> newPass;

            ps1.changePassword(p, newPass);
        }
        else if(choice == 'f'){
            string temp;
            cout << "Enter username to search for: ";
            cin >> temp;
            cout << endl;
            ps1.find(temp);
        }
        else if(choice == 'd'){
            ps1.dump();
        }
        else if(choice == 's'){
            cout << "Size of hashtable: " << ps1.size();
        }
        else if(choice == 'w'){
            string name;
            cout << "Enter name choice for file: ";
            cin >> name;
            cout << endl;
            const char * cStr = name.c_str();
            ps1.write_to_file(cStr);
        }

    }
    return 0;
}
