#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

void clearScreen();
void printHeader();
void printRadar(char grid[20][20]);
void printColored(std::string text, int colorCode);
std::string getCurrentTime();

#endif