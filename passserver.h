#ifndef HASHTABLE_PASSSERVER_H
#define HASHTABLE_PASSSERVER_H

#include "iostream"
#include "hashtable.h"

using namespace std;


class PassServer : cop4530::HashTable<string , string>{
public:
    explicit PassServer(int size = 101);
    ~PassServer();
    bool load(const char *filename);
    bool addUser(pair<string, string> & kv);
    bool addUser(pair<string, string> && kv);
    bool removeUser(const string & k);
    bool changePassword(const std::pair<string, string> &p, const string & newpassword);
    bool find(const string & user);
    void dump();
    int size();
    bool write_to_file(const char *filename);

private:
    string encrypt(const string & str);

    HashTable<string, string> ht;
};



#endif //HASHTABLE_PASSSERVER_H
