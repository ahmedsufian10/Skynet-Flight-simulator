#ifndef MODULEA_H
#define MODULEA_H

#include "aircraft.h"
#include <string>


struct GraphNode {
    int id;
    std::string name;
    char type; // 'A' for Airport, 'W' for Waypoint
    int x, y; // Grid coordinates
    Aircraft* occupiedBy; // For collision detection
    GraphNode* next;

    GraphNode(int i, std::string n, char t, int px, int py);
};

struct AdjListNode {
    int dest;
    int weight;
    AdjListNode* next;

    AdjListNode(int d, int w);
};

class Graph {
private:
    int V;
    GraphNode** nodes;
    AdjListNode** adjList;

    int findNodeIndex(int id);

public:
    Graph(int vertices);
    ~Graph();

    int getRandomWaypoint();
    void placeAircraftRandomly(Aircraft* plane);
    void addNode(int id, std::string name, char type, int x, int y);
    void addEdge(int src, int dest, int weight);
    int* dijkstra(int src, int dest);
    bool moveAircraft(Aircraft* plane, int newNodeID);
    void displayRadar(char grid[20][20]);
    bool checkCollision(int nodeID);
    int findNearestAirport(int startNode);
};

#endif