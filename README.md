# Dijkstra's Algorithm in C

## Overview

This project implements **Dijkstra's algorithm** to find the shortest path between two intersections (referred to as "carrefours") in a directed graph. The program reads a set of intersections and their corresponding travel times from an input file, and the user can interactively select the starting and ending intersection to compute the shortest path.

## Files

- **dijkstra.c**: Contains the core implementation of Dijkstra's algorithm, including:
  - `prochain_carrefour`: Finds the next intersection to consider based on the shortest cumulative time.
  - `chemin`: Computes the shortest path from the start to the destination intersection.
- **dijkstra.h**: Header file for `dijkstra.c`, declaring the main functions and constants used for the algorithm.
- **input.c**: Handles reading and parsing input data, such as intersection names and travel times between them.
- **input.h**: Header file for `input.c`, defining constants and function prototypes for input handling.
- **main.c**: The entry point of the program, which interacts with the user by reading input data, selecting the start and destination intersections, and displaying the shortest path and its duration.

## Features

- **Dynamic Memory Allocation**: The program dynamically allocates memory for storing the graph data (intersections and travel times) and the shortest path result.
- **Interactive Input**: The program allows the user to input their desired start and destination intersection names, ensuring they exist within the data set.
- **Graph Search**: Implements a version of Dijkstra’s algorithm to compute the shortest path, considering all nodes and edges.
- **Error Handling**: The program includes basic error handling for incorrect inputs or memory allocation failures.

## Learning Outcomes

Through this project, I learned:
- **Dijkstra's Algorithm**: Understanding the process of finding the shortest path in a graph with weighted edges and how priority selection (based on cumulative time) affects the outcome.
- **Memory Management in C**: Using dynamic memory allocation to handle variable-sized data structures (such as paths) and ensuring proper memory deallocation to prevent leaks.
- **Modular Programming**: Organizing the project into multiple source files and headers to separate concerns (e.g., input handling, algorithm logic).
- **Error Checking and Handling**: Implementing checks for input validity and edge cases, such as nonexistent intersections or failed memory allocations.

## How to Run

1. Compile the project using a C compiler (such as GCC):
   ```bash
   gcc main.c dijkstra.c input.c -o dijkstra

2. Run the program: ./dijkstra
