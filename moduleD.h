#ifndef MODULED_H
#define MODULED_H

#include <string>

struct FlightLog {
    std::string flightID;
    std::string timestamp;
    std::string status;
    FlightLog* left;
    FlightLog* right;
    int height;

    FlightLog(std::string id, std::string time, std::string stat);
};

class AVLTree {
private:
    FlightLog* root;

    int getHeight(FlightLog* node);
    int getBalance(FlightLog* node);
    FlightLog* rightRotate(FlightLog* y);
    FlightLog* leftRotate(FlightLog* x);
    FlightLog* insertNode(FlightLog* node, FlightLog* newLog);
    void inOrderTraversal(FlightLog* node);
    FlightLog* minValueNode(FlightLog* node);

public:
    AVLTree();

    void insert(std::string flightID, std::string timestamp, std::string status);
    void displayDailyReport();
    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);
};

#endif