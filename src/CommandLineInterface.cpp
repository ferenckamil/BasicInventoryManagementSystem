#include "CommandLineInterface.hpp"
#include "Electronics.hpp"
#include "Groceries.hpp"
#include "Item.hpp"
#include "CLIHelpers.hpp"

#include <chrono>

CommandLineInterface::CommandLineInterface() : isRunning(true) {

    std::cout << "========================================\n";
    std::cout << " Basic Inventory Management System\n";
    std::cout << "========================================\n";
    
    if (CLIHelpers::confirm("Preload data from file?")) 
    {
        handleReadFromFile();
    } 
    else 
    {
        std::cout << "Starting with empty inventory...\n";
        CLIHelpers::pause();
    }

}

void CommandLineInterface::run() {
    while(isRunning)
    {
        displayMenu();
        handleUserInteractions();
    }
}

void CommandLineInterface::displayMenu() const {
    std::cout<<"----- MAIN MENU -----\n";
    std::cout<<"1. Add item\n";
    std::cout<<"2. Remove item\n";
    std::cout<<"3. Update Quantity\n";
    std::cout<<"4. Display Inventory\n";
    std::cout<<"5. Read from file\n";
    std::cout<<"6. Save to file\n";
    std::cout<<"7. Find most expensive item\n";
    std::cout<<"8. Find item below quantity threshold\n";
    std::cout<<"\n";
    std::cout<<"h. Display help\n";
    std::cout<<"q. Exit\n";
}

void CommandLineInterface::displayHelp() const {

    std::cout << "\n===== Basic Inventory Management System manual =====\n"
              << "This program allows you to manage an inventory of various items.\n"
              << "Available Commands:\n\n"
              << "  1. Add item\n"
              << "     Starts a wizard to add a new item. You'll need to specify the\n"
              << "     item type (e.g., ELECTRONICS, GROCERIES, ITEM) and provide\n"
              << "     all required details (ID, name, quantity, price, specific attributes).\n\n"
              << "  2. Remove item\n"
              << "     Prompts for the unique ID of the item you want to remove from the inventory.\n\n"
              << "  3. Update Quantity\n"
              << "     Prompts for the ID of the item whose quantity you want to change, then asks\n"
              << "     for the new quantity.\n\n"
              << "  4. Display Inventory\n"
              << "     Shows the complete list of items currently in the inventory, including\n"
              << "     their specific details (like warranty or expiration date).\n\n"
              << "  5. Read from file\n"
              << "     Prompts for a file path. Loads items from the specified file,\n"
              << "     adding them to the current inventory (skips duplicates).\n\n"
              << "  6. Save to file\n"
              << "     Prompts for a file path. Saves the current state of the inventory\n"
              << "     to the specified file, overwriting it if it exists.\n\n"
              << "  7. Find most expensive item\n"
              << "     Searches the inventory and displays the details of the item with the highest price.\n\n"
              << "  8. Find item below quantity threshold\n"
              << "     Prompts for a quantity. Displays all items with a quantity lower than the\n"
              << "     specified threshold.\n\n"
              << "  h. Display help\n"
              << "     Shows this help screen.\n\n"
              << "  q. Exit\n"
              << "     Prompts if you want to exit the program.\n"
              << "================================================\n";

    CLIHelpers::pause();
}

void CommandLineInterface::handleAddItem() {
    while (true) 
    {
        try 
        {
            std::cout << "Select item type:\n";
            std::cout << "1. Electronics\n";
            std::cout << "2. Groceries\n";
            std::cout << "3. Item (type not specified)\n";
            int choice = CLIHelpers::askInt("Enter choice (1-3): ", 1);
            if (choice < 1 || choice > 3)
            {
                throw std::invalid_argument("Invalid item type selection");
            }
            
            std::string itemId = CLIHelpers::askString("Enter item ID: ");
            std::string itemName = CLIHelpers::askString("Enter item name: ");
            int quantity = CLIHelpers::askInt("Enter quantity: ", 1);
            double price = CLIHelpers::askDouble("Enter price: ", 0.01);

            std::shared_ptr<Item> newItem;

            switch (choice) 
            {
                case 1: 
                {
                    std::chrono::year_month_day warrantyDate = CLIHelpers::askDate("Enter warranty expiration (YYYY-MM-DD): ");
                    newItem = std::make_shared<Electronics>(itemId, itemName, quantity, price, warrantyDate);
                    break;
                }

                case 2: 
                {
                    std::chrono::year_month_day expiryDate = CLIHelpers::askDate("Enter expiration date (YYYY-MM-DD): ");
                    newItem = std::make_shared<Groceries>(itemId, itemName, quantity, price, expiryDate);
                    break;
                }

                case 3: 
                {
                    newItem = std::make_shared<Item>(itemId, itemName, quantity, price);
                    break;
                }
            }

            if(inventory.addItem(newItem))
            {
                std::cout<<"Item created successfully!\n";
            }
            else
            {
                std::cerr << "Can not add the element with ID: " << itemId << ". Item with this ID already present in inventory. Skipping... \n";
            }
            
            if (CLIHelpers::confirm("Add another item?")) 
            {
                continue;
            }
            break;

        } catch (const std::exception& e) {
            std::cerr << "\nError: " << e.what() << "\n";
            if (!CLIHelpers::confirm("Try again?")) 
            {
                break;
            }
        }
    }
}

