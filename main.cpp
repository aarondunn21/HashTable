#include <iostream>
#include "hashtable.h"
#include "string"
#include "passserver.h"
#include "cstring"

using namespace std;
using namespace cop4530;

int main() {

    PassServer ps1;
    pair<string, string> p;

    ps1.load("1stTest");
    ps1.dump();
//    p.first = "Aaron";
//    p.second = "Chicken";
//    ps1.addUser(p);
//    p.first = "sdfg";
//    p.second = "ert";
//    ps1.addUser(p);
//    p.first = "rteydfsg";
//    p.second = "hjgkgn";
//    ps1.addUser(p);
//    p.first = "snbmvrtyw";
//    p.second = "fdsgsder46115661";
//    ps1.addUser(p);
//    ps1.write_to_file("1stTest");
//    ps1.dump();
//    cout << endl;
//    ps1.removeUser("sdfg");
//    ps1.dump();
//    p.first = "Aaron";
//    p.second = "Chicken";
//    ps1.changePassword(p, "Chicken194189844444444dfghdfghdfghdfh");
//    ps1.dump();
//    ps1.write_to_file("1stTest");







//    HashTable<int, int> ht;
//    for(int i = 0; i < 300; i++){
//        p.first = 6 * i;
//        p.second = 2 * i;
//        ht.insert(p);
//    }
//    p.first = 275704;
//    p.second = 123;
//    ht.insert(p);
//
//    ht.dump();
//    ht.contains(964);
//    ht.remove(964);
//    ht.contains(964);
//    ht.dump();
//    p.first = 10604;
//    p.second = 121;
//    ht.match(p);
//    cout << ht.size() << endl;
//    ht.clear();
//    cout << ht.size() << endl;
//    ht.dump();


    return 0;
}
