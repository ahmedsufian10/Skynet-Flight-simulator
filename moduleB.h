#ifndef MODULEB_H
#define MODULEB_H

#include "aircraft.h"
#include <string>

class MinHeap {
private:
    Aircraft** heap;
    int capacity;
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);
    int findIndex(std::string flightID);

public:
    MinHeap(int cap);
    ~MinHeap();

    void insert(Aircraft* plane);
    Aircraft* extractMin();
    void decreaseKey(std::string flightID, Priority newPriority);
    bool isEmpty();
    Aircraft* peek();
    void displayQueue();
};

#endif