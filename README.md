# BasicInventoryManagementSystem

C++ application that models a basic inventory management system for a store. The system manages information about items using classes and handles basic file input/output operations.

## Features

- Add, remove, and update items in the inventory
- Save inventory data to a file
- Load inventory data from a file
- Basic console-based user interface

## Project Structure

BasicInventoryManagementSystem/
├── src/ # Source files
├── include/ # Header files
├── CMakeLists.txt # CMake build configuration
└── README.md # Project description


## Requirements

- C++17 or higher
- CMake 3.15+
- Git (for version control)

## Build Instructions

```bash
#Clone the repository
git clone https://github.com/ferenckamil/BasicInventoryManagementSystem.git
cd BasicInventoryManagementSystem

# Create build directory
cmake -S . -B build

# Build project
cmake --build build

# Run application
./build/BasicInventoryManagementSystem.exe

```

## Usage

Follow the on-screen instructions to:
- Add, remove, or update inventory items
- View the current inventory
- Save or load inventory data from files

## Improvements

- Add unit tests
- Add the dockerfile to run the application in the container