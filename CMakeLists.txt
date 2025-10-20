cmake_minimum_required(VERSION 3.15)
project(BasicInventoryManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(include)

# Add executable
add_executable(BasicInventoryManagementSystem
    src/Item.cpp
    src/Inventory.cpp
    src/Electronics.cpp
    src/Groceries.cpp
    src/CommandLineInterface.cpp
    src/main.cpp
)