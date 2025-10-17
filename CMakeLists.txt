cmake_minimum_required(VERSION 3.15)
project(BasicInventoryManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(include)

# Add executable
add_executable(BasicInventoryManagementSystem
    src/item.cpp
    src/inventory.cpp
    src/main.cpp
)