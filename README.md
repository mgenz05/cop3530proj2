# medicine-prescriber-heap-efficiency-comparison-cpp-2025

A C++ project created for demonstrating the performance differences between Min Heap and Max Heap data structures when used to compute the optimal medicine recommendation based on user selected criteria. This project includes a graphical interface built with wxWidgets, a custom max heap implementation with an imported min heap implementation, and a scoring system that evaluates medicines from a dataset to determine the best match.
The application loads a CSV based medicine database, computes match scores using both heap types, and displays execution time comparisons to highlight efficiency differences.

## Tech Stack
- C++: Used for heap implementation, scoring logic, and application structure
- wxWidgets: GUI framework used to build the interactive interface
- Custom Max Heap implemented manually using vectors
- Imported Min Heap using priority queues
- CLion IDE: Used for development, debugging, and project organization
- CMake: Build configuration for cross platform compilation

## Highlights
- Implements MaxHeap and MinHeap structures to compare performance on identical workloads
- Uses a medicine scoring algorithm to evaluate how well each medicine matches user selected criteria
- Integrates wxWidgets to provide a clean, interactive GUI for input selection and result display
- Displays execution time comparisons between heap types using chrono
- Loads and parses a CSV dataset into an efficient unordered map for fast lookup
- Demonstrates practical use of heaps in real world scenarios

## Learning Objectives
- Strengthen understanding of heap data structures, including manual MaxHeap implementation and priority queue based MinHeap
- Apply algorithmic thinking to compute match scores and evaluate performance trade offs
- Use wxWidgets to build multi-screen GUI applications in C++
- Practice file parsing, data structuring, and efficient lookups using unordered map
- Reinforce concepts of runtime measurement, profiling, and comparative analysis
