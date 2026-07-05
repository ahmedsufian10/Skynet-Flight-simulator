#pragma once

#include <string>

enum Priority { CRITICAL = 1, HIGH = 2, MEDIUM = 3, LOW = 4 };
enum Status { IN_AIR, LANDED, CRASHED };

class Aircraft {
public:
    std::string flightID;
    std::string model;
    std::string origin;
    std::string destination;
    int fuelLevel;
    Priority priority;
    Status status;
    int x, y; // Grid position
    int nodeID; // Graph node position

    Aircraft();
    Aircraft(std::string id, std::string mdl, std::string org, std::string dest,
        int fuel, Priority pri, int nx, int ny);

    void declareEmergency(Priority newPriority);
    void updateFuel(int newFuel);
    void updatePosition(int newX, int newY, int newNodeID);
    void printInfo() const;
};

