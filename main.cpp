#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "aircraft.h"
#include "moduleA.h"
#include "moduleB.h"
#include "moduleC.h"
#include "moduleD.h"
#include "utils.h"

using namespace std;

// Global variables
Graph* airspace;
MinHeap* landingQueue;
HashTable* aircraftRegistry;
AVLTree* flightLog;
int nextNodeID = 0;
int aircraftCount = 0;

void initializeSystem() {
    // Initialize all systems
    airspace = new Graph(50);
    landingQueue = new MinHeap(50);
    aircraftRegistry = new HashTable(50);
    flightLog = new AVLTree();

    srand((unsigned int)time(0)); // Seed random number generator

    // Add airports
    airspace->addNode(nextNodeID++, "JFK", 'A', 5, 5);
    airspace->addNode(nextNodeID++, "LHR", 'A', 15, 15);
    airspace->addNode(nextNodeID++, "DXB", 'A', 10, 10);

    // Add waypoints
    for (int i = 0; i < 15; i++) {
        airspace->addNode(nextNodeID++, "WP" + to_string(i), 'W', rand() % 20, rand() % 20);
    }

    // Add edges
    for (int i = 0; i < nextNodeID; i++) {
        for (int j = 0; j < nextNodeID; j++) {
            if (i != j && rand() % 3 == 0) {
                airspace->addEdge(i, j, rand() % 50 + 10);
            }
        }
    }

    // Create initial planes for testing
    Aircraft* plane1 = new Aircraft("PK-786", "Boeing777", "Lahore", "Dubai", 5, CRITICAL, 2, 3);
    Aircraft* plane2 = new Aircraft("UA-909", "Airbus320", "NewYork", "London", 8, HIGH, 10, 8);
    Aircraft* plane3 = new Aircraft("BA-101", "Boeing747", "London", "Paris", 60, MEDIUM, 15, 12);

    // Place planes on random graph nodes
    int waypoint1 = 3;  // First waypoint
    int waypoint2 = 7;  // Second waypoint  
    int waypoint3 = 10; // Third waypoint

    if (waypoint1 < nextNodeID) airspace->moveAircraft(plane1, waypoint1);
    if (waypoint2 < nextNodeID) airspace->moveAircraft(plane2, waypoint2);
    if (waypoint3 < nextNodeID) airspace->moveAircraft(plane3, waypoint3);

    // Add to systems
    landingQueue->insert(plane1);
    landingQueue->insert(plane2);
    landingQueue->insert(plane3);

    aircraftRegistry->insert("PK-786", plane1);
    aircraftRegistry->insert("UA-909", plane2);
    aircraftRegistry->insert("BA-101", plane3);
}

void displayMenu() {
    // Display main menu
    clearScreen();
    printHeader();

    char radar[20][20];
    airspace->displayRadar(radar);
    printRadar(radar);

    cout << "\nMAIN MENU:\n";
    cout << "1. Airspace Visualizer\n";
    cout << "2. Flight Control\n";
    cout << "3. Search & Reporting\n";
    cout << "4. System Operations\n";
    cout << "5. Exit\n";
    cout << "\nEnter choice: ";
}

