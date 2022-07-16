#include "hashtable.h"
#include "iostream"
#include "vector"
#include "sstream"
#include <fstream>  // includes write/read of files
#include "sstream"
using namespace std;
using namespace cop4530;
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template<typename K, typename V>
int HashTable<K, V>::MyHash(const K &k) {
    string temp = k;
    int kInt = 0;
    for (char i: temp) {
        kInt += i;
    }
    return kInt % tableSize;
    //returns index to hashtable
}

template<typename K, typename V>
HashTable<K, V>::HashTable(int size) {
    hashTable.resize(prime_below(size));
    tableSize = hashTable.size();
    entries = 0;

}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K &k) {
    int hash = MyHash(k);
    if(hashTable[hash].empty()){
        cout << "key not contained" << endl;
        return false;
        //add if list is empty at index
    }
    else{
        auto lItr = hashTable[hash].begin();
        for(; lItr != hashTable[hash].end(); lItr++){
            if(lItr->first == k){
                cout << "key contained in table" << endl;
                cout << "[KEY]:" << lItr->first << " [VALUE]:" << lItr->second << endl;
                return true;
                //add if list is not empty
            }
        }
        cout << "key not contained in list" << endl;
        return false;

    }
}

template<typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> &kv) {
    int hash = MyHash(kv.first);
    if(hashTable[hash].empty()){
        cout << "key value pair not contained" << endl;
        return false;
        //false if list empty
    }
    auto lItr = hashTable[hash].begin();
    for(; lItr != hashTable[hash].end(); lItr++){
        if(lItr->second == kv.second && lItr->first == kv.first){
            cout << "Key Value pair is in the table!" << endl;
            return true;
            //true if key value pair present
        }
    }
    cout << "key value pair not contained" << endl;
    return false;
    //key has list but not contained
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> &kv) {
    if(entries > tableSize){
        rehash();
    }
    int hash = MyHash(kv.first);
    if(hashTable[hash].empty()){
        hashTable[hash].push_back(kv);
        entries++;
        return true;
        //add if list is empty at index
    }

    auto lItr = hashTable[hash].begin();
    for(; lItr != hashTable[hash].end(); lItr++){
        if(lItr->first == kv.first){
            cout << "Value replaced" << endl;
            lItr->second = kv.second;
            //if key is present but not value replace value
            return true;
        }
        if(lItr->second == kv.second){
            cout << "Key Value pair already in table! Nothing added." << endl;
            return false;
            //quit if key value pair present
        }
    }
    hashTable[hash].push_back(kv);
    entries++;
    return true;
    //if key is present but not value add pair

}

template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> &&kv) {
    if(entries > tableSize){
        rehash();
        //if table needs to be resized and rehashed
    }
    int hash = MyHash(kv.first);
    if(hashTable[hash].empty()){
        hashTable[hash].push_back(move(kv));
        entries++;
        return true;
        //add if list is empty at index
    }

    auto lItr = hashTable[hash].begin();
    for(; lItr != hashTable[hash].end(); lItr++){
        if(lItr->first == kv.first){
            cout << "Value replaced" << endl;
            swap(lItr->second, kv.second);
            //if key is present but not value replace value
            return true;
        }
        if(lItr->second == kv.second){
            cout << "Key Value pair already in table! Nothing added." << endl;
            return false;
            //quit if key value pair present
        }
    }
    hashTable[hash].push_back(kv);
    entries++;
    return true;
    //if key is present but not value add pair
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K &k) {
    int hash = MyHash(k);
    if(hashTable[hash].empty()){
        cout << "Empty Hashtable, nothing to remove" << endl;
        return false;
        //nothing to remove
    }

    auto lItr = hashTable[hash].begin();
    for(; lItr != hashTable[hash].end(); lItr++){
        if(lItr->first == k){
            hashTable[hash].erase(lItr);
            entries--;
            cout << "Entry Removed" << endl;
            return true;
        }
    }
    cout << "Nothing to remove" << endl;
    return false;
}
//move version of insert

template<typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    fstream myFile;
    char c; //holds output from file
    string temp = " ";
    string temp2 = " ";
    pair<K, V> p;

    myFile.open(filename); //attempt to open file
    if(!myFile){
        cout << "error with opening chosen file" << endl;
        return false;
    }
    else{
        while(getline(myFile, temp)){
            stringstream ss;
            ss << temp;
            while(!ss.eof()) {
                ss >> temp2;
                p.first = temp2;
                ss >> temp2;
                p.second = temp2;
                insert(p);
            }
            //adds each key value pair to a pair variable and inserts it
        }
    }
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::dump() const{
    kVPair temp;
    if(entries == 0){
        cout << "empty hash table" << endl;
        return;
    }
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i].size() < 1){
            continue;
            //if hash table is empty continue
        }
        auto lItr = hashTable[i].begin();
        for(; lItr != hashTable[i].end(); lItr++){
            cout << i << ". [KEY]:" << lItr->first << " [VALUE]:" << lItr->second << "; ";
            //print every entry
        }
        cout << endl;
    }
}

template<typename K, typename V>
int HashTable<K, V>::size() const{
    return entries;
}

template<typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for(int i = 0; i < tableSize; i++) {
        hashTable[i].clear();
        entries = 0;
    }
}

template<typename K, typename V>
void HashTable<K, V>::rehash() {
    cout << "[INFO] rehashing underway" << endl;
    vector<list<pair<K, V>>> temp = hashTable;
    //save data of old hash table
    hashTable.clear();
    hashTable.resize(tableSize * 2);
    tableSize = hashTable.size();
    //double size of hashtable

    pair<K, V> p;

    for(int i = 0; i < temp.size(); i++){
        auto lItr = temp[i].begin();
        for(; lItr != temp[i].end(); lItr++){
            p.first = lItr->first;
            p.second = lItr->second;
            insert(p);
            //re-insert data into larger table

            entries--;
            //resets off balance when using insert function
        }
    }

}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) {
    ofstream MyFile(filename);

    kVPair temp;
    if(entries == 0){
        cout << "empty hash table" << endl;
        return false;
    }
    for(int i = 0; i < tableSize; i++){
        if(hashTable[i].size() < 1){
            continue;
            //leave if hash table is empty
        }
        auto lItr = hashTable[i].begin();
        for(; lItr != hashTable[i].end(); lItr++){
            MyFile << lItr->first << " " << lItr->second << endl;
            //adds pair to value separated by white space
        }
        cout << endl;
    }
    MyFile.close();
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
    makeEmpty();
    hashTable.clear();
    //destructor
}





















