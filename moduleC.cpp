#include "moduleC.h"
#include <iostream>
#include <string>
using namespace std;

HashNode::HashNode(string k, Aircraft* v) {
    key = k;
    value = v;
    next = nullptr;
}

HashTable::HashTable(int size) {
    capacity = size;
    table = new HashNode * [capacity]();
}

HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        HashNode* current = table[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

int HashTable::hashFunction(string key) {
    // Simple hash function: sum of ASCII values
    int sum = 0;
    for (char c : key) {
        sum += (int)c;
    }
    return sum % capacity;
}

void HashTable::insert(string key, Aircraft* value) {
    // Insert aircraft into hash table
    int index = hashFunction(key);
    HashNode* newNode = new HashNode(key, value);

    if (!table[index]) {
        table[index] = newNode;
    }
    else {
        newNode->next = table[index];
        table[index] = newNode;
    }
}

Aircraft* HashTable::search(string key) {
    // Search for aircraft by flight ID
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }

    return nullptr;
}

void HashTable::update(string key, Aircraft* newValue) {
    // Update aircraft information
    Aircraft* plane = search(key);
    if (plane) {
        *plane = *newValue;
    }
}

void HashTable::remove(string key) {
    // Remove aircraft from hash table
    int index = hashFunction(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (!current) return;

    if (!prev) {
        table[index] = current->next;
    }
    else {
        prev->next = current->next;
    }

    delete current;
}

void HashTable::display() {
    // Display all aircraft in hash table
    cout << "\nAIRCRAFT REGISTRY:\n";
    cout << "==================\n";

    for (int i = 0; i < capacity; i++) {
        HashNode* current = table[i];
        while (current) {
            cout << "Index " << i << ": " << current->key << "\n";
            current = current->next;
        }
    }
}