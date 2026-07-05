#ifndef MODULEC_H
#define MODULEC_H

#include "aircraft.h"
#include <string>

struct HashNode {
    std::string key;
    Aircraft* value;
    HashNode* next;

    HashNode(std::string k, Aircraft* v);
};

class HashTable {
private:
    int capacity;
    HashNode** table;

    int hashFunction(std::string key);

public:
    HashTable(int size);
    ~HashTable();

    void insert(std::string key, Aircraft* value);
    Aircraft* search(std::string key);
    void update(std::string key, Aircraft* newValue);
    void remove(std::string key);
    void display();
};

#endif