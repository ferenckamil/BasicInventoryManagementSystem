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

When you start the program, it displays a welcome message and asks:

## Preload data from file?

- If you confirm (`y`), the program attempts to read the inventory from a file.  
- If you decline (`n`), it starts with an empty inventory.

![Start of application - positive](demo-images/0%20-start-true.PNG)
![Start of application - negative](demo-images/0%20-%20start-false.PNG)

## Menu
Application is providing simple CLI to interact with logic of system.

![MainMenu](demo-images/0%20-%20menu.PNG)

## Add Item

- Adds a new item to the inventory.
- Validates input data:
  - The date must not be in the past.
  - The ID must be unique — existing IDs are rejected.
- The user is prompted to try again.

![Add item](demo-images/1%20-add.PNG)
![Inventory after add](demo-images/1%20-add_inventory_after.PNG)

## Remove Item

- Removes an item by its ID.
- Checks input correctness.
- If the provided ID does not exist, the removal is aborted.

![Remove item](demo-images/2%20-%20remove.PNG)
![Inventory after remove](demo-images/2%20-%20remove_inventory_after.PNG)

## Update Quantity

- Updates the quantity of an existing item.
- Ensures the ID exists and the entered amount is valid.
- Invalid or non-existing IDs are rejected.

![Update item](demo-images/3%20-%20update.PNG)
![Inventory after update](demo-images/3%20-%20update_inventory_after.PNG)

## Display Inventory

- Shows a full list of all items currently in the inventory.
- Displays ID, name, quantity, price, and date of entry.

![Update item](demo-images/4%20-%20display_inventory.PNG)

## Read from File

- Reads inventory data from a file.
- Skips adding of item, if items with given IDs exist.
- Verifies that the provided file path exists before loading.
- Displays an error message if the path is invalid.

![Read](demo-images/5%20-%20read_from_file_id_exists.PNG)

## Save to File

- Saves the current inventory state to a file.
- Checks that the specified file path is valid and writable.

![Save](demo-images/6%20-%20save%20to%20file.PNG)
![Saved file](demo-images/6%20-%20file.PNG)

## Find Most Expensive Item

- Searches the inventory and returns the item with the highest price.

![MostExpensiveItem](demo-images/7%20-%20find_most_expensive.PNG)

## Find Items Below Quantity Threshold

- Returns a list of all items whose quantity is below the given threshold.
- Useful for tracking low-stock items.

![ItemBelowThreshold](demo-images/8%20-%20given%20threshold.PNG)

## Help

- Displays a summary of all available commands with a short description.

![Help](demo-images/10%20-%20help.PNG)

## Leaving the program

- If you confirm (`y`), the program attempts to save the inventory to a file.  
- If you decline (`n`), it ends with saving the state of inventory.

![End of application - positive](demo-images/9%20-%20stop-true.PNG)
![End of application - negative](demo-images/9%20-%20stop-false.PNG)