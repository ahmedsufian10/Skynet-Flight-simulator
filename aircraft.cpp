#include "aircraft.h"
#include <iostream>
using namespace std;

Aircraft::Aircraft() : fuelLevel(100), priority(MEDIUM), status(IN_AIR), x(0), y(0), nodeID(0) {}

Aircraft::Aircraft(string id, string mdl, string org, string dest,
    int fuel, Priority pri, int nx, int ny) {
    flightID = id;
    model = mdl;
    origin = org;
    destination = dest;
    fuelLevel = fuel;
    priority = pri;
    status = IN_AIR;
    x = nx;
    y = ny;
    nodeID = 0;
}

void Aircraft::declareEmergency(Priority newPriority) {
    // Change priority for emergency
    priority = newPriority;
    if (newPriority == CRITICAL) {
        fuelLevel = 5; // Emergency fuel level
    }
}

void Aircraft::updateFuel(int newFuel) {
    // Update fuel and adjust priority if low
    fuelLevel = newFuel;
    if (fuelLevel < 10) {
        priority = HIGH;
    }
}

void Aircraft::updatePosition(int newX, int newY, int newNodeID) {
    // Update aircraft position
    x = newX;
    y = newY;
    nodeID = newNodeID;
}

void Aircraft::printInfo() const {
    // Print aircraft information
    cout << "\n| Flight ID : " << flightID;
    cout << "\n| Model     : " << model;
    cout << "\n| Origin    : " << origin;
    cout << "\n| Fuel      : " << fuelLevel << "%";
    cout << "\n| Status    : ";
    switch (status) {
    case IN_AIR: cout << "IN AIR"; break;
    case LANDED: cout << "LANDED"; break;
    case CRASHED: cout << "CRASHED"; break;
    }
    cout << "\n| Priority  : " << priority;
    cout << "\n| Position  : (" << x << "," << y << ")";
    cout << "\n------------------------\n";
}