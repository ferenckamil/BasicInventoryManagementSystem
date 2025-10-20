#pragma once

#include <string>
#include <iostream>

#include "Inventory.hpp"

class CommandLineInterface
{
private:
    Inventory inventory;

    bool isRunning;

    //start menu and help
    void displayMenu() const;
    void displayHelp() const;

    //function to handle user inputs
    void handleUserInteractions();

    //functions for each menu cases
    void handleAddItem();
    void handleRemoveItem();
    void handleUpdateQuantity();
    void handleDisplayInventory();
    void handleReadFromFile();
    void handleSaveToFile();
    void handleMostExpensiveItem();
    void handleItemBelowThreshold();


public:
    CommandLineInterface();
    void run();

};
