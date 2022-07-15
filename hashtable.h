#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "vector"
#include "list"

using namespace std;

// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

namespace cop4530{
    template <typename K, typename V>
    class HashTable {
    public:
        explicit HashTable(int size = 101);
        ~HashTable();
        bool contains(const K & k);
        bool match(const std::pair<K, V> & kv);
        bool insert(const std::pair<K, V> & kv);
        bool insert(const std::pair<K, V> && kv);
        bool remove(const K & k);
        void clear();
        bool load(const char *filename);
        void dump() const;
        int size() const;
        bool write_to_file(const char *filename);

    private:
        unsigned long prime_below (unsigned long);
        void setPrimes(vector<unsigned long>&);
        int MyHash(const K &k);
        void makeEmpty();
        void rehash();

        struct kVPair {
            K key;
            V value;
        };

        vector<list<pair<K, V>>> hashTable;
        int tableSize;
        int entries;




    };

}

#include "hashtable.hpp"

#endif
