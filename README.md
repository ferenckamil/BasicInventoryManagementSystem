# BasicInventoryManagementSystem

C++ application that models a basic inventory management system for a store. The system manages information about items using classes and handles basic file input/output operations.

## Features

- Add, remove, and update items in the inventory
- Save inventory data to a file
- Load inventory data from a file
- Basic console-based user interface

## Project Structure
```
BasicInventoryManagementSystem/
├── include/ # Header files
|   ├── CLIHelpers.hpp
|   ├── CommandLineInterface.hpp
|   ├── Electronics.hpp
|   ├── Groceries.hpp
|   ├── Inventory.hpp
|   └── Item.hpp
├── src/ # Source files
|   ├── CLIHelpers.cpp
|   ├── CommandLineInterface.cpp
|   ├── Electronics.cpp
|   ├── Groceries.cpp
|   ├── Inventory.cpp
|   ├── Item.cpp
|   └── main.cpp
├── text-files/ # TXT file to populate inventory and sample output file with saved inventory
|   ├── input.txt
|   └── output.txt
├── CMakeLists.txt # CMake build configuration
└── README.md # Project description
```

## Requirements

- C++20 or higher
- CMake 3.15+
- Git (for version control)

For Windows:
- VS Code with extensions:
  - C/C++ (Microsoft)
  - CMake Tools (Microsoft)
- MinGW-w64 standalone

## Usage

Follow the on-screen instructions to:
- Add, remove, or update inventory items
- View the current inventory
- Save or load inventory data from files
- Display the item with highest price
- List the items from the inventory below given threshold

# Demo

TODO

