//
// Created by Aaron on 7/14/2022.
//


#include "passserver.h"
#include "hashtable.h"
#include "sstream"



using namespace std;
using namespace cop4530;


PassServer::PassServer(int size)  {

}

bool PassServer::addUser(pair<string, string> &kv) {
    kv.second = encrypt(kv.second);
    return ht.insert(kv);


}

bool PassServer::addUser(pair<string, string> &&kv) {
    kv.second = encrypt(kv.second);
    return ht.insert(kv);
}
//move version of addUser

bool PassServer::removeUser(const string &k) {
    return ht.remove(k);
}

bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword) {

    pair<string, string> pTemp = p;
    pTemp.second = encrypt(pTemp.second);
    if(!ht.match(pTemp)){
        cout << "user not found" << endl;
        return false;
    }
    else{
        string temp = encrypt(newpassword);
        if(temp == pTemp.second){
            cout << "password change cannot be the same" << endl;
            return false;
        }
        pTemp.second = temp;
        ht.insert(pTemp);
        return true;
        //changes users password if applicable
    }
}

bool PassServer::find(const string &user) {
    ht.contains(user);
}

bool PassServer::load(const char *filename) {
    return ht.load(filename);
}

void PassServer::dump() {
    ht.dump();
}

int PassServer::size() {
    return ht.size();
}

string PassServer::encrypt(const string &str) {
    //unable to use crypt.h file on my machine
    //created my own encryption function
    int ascii = 0;
    string result = " ";
    char temp = ' ';
    for (char c : str){
        ascii += (c * 15) / 5;
        temp += c % str.length();

    }
    int num = (ascii + temp) % 12345;
    stringstream  ss;
    ss << hex << num;
    //make encoded value a hex
    return result = "$1$" + ss.str() + "$";
}

PassServer::~PassServer() {
    ht.clear();
}

bool PassServer::write_to_file(const char *filename) {
    return ht.write_to_file(filename);
}








