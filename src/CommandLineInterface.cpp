#include "CommandLineInterface.hpp"
#include "Electronics.hpp"
#include "Groceries.hpp"
#include "Item.hpp"

#include <chrono>

CommandLineInterface::CommandLineInterface() : isRunning(true) {
    char choice = 'n';
    std::cout << "========================================\n";
    std::cout << " Basic Inventory Management System\n";
    std::cout << "========================================\n";
    std::cout << "Preload data from file? (y/n): ";
    
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    if (std::tolower(choice) == 'y') 
    {
        std::string filename;
        std::cout << "Enter path to file: ";

        std::getline(std::cin, filename); 

        if (filename.empty()) {
            std::cerr << "File name empty, starting with empty inventory...\n";
        } else {
            try {
                inventory.readFromFile(filename); 
                
                std::cout << "Inventory successfully populated from the file : " << filename << "\n";
            } 
            catch (const std::exception& e) {
                std::cerr <<"Error reading from file: "<<e.what()<<". Most propably reason: incorrect path\n";
                std::cerr << "Starting with empty inventory...\n";
            }
        }
    } else {
        std::cout << "Starting with empty inventory...\n";
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.get(); // Czeka na Enter
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

    std::cout<<"Press Enter to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

//TODO:

//refactor common parts of each function by creation of helper functions


void CommandLineInterface::handleAddItem() {
    char runAgain = 'y';
    do
    {
        std::string itemType, itemId, itemName;
        double price = -1.0; 
        int quantity = -1;

        bool inputError = false;

        std::shared_ptr<Item> newItem = nullptr;

        std::cout<<"Adding new item...\n";

        std::cout<<"Insert item type (supported types are: \"ELECTRONICS\", \"GROCERIES\", \"ITEM\"):\n"; 
        std::cin >> itemType;

        for (char &c : itemType) {
            c = std::toupper(static_cast<unsigned char>(c));
        }

        if (itemType != "ELECTRONICS" && itemType != "GROCERIES" && itemType != "ITEM") {
            std::cerr << "Unknown item type '" << itemType << "'.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            inputError = true;
        }

        if (!inputError) 
        {
            std::cout<<"Insert item ID:\n"; 
            std::cin >> itemId;
            if (itemId.empty() || itemId.find(' ') != std::string::npos) 
            {
                std::cerr << "Item ID can not be empty or containing spaces\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                inputError = true;
            } 
        }        
        
        if (!inputError) 
        {
            std::cout<<"Insert item name:\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, itemName);
            if (itemName.empty()) {
                std::cerr << "Name can not be empty.\n";
                inputError = true;
            }
        }

        if (!inputError) 
        {
            std::cout<<"Insert item price (supported format are: X / X.Y):\n";
            std::cin >> price;
            if (std::cin.fail() || price <= 0.0) {
                std::cerr << "Price can not be less or equal zero\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                inputError = true;
            }
        }
        
        if (!inputError) 
        {
            std::cout<<"Insert item quantity:\n"; 
            std::cin >> quantity;
            if (std::cin.fail() || quantity <= 0) {
                std::cerr << "Quantity can not be less or equal zero\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                inputError = true;
            }
        }

        if (!inputError) {
            try {
                if (itemType == "ELECTRONICS") 
                {
                    std::chrono::year_month_day warrantyPeriod;
                    std::string dateStr;
                    
                    std::cout << "Insert warranty period (supported format is RRRR-MM-DD): \n";
                    std::cin >> dateStr;

                    std::stringstream ss(dateStr);
                    ss >> std::chrono::parse("%F", warrantyPeriod);
                    if (ss.fail() || !warrantyPeriod.ok()) 
                    {
                        throw std::runtime_error("Invalid warranty period format");
                    }
                        
                    newItem = std::make_shared<Electronics>(itemId, itemName, quantity, price, warrantyPeriod);
                } 
                else if (itemType == "GROCERIES") 
                {
                    std::chrono::year_month_day expirationDate;
                    std::string dateStr;
                    
                    std::cout << "Insert expiration date (supported format is RRRR-MM-DD): \n";
                    std::cin >> dateStr;

                    std::stringstream ss(dateStr);
                    ss >> std::chrono::parse("%F", expirationDate);
                    if (ss.fail() || !expirationDate.ok()) 
                    {
                        throw std::runtime_error("Invalid expiration date format");
                    }
                        
                    newItem = std::make_shared<Groceries>(itemId, itemName, quantity, price, expirationDate);
                } 
                else
                {
                    newItem = std::make_shared<Item>(itemId, itemName, quantity, price);
                }
                
                if(inventory.addItem(newItem))
                {
                    std::cout<<"Item created successfully!\n";
                }
                else
                {
                    std::cerr << "Can not add the element with ID: " << itemId << ". Item with this ID already present in inventory. Skipping... \n";
                }
            }
            catch (const std::exception& e)
            {
                std::cerr<<"Incorrect input data: "<<e.what()<<"\n";
                if(std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
        
        std::cout << "Add another item? (y/n): \n";
        std::cin >> runAgain;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    } while (std::tolower(runAgain) == 'y');

    std::cout<<"Press Enter to continue...\n";
    std::cin.get();

}

void CommandLineInterface::handleRemoveItem() {
    char runAgain = 'y'; 
    do
    {
        std::string itemId;

        std::cout<<"Insert item ID to remove:\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, itemId);

        if (itemId.empty() || itemId.find(' ') != std::string::npos) 
        {
            std::cerr << "Item ID can not be empty or containing spaces\n";
        }
        else
        {
            if(inventory.removeItem(itemId))
            {
                std::cout<<"Item removed successfully!\n";
            }
        else
            {
                std::cerr << "Can not remove the element with ID: " << itemId << ". Item not found\n";
            }
        }

        
        std::cout << "Remove another item? (y/n): \n";
        std::cin >> runAgain;

    } while (std::tolower(runAgain) == 'y');

    std::cout<<"Press Enter to continue...\n";
    std::cin.get();
}

void CommandLineInterface::handleUpdateQuantity() {
    char runAgain = 'y';
    do
    {   
        std::string itemId;
        int quantity = -1;

        bool inputError = false;

        std::cout<<"Insert item ID that should be update:\n"; 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, itemId);

        if (itemId.empty() || itemId.find(' ') != std::string::npos) 
        {
            std::cerr << "Item ID can not be empty or containing spaces. Press Enter to continue...\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            inputError = true;
        }

        if (!inputError) 
        {
            std::cout<<"Insert new quantity for item:\n"; 
            std::cin >> quantity;
            if (std::cin.fail() || quantity < 0) {
                std::cerr << "Quantity can not be less or equal zero. Press Enter to continue...\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                inputError = true;
            }
        }

        if (!inputError) 
        {
            try 
            {
                if(inventory.updateItem(itemId, quantity))
                {
                    std::cout<<"Item updated successfully!\n";
                }
                else
                {
                    std::cerr << "Can not update the element with ID: " << itemId << "\n";
                }
            }
            catch (const std::invalid_argument& e)
            {
                std::cerr << "Error during update: " << e.what() << std::endl;
            }
        }

        std::cout << "Update quantity for another item? (y/n): \n";
        std::cin >> runAgain; 

    } while (std::tolower(runAgain) == 'y');

    std::cout<<"Press Enter to continue...\n";
    std::cin.get();
}

void CommandLineInterface::handleDisplayInventory() {
    inventory.displayInventory();

    std::cout<<"Press Enter to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void CommandLineInterface::handleReadFromFile() {
    std::string inputFile;

    bool isReadCorrect = false;

    while(!isReadCorrect) {
        isReadCorrect = false;

        std::cout<<"Insert a path to the input file: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, inputFile);

        if (inputFile.empty()) {
            std::cout << "Read from file canceled.\n";
            isReadCorrect = true;
            continue;
        }

        try {     
            inventory.readFromFile(inputFile);
            std::cout<<"Inventory successfully populated from the file :"<<inputFile<<"\n";
            inventory.displayInventory();
            isReadCorrect = true;
        } 
        catch (const std::runtime_error& e) {
            std::cerr<<"Error reading from file: "<<e.what()<<". Most propably reason: incorrect path\n";

            char runAgain = 'n';
            std::cout << "Try again? (y/n): \n";
            std::cin >> runAgain;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::tolower(runAgain) != 'y') {
                std::cout << "Read from file aborted\n";
                isReadCorrect = true;
            } 
        } catch (const std::exception& e) {
            std::cerr<<"Error reading from file: "<<e.what()<<"\n";
            isReadCorrect = true; 
        }
    }
    
    std::cout<<"Press any key to continue...\n";
    std::cin.get();

}

void CommandLineInterface::handleSaveToFile() {
    std::string outputFile;
    bool isWriteCorrect = false;

    while(!isWriteCorrect) {
        std::cout<<"Insert a path where output file will be stored: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, outputFile);

        if (outputFile.empty()) {
            std::cout << "Save to file canceled.\n";
            isWriteCorrect = true;
            continue;
        }

        if (outputFile.find(' ') != std::string::npos) {
             std::cerr << "Error: Path cannot contain spaces.\n";
             char runAgain = 'n';
             std::cout << "Try entering the path again? (y/n): ";
             std::cin >> runAgain;
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             if (std::tolower(runAgain) != 'y') {
                 std::cout << "Save to file aborted.\n";
                 isWriteCorrect = true;
             }
             continue; 
        }

        try{
            inventory.saveToFile(outputFile);
            std::cout<<"Inventory saved to file :"<<outputFile<<"\n";
        }
        catch (const std::runtime_error& e)
        {
            std::cerr<<"Error saving the file: "<<e.what()<<"\n";
            char runAgain = 'n';
            std::cout << "Try again? (y/n): ";
            std::cin >> runAgain;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::tolower(runAgain) != 'y') {
                std::cout << "Save to file aborted.\n";
                isWriteCorrect = true;
            }
        }
    }

    std::cout<<"Insert a path where output file will be stored: \n";
    std::cin >> outputFile;

    try{
        inventory.saveToFile(outputFile);
        std::cout<<"Inventory saved to file :"<<outputFile<<"\n";
    }
    catch (const std::runtime_error& e)
    {
        std::cerr<<"Error saving the file: "<<e.what()<<"\n";
    }

    std::cout<<"Press any key to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void CommandLineInterface::handleMostExpensiveItem() {
    std::cout<<"Showing most expensive item: \n";

    inventory.findHighestPrice()->displayItem();

    std::cout<<"\n";

    std::cout<<"Press Enter to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void CommandLineInterface::handleItemBelowThreshold() {
    int threshold = -1;

    bool inputError = false;
    char runAgain = 'y';

    do {
        runAgain = 'n';
        inputError = false;

        std::cout << "Enter the quantity threshold: \n";
        std::cin >> threshold;

        if (std::cin.fail() || threshold < 0) {
                std::cerr << "Threshold can not be less or equal zero\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                inputError = true;
            }

        if (inputError) {
            std::cout << "Try again? (y/n): ";
            std::cin >> runAgain;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (std::tolower(runAgain) != 'y') {
                std::cout << "Aborted\n";
                std::cout << "Press Enter to continue...\n";
                std::cin.get();
                return;
            }
        }

    } while (inputError && std::tolower(runAgain) == 'y'); 

    
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

    std::cout<<"Press Enter to continue...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void CommandLineInterface::handleUserInteractions() {
    char choice;
    
    std::cout<<"Enter option: \n";
    std::cin >> choice;

    switch(choice)
    {
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
            char saveChoice = 'n';

            std::cout << "Save inventory before leaving? (y/n): ";
            std::cin >> saveChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::tolower(saveChoice) == 'y') {
                std::cout << "Saving...\n";
                handleSaveToFile();
            } else {
                std::cout << "Inventory not save. Closing program\n";
            }
            isRunning = false;
            break;
        } 
        default:
            std::cout<<"Incorrect option. Type h/H to print help.\n";
    }
}
