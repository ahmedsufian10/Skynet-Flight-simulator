#include "moduleB.h"
#include <iostream>
#include <string>
using namespace std;

MinHeap::MinHeap(int cap) {
    capacity = cap;
    size = 0;
    heap = new Aircraft * [capacity];
}

MinHeap::~MinHeap() {
    delete[] heap;
}

void MinHeap::swap(int i, int j) {
    // Swap two elements in heap
    Aircraft* temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void MinHeap::heapifyUp(int index) {
    // Maintain heap property upwards
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index]->priority < heap[parent]->priority) {
            swap(index, parent);
            index = parent;
        }
        else {
            break;
        }
    }
}

void MinHeap::heapifyDown(int index) {
    // Maintain heap property downwards
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left]->priority < heap[smallest]->priority) {
            smallest = left;
        }
        if (right < size && heap[right]->priority < heap[smallest]->priority) {
            smallest = right;
        }

        if (smallest != index) {
            swap(index, smallest);
            index = smallest;
        }
        else {
            break;
        }
    }
}

void MinHeap::insert(Aircraft* plane) {
    // Insert new aircraft into heap
    if (size >= capacity) return;

    heap[size] = plane;
    heapifyUp(size);
    size++;
}

Aircraft* MinHeap::extractMin() {
    // Remove and return highest priority aircraft
    if (size == 0) return nullptr;

    Aircraft* min = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);

    return min;
}

int MinHeap::findIndex(std::string flightID) {
    // Find aircraft index by flight ID
    for (int i = 0; i < size; i++) {
        if (heap[i]->flightID == flightID) {
            return i;
        }
    }
    return -1;
}

void MinHeap::decreaseKey(std::string flightID, Priority newPriority) {
    // Decrease priority (increase urgency) of aircraft
    int index = findIndex(flightID);
    if (index == -1) return;

    if (newPriority < heap[index]->priority) {
        heap[index]->priority = newPriority;
        heapifyUp(index);
    }
}

bool MinHeap::isEmpty() {
    return size == 0;
}

Aircraft* MinHeap::peek() {
    // View next aircraft to land without removing
    if (size == 0) return nullptr;
    return heap[0];
}

void MinHeap::displayQueue() {
    // Display landing queue
    cout << "\n==========================================================================\n";
    cout << "LANDING QUEUE (Min-Heap)\n";
    cout << "==========================================================================\n";

    if (size == 0) {
        cout << "Queue is empty!\n";
        return;
    }

    cout << "* NEXT TO LAND: " << heap[0]->flightID;
    cout << " [STATUS: ";
    switch (heap[0]->priority) {
    case CRITICAL: cout << "CRITICAL"; break;
    case HIGH: cout << "LOW FUEL"; break;
    case MEDIUM: cout << "NORMAL"; break;
    case LOW: cout << "LOW PRIORITY"; break;
    }
    cout << "] *\n---\n";

    for (int i = 1; i < size && i < 5; i++) {
        cout << i + 1 << ". " << heap[i]->flightID << " [Status: ";
        switch (heap[i]->priority) {
        case CRITICAL: cout << "CRITICAL"; break;
        case HIGH: cout << "Low Fuel"; break;
        case MEDIUM: cout << "Normal"; break;
        case LOW: cout << "Normal"; break;
        }
        cout << "]\n";
    }
}