void airspaceVisualizer() {
    // Display airspace visualizer
    clearScreen();
    printHeader();

    char radar[20][20];
    airspace->displayRadar(radar);
    printRadar(radar);

    landingQueue->displayQueue();

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void addNewFlight() {
    // Add new flight to system
    clearScreen();
    printHeader();

    string id, model, origin, dest;
    int fuel, priorityChoice;

    cout << "\nADD NEW FLIGHT:\n";
    cout << "Flight ID (e.g., PK-786): ";
    cin >> id;
    cout << "Model: ";
    cin >> model;
    cout << "Origin: ";
    cin >> origin;
    cout << "Destination: ";
    cin >> dest;
    cout << "Initial Fuel %: ";
    cin >> fuel;

    cout << "\nPriority:\n";
    cout << "1. CRITICAL (Medical Emergency)\n";
    cout << "2. HIGH (Low Fuel)\n";
    cout << "3. MEDIUM (Commercial)\n";
    cout << "4. LOW (Cargo/Private)\n";
    cout << "Choice: ";
    cin >> priorityChoice;

    Priority pri = MEDIUM;
    switch (priorityChoice) {
    case 1: pri = CRITICAL; break;
    case 2: pri = HIGH; break;
    case 3: pri = MEDIUM; break;
    case 4: pri = LOW; break;
    }

    // Create aircraft with random position
    int randX = rand() % 20;
    int randY = rand() % 20;
    Aircraft* newPlane = new Aircraft(id, model, origin, dest, fuel, pri, randX, randY);

    // Place on a random available waypoint
    // Find an empty waypoint
    bool placed = false;
    for (int i = 3; i < nextNodeID && !placed; i++) { // Start from 3 (after airports)
        if (!airspace->checkCollision(i)) {
            airspace->moveAircraft(newPlane, i);
            placed = true;
            cout << "\nPlaced on waypoint " << i << "\n";
        }
    }

    if (!placed) {
        cout << "\nWarning: Could not place on graph node. Showing on radar only.\n";
    }

    // Add to systems
    landingQueue->insert(newPlane);
    aircraftRegistry->insert(id, newPlane);

    cout << "\nFlight " << id << " added successfully!\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void declareEmergency() {
    // Declare emergency for flight
    clearScreen();
    printHeader();

    string flightID;
    cout << "\nDECLARE EMERGENCY:\n";
    cout << "Enter Flight ID: ";
    cin >> flightID;

    Aircraft* plane = aircraftRegistry->search(flightID);
    if (plane) {
        cout << "\nEmergency Type:\n";
        cout << "1. Medical Emergency\n";
        cout << "2. Engine Failure\n";
        cout << "3. Low Fuel\n";
        cout << "Choice: ";
        int choice;
        cin >> choice;

        Priority newPri = CRITICAL;
        if (choice == 3) newPri = HIGH;

        landingQueue->decreaseKey(flightID, newPri);
        plane->declareEmergency(newPri);

        cout << "\nEmergency declared for flight " << flightID << "!\n";
    }
    else {
        cout << "\nFlight not found!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void landFlight() {
    // Land the next flight
    clearScreen();
    printHeader();

    Aircraft* plane = landingQueue->extractMin();
    if (plane) {
        plane->status = LANDED;
        flightLog->insert(plane->flightID, getCurrentTime(), "Landed safely");

        // Remove from graph node
        // (In full implementation, you'd clear the node occupation)

        cout << "\n> Command: extract-min\n";
        cout << "> LANDING Flight " << plane->flightID << "... SUCCESS.\n";
    }
    else {
        cout << "\nNo flights in landing queue!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void searchFlight() {
    // Search for flight by ID
    clearScreen();
    printHeader();

    string flightID;
    cout << "\nSEARCH FLIGHT:\n";
    cout << "Enter Flight ID: ";
    cin >> flightID;

    cout << "\nSEARCHING DATABASE... ";
    Aircraft* plane = aircraftRegistry->search(flightID);

    if (plane) {
        cout << "FOUND.\n";
        cout << "------------------------\n";
        plane->printInfo();
    }
    else {
        cout << "NOT FOUND.\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void calculateSafeRoute() {
    // Calculate safe route to nearest airport
    clearScreen();
    printHeader();

    string flightID;
    cout << "\nCALCULATE SAFE ROUTE:\n";
    cout << "Enter Flight ID: ";
    cin >> flightID;

    Aircraft* plane = aircraftRegistry->search(flightID);
    if (plane) {
        int nearestAirport = airspace->findNearestAirport(plane->nodeID);
        if (nearestAirport != -1) {
            cout << "\nCALCULATING PATH TO NEAREST AIRPORT...\n";
            cout << "---\n";
            cout << "Start: Node " << plane->nodeID << "\n";
            cout << "Destination: Airport (Node " << nearestAirport << ")\n";
            cout << "---\n";
            cout << "Path calculated using Dijkstra's Algorithm\n";
        }
        else {
            cout << "\nNo airport reachable!\n";
        }
    }
    else {
        cout << "\nFlight not found!\n";
    }

    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void flightControlMenu() {
    // Flight control submenu
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "\nFLIGHT CONTROL:\n";
        cout << "1. Add New Flight\n";
        cout << "2. Declare Emergency\n";
        cout << "3. Land Next Flight\n";
        cout << "4. View Landing Queue\n";
        cout << "5. Back to Main Menu\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addNewFlight(); break;
        case 2: declareEmergency(); break;
        case 3: landFlight(); break;
        case 4:
            clearScreen();
            printHeader();
            landingQueue->displayQueue();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 5: break;
        default:
            cout << "Invalid choice!\n";
            cin.ignore();
            cin.get();
        }
    } while (choice != 5);
}

void searchReportingMenu() {
    // Search and reporting submenu
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "\nSEARCH & REPORTING:\n";
        cout << "1. Search Flight by ID\n";
        cout << "2. Print Daily Flight Log\n";
        cout << "3. Calculate Safe Route\n";
        cout << "4. Back to Main Menu\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: searchFlight(); break;
        case 2:
            clearScreen();
            printHeader();
            flightLog->displayDailyReport();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 3: calculateSafeRoute(); break;
        case 4: break;
        default:
            cout << "Invalid choice!\n";
            cin.ignore();
            cin.get();
        }
    } while (choice != 4);
}

void systemOperationsMenu() {
    // System operations submenu
    int choice;
    do {
        clearScreen();
        printHeader();

        cout << "\nSYSTEM OPERATIONS:\n";
        cout << "1. Save System State\n";
        cout << "2. Load System State\n";
        cout << "3. Back to Main Menu\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            flightLog->saveToFile("skynet_save.txt");
            cout << "\nSystem state saved!\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 2:
            flightLog->loadFromFile("skynet_save.txt");
            cout << "\nSystem state loaded!\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 3: break;
        default:
            cout << "Invalid choice!\n";
            cin.ignore();
            cin.get();
        }
    } while (choice != 3);
}

int main() {
    // Main program entry point
    initializeSystem();

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: airspaceVisualizer(); break;
        case 2: flightControlMenu(); break;
        case 3: searchReportingMenu(); break;
        case 4: systemOperationsMenu(); break;
        case 5:
            cout << "\nThank you for using SkyNet ATC Simulator!\n";
            break;
        default:
            cout << "Invalid choice! Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 5);

    // Cleanup
    delete airspace;
    delete landingQueue;
    delete aircraftRegistry;
    delete flightLog;

    return 0;
}