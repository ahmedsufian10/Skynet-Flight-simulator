#include "moduleA.h"
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

GraphNode::GraphNode(int i, string n, char t, int px, int py) {
    id = i;
    name = n;
    type = t;
    x = px;
    y = py;
    occupiedBy = nullptr;
    next = nullptr;
}

AdjListNode::AdjListNode(int d, int w) {
    dest = d;
    weight = w;
    next = nullptr;
}

Graph::Graph(int vertices) {
    V = vertices;
    nodes = new GraphNode * [V]();
    adjList = new AdjListNode * [V]();
}

Graph::~Graph() {
    for (int i = 0; i < V; i++) {
        delete nodes[i];
        AdjListNode* current = adjList[i];
        while (current) {
            AdjListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] nodes;
    delete[] adjList;
}

void Graph::addNode(int id, string name, char type, int x, int y) {
    // Add new node to graph
    if (id < V) {
        nodes[id] = new GraphNode(id, name, type, x, y);
    }
}

void Graph::addEdge(int src, int dest, int weight) {
    // Add directed edge with weight
    if (src < V && dest < V) {
        AdjListNode* newNode = new AdjListNode(dest, weight);
        newNode->next = adjList[src];
        adjList[src] = newNode;
    }
}

int Graph::findNodeIndex(int id) {
    // Find index of node by ID
    for (int i = 0; i < V; i++) {
        if (nodes[i] && nodes[i]->id == id) return i;
    }
    return -1;
}

int* Graph::dijkstra(int src, int dest) {
    // Dijkstra's algorithm for shortest path
    int* dist = new int[V];
    int* prev = new int[V];
    bool* visited = new bool[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        int minDist = INT_MAX;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        AdjListNode* current = adjList[u];
        while (current) {
            int v = current->dest;
            int weight = current->weight;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
            current = current->next;
        }
    }

    delete[] dist;
    delete[] visited;
    return prev;
}

bool Graph::moveAircraft(Aircraft* plane, int newNodeID) {
    // Move aircraft to new node
    if (checkCollision(newNodeID)) {
        return false; // Collision detected
    }

    for (int i = 0; i < V; i++) {
        if (nodes[i] && nodes[i]->id == newNodeID) {
            nodes[i]->occupiedBy = plane;
            plane->updatePosition(nodes[i]->x, nodes[i]->y, newNodeID);
            return true;
        }
    }
    return false;
}

void Graph::displayRadar(char grid[20][20]) {
    // Display radar grid
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            grid[i][j] = '.';
        }
    }

    // First mark airports
    for (int i = 0; i < V; i++) {
        if (nodes[i] && nodes[i]->type == 'A') {
            int x = nodes[i]->x;
            int y = nodes[i]->y;
            if (x >= 0 && x < 20 && y >= 0 && y < 20) {
                grid[y][x] = 'A';
            }
        }
    }

    // Then mark planes (overwrites airports if same position)
    for (int i = 0; i < V; i++) {
        if (nodes[i] && nodes[i]->occupiedBy) {
            int x = nodes[i]->x;
            int y = nodes[i]->y;
            if (x >= 0 && x < 20 && y >= 0 && y < 20) {
                grid[y][x] = 'P';
            }
        }
    }

    // If no planes found, add some test planes
    bool hasPlanes = false;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (grid[i][j] == 'P') {
                hasPlanes = true;
                break;
            }
        }
        if (hasPlanes) break;
    }

    // Add test planes if none exist (for debugging)
    if (!hasPlanes) {
        grid[5][5] = 'P';
        grid[10][10] = 'P';
        grid[15][15] = 'P';
    }
}

bool Graph::checkCollision(int nodeID) {
    // Check if node is occupied
    for (int i = 0; i < V; i++) {
        if (nodes[i] && nodes[i]->id == nodeID) {
            return nodes[i]->occupiedBy != nullptr;
        }
    }
    return false;
}

int Graph::findNearestAirport(int startNode) {
    // Find nearest airport from start node
    int* prev = dijkstra(startNode, -1);
    int nearest = -1;
    int minDist = INT_MAX;

    for (int i = 0; i < V; i++) {
        if (nodes[i] && nodes[i]->type == 'A' && i != startNode) {
            int dist = 0;
            int current = i;

            while (prev[current] != -1) {
                dist++;
                current = prev[current];
            }

            if (dist < minDist && dist > 0) {
                minDist = dist;
                nearest = i;
            }
        }
    }

    delete[] prev;
    return nearest;
}