void CommandLineInterface::handleRemoveItem() {
    while (true) 
    {
        try 
        {
            std::string itemId = CLIHelpers::askString("Enter item ID: ");

            if(inventory.removeItem(itemId))
            {
                std::cout<<"Item removed successfully!\n";
            }
            else
            {
                std::cerr << "Can not remove the element with ID: " << itemId << ". Item not found\n";
            }
            
            if (CLIHelpers::confirm("Remove another item?")) 
            {
                continue;
            }
            break;

        } catch (const std::exception& e) {
            std::cerr << "\nError: " << e.what() << "\n";
            if (!CLIHelpers::confirm("Try again?")) 
            {
                break;
            }
        }
    }
}

void CommandLineInterface::handleUpdateQuantity() {
    while (true) 
    {
        try 
        {
            std::string itemId = CLIHelpers::askString("Enter item ID: ");
            int quantity = CLIHelpers::askInt("Enter quantity: ", 1);
            
            if(inventory.updateItem(itemId, quantity))
            {
                std::cout<<"Item updated successfully!\n";
            }
            else
            {
                std::cerr << "Can not update the element with ID: " << itemId << "\n";
            }
            
            if (CLIHelpers::confirm("Update another item?")) 
            {
                continue;
            }
            break;

        } catch (const std::exception& e) {
            std::cerr << "\nError: " << e.what() << "\n";
            if (!CLIHelpers::confirm("Try again?")) 
            {
                break;
            }
        }
    }
}

void CommandLineInterface::handleDisplayInventory() {
    inventory.displayInventory();
    CLIHelpers::pause();
}

void CommandLineInterface::handleReadFromFile() {
    while(true)
    {
        std::string filename = CLIHelpers::askString("Enter path to file: ");

        try 
        {
            inventory.readFromFile(filename); 
            std::cout << "Inventory successfully populated from the file : " << filename << "\n";
            break;
        } 
        catch (const std::exception& e) {
            std::cerr <<"Error reading from file: "<<e.what()<<". Most propably reason: incorrect path\n";
            if (!CLIHelpers::confirm("Try again?")) 
            {
                break;
            }
        }
    }
    
    CLIHelpers::pause();
}

void CommandLineInterface::handleSaveToFile() {

    while(true)
    {
        std::string filename = CLIHelpers::askString("Enter path to file: ");

        try 
        {
            inventory.saveToFile(filename); 
            std::cout<<"Inventory saved to file :"<<filename<<"\n";
            break;
        } 
        catch (const std::exception& e) {
            std::cerr<<"Error saving the file: "<<e.what()<<"\n";
            if (!CLIHelpers::confirm("Try again?")) 
            {
                break;
            }
        }
    }
    
    CLIHelpers::pause();
}

void CommandLineInterface::handleMostExpensiveItem() {
    inventory.findHighestPrice()->displayItem();
    std::cout<<"\n";
    CLIHelpers::pause();
}

void CommandLineInterface::handleItemBelowThreshold() {

    while (true) 
    {
        try 
        {
            int threshold = CLIHelpers::askInt("Enter threshold: ", 1);
            
            std::vector<const Item*> itemsFound;
            inventory.findItemsBelowQuantityThreshold(threshold, itemsFound);

            if (itemsFound.empty()) 
            {
                std::cout << "No items found\n";
            } 
            else 
            {
                std::cout << "Found " << itemsFound.size() << " item(s) below quantity " << threshold << "\n";
                std::cout << "-------------------------------------------\n";
                for (const Item* item : itemsFound) 
                {
                    if (item) 
                    {
                        item->displayItem();
                    }
                    std::cout <<'\n';
                }

                std::cout << "-------------------------------------------\n";
            }
            
            if (CLIHelpers::confirm("Check under other thresholod?")) 
            {
                continue;
            }
            break;

        } catch (const std::exception& e) {
            std::cerr << "\nError: " << e.what() << "\n";
            if (!CLIHelpers::confirm("Try again?")) 
            {
                break;
            }
        }
    }
}

void CommandLineInterface::handleUserInteractions() {
    char choice;
    
    std::cout<<"Enter option: \n";
    std::cin >> choice;

    switch(choice) {
        case '1':
            handleAddItem();
            break;
        case '2':
            handleRemoveItem();
            break;
        case '3':
            handleUpdateQuantity();
            break;
        case '4':
            handleDisplayInventory();
            break;
        case '5':
            handleReadFromFile();
            break;
        case '6':
            handleSaveToFile();
            break;
        case '7':
            handleMostExpensiveItem();
            break;
        case '8':
            handleItemBelowThreshold();
            break;
        case 'h':
        case 'H':
            displayHelp();
            break;
        case 'q':
        case 'Q': 
        {
            if (CLIHelpers::confirm("Save the inventory before leaving?")) 
            {
                handleSaveToFile();
            } 
            else 
            {
                std::cout << "Closing without saving...\n";
            }
            isRunning = false;
            break;
        } 
        default:
            std::cout<<"Incorrect option. Type h/H to print help.\n";
    }
}
