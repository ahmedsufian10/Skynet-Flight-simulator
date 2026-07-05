#include "utils.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

void clearScreen() {
    // Clear console screen
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader() {
    // Print application header
    cout << "\n========================================\n";
    cout << "      SKYNET ATC SIMULATOR v1.0\n";
    cout << "========================================\n";
}

void printRadar(char grid[20][20]) {
    // Print radar grid with borders
    cout << "\n       AIRSPACE RADAR (20x20)\n";
    cout << "     ";
    for (int i = 0; i < 20; i++) cout << "--";
    cout << "-\n";

    for (int i = 0; i < 20; i++) {
        cout << "    |";
        for (int j = 0; j < 20; j++) {
            if (grid[i][j] == 'A') {
                cout << "A "; // Green for airports
            }
            else if (grid[i][j] == 'P') {
                cout << "P "; // Red for planes
            }
            else {
                cout << grid[i][j] << " ";
            }
        }
        cout << "|\n";
    }

    cout << "     ";
    for (int i = 0; i < 20; i++) cout << "--";
    cout << "-\n";
    cout << "Legend: A=Airport, P=Plane, .=Empty\n";
}

void printColored(string text, int colorCode) {
    // Print colored text
#ifndef _WIN32
    cout << "\033[" << colorCode << "m" << text << "\033[0m";
#else
// For Windows, just print plain text or use Windows API
    cout << text;
#endif
}

string getCurrentTime() {
    // Get current time as string
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // localtime_s (Windows/MSVC) and localtime_r (Linux/macOS/POSIX) do the
    // same job but have different names AND different argument order, so we
    // pick the right one at compile time depending on platform.
    struct tm local_time;
#ifdef _WIN32
    localtime_s(&local_time, &now_time);       // Windows: (dest, source)
#else
    localtime_r(&now_time, &local_time);       // POSIX:   (source, dest)
#endif

    stringstream ss;
    ss << put_time(&local_time, "%H:%M");
    return ss.str();
}