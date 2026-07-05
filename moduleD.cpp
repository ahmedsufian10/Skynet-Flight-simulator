#include "moduleD.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

FlightLog::FlightLog(string id, string time, string stat) {
    flightID = id;
    timestamp = time;
    status = stat;
    left = nullptr;
    right = nullptr;
    height = 1;
}

AVLTree::AVLTree() {
    root = nullptr;
}

int AVLTree::getHeight(FlightLog* node) {
    // Get height of node
    return node ? node->height : 0;
}

int AVLTree::getBalance(FlightLog* node) {
    // Get balance factor
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

FlightLog* AVLTree::rightRotate(FlightLog* y) {
    // Right rotation for AVL balance
    FlightLog* x = y->left;
    FlightLog* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

FlightLog* AVLTree::leftRotate(FlightLog* x) {
    // Left rotation for AVL balance
    FlightLog* y = x->right;
    FlightLog* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

FlightLog* AVLTree::insertNode(FlightLog* node, FlightLog* newLog) {
    // Insert node into AVL tree
    if (!node) return newLog;

    if (newLog->timestamp < node->timestamp) {
        node->left = insertNode(node->left, newLog);
    }
    else if (newLog->timestamp > node->timestamp) {
        node->right = insertNode(node->right, newLog);
    }
    else {
        return node; // Duplicate timestamps not allowed
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && newLog->timestamp < node->left->timestamp) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && newLog->timestamp > node->right->timestamp) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && newLog->timestamp > node->left->timestamp) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && newLog->timestamp < node->right->timestamp) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(string flightID, string timestamp, string status) {
    // Public insert method
    FlightLog* newLog = new FlightLog(flightID, timestamp, status);
    root = insertNode(root, newLog);
}

void AVLTree::inOrderTraversal(FlightLog* node) {
    // In-order traversal for chronological display
    if (node) {
        inOrderTraversal(node->left);
        cout << "[" << node->timestamp << "] Flight " << node->flightID
            << " -> " << node->status << ".\n";
        inOrderTraversal(node->right);
    }
}

void AVLTree::displayDailyReport() {
    // Display all flight logs
    cout << "\n--- DAILY FLIGHT LOG =================\n";
    if (!root) {
        cout << "No flights logged today.\n";
    }
    else {
        inOrderTraversal(root);
    }
    cout << "-------------------------------------\n";
}

FlightLog* AVLTree::minValueNode(FlightLog* node) {
    // Find node with minimum timestamp
    FlightLog* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

void AVLTree::saveToFile(string filename) {
    // Save AVL tree to file
    ofstream file(filename);
    if (!file) return;

    file << "AVL Tree data saved\n";
    file.close();
}

void AVLTree::loadFromFile(string filename) {
    // Load AVL tree from file
    ifstream file(filename);
    if (!file) return;

    string line;
    while (getline(file, line)) {
        // Parse and insert
    }
    file.close();
}