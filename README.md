# Skynet ATC Simulator

A console-based Air Traffic Control simulator written in C++. Built as a data
structures project — each module implements one core data structure, applied
to a realistic ATC problem instead of a toy example.

## What it does

- Tracks aircraft (flight ID, model, origin/destination, fuel, priority, position)
  on a 20x20 grid radar display.
- Models airspace as a graph of airports and waypoints, with weighted routes
  between them.
- Manages a landing queue ordered by emergency priority (CRITICAL > HIGH > MEDIUM > LOW).
- Looks up flights by ID instantly instead of scanning a list.
- Keeps a running, sorted flight log that can be saved to and reloaded from disk.

Run it and you get a menu-driven CLI:

```
MAIN MENU:
1. Airspace Visualizer
2. Flight Control
3. Search & Reporting
4. System Operations
5. Exit
```

## Data structures, mapped to files

| File | Data structure | Used for |
|---|---|---|
| `aircraft.h/.cpp` | Plain class | Represents a single aircraft and its state |
| `moduleA.h/.cpp` | Graph (adjacency list) + Dijkstra's algorithm | Airspace map; shortest safe route to the nearest airport |
| `moduleB.h/.cpp` | Min-heap | Priority queue for the landing queue (highest-priority emergency lands first) |
| `moduleC.h/.cpp` | Hash table (separate chaining) | O(1) average flight lookup by flight ID |
| `moduleD.h/.cpp` | AVL tree (self-balancing BST) | Flight log, kept sorted and balanced; persisted to file |
| `utils.h/.cpp` | — | Shared helpers: screen clearing, colored output, the radar grid printer, timestamps |

## Building

Requires a C++17 compiler.

**g++ / Linux / macOS / WSL:**
```bash
g++ -std=c++17 -Wall -o program main.cpp aircraft.cpp moduleA.cpp moduleB.cpp moduleC.cpp moduleD.cpp utils.cpp
./program
```

**Visual Studio (Windows):**
Add all `.cpp`/`.h` files to a new empty C++ console project and build normally
(Ctrl+Shift+B).

> Note: `utils.cpp` picks the right time function for the platform automatically
> (`localtime_s` on Windows, `localtime_r` everywhere else), so the same source
> builds on both without changes.

## Project structure

```
.
├── main.cpp        # Menu system and program entry point
├── aircraft.h/.cpp # Aircraft class
├── moduleA.h/.cpp  # Graph + Dijkstra's algorithm
├── moduleB.h/.cpp  # Min-heap priority queue
├── moduleC.h/.cpp  # Hash table
├── moduleD.h/.cpp  # AVL tree flight log
└── utils.h/.cpp    # Shared CLI helpers
```
