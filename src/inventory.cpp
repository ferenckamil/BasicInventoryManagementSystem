#include <inventory.hpp>

#include <electronics.hpp>
#include <groceries.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <filesystem>
#include <algorithm>

Inventory::Inventory() {
    itemFactoryRegistry["ELECTRONICS"] = [](const std::vector<std::string>& elements) -> std::unique_ptr<Item> {
        if (elements.size() != 6) 
        {
            throw std::invalid_argument("Incorrect input data for Electronics");
        }
        
        std::chrono::year_month_day warrantyPeriod;
        std::stringstream date(elements[5]);
        date >> std::chrono::parse("%F", warrantyPeriod);

        if (date.fail() || !warrantyPeriod.ok()) 
        {
            throw std::invalid_argument("Invalid warranty period period format");
        }
        
        return std::make_unique<Electronics>(elements[1], elements[2], std::stoi(elements[3]), std::stod(elements[4]), warrantyPeriod);
    };

    itemFactoryRegistry["GROCERIES"] = [](const std::vector<std::string>& elements) -> std::unique_ptr<Item> {
        if (elements.size() != 6) 
        {
            throw std::invalid_argument("Incorrect input data for Groceries");
        }
        
        std::chrono::year_month_day expirationDate;
        std::stringstream date(elements[5]);
        date >> std::chrono::parse("%F", expirationDate);

        if (date.fail() || !expirationDate.ok()) 
        {
            throw std::invalid_argument("Invalid expiration date period format");
        }
        
        return std::make_unique<Groceries>(elements[1], elements[2], std::stoi(elements[3]), std::stod(elements[4]), expirationDate);
    };

    itemFactoryRegistry["ITEM"] = [](const std::vector<std::string>& elements) -> std::unique_ptr<Item> {
        if (elements.size() != 5) 
        {
            throw std::invalid_argument("Incorrect input data for Groceries");
        }
        
        return std::make_unique<Item>(elements[1], elements[2], std::stoi(elements[3]), std::stod(elements[4]));
    };
}

/*
returns true if add operation was successful
return false if item with same id already exist in the inventory.
*/
bool Inventory::addItem(std::unique_ptr<Item> item) {

    if(!item)
    {
        return false;
    }

    //getting id before, to avoid the case that item has been moved first
    const std::string& itemId = item->getItemID();

    auto result = itemsCollection.emplace(std::make_pair(itemId, std::move(item)));

    return result.second;
}

/*
returns true if item has been removed succesfully, false otherwise.
*/
bool Inventory::removeItem(const std::string& itemID) {
    
    if(itemsCollection.empty())
    {
        return false;
    }

    if(auto found = itemsCollection.find(itemID); found != itemsCollection.end())
    {
        itemsCollection.erase(found);
        return true;
    }

    return false;

}

/*
returns true if item has been updated succesfully, false otherwise.
*/
bool Inventory::updateItem(const std::string& itemID, int quantity) {
    
    if(itemsCollection.empty())
    {
        return false;
    }

    if(auto found = itemsCollection.find(itemID); found != itemsCollection.end())
    {
        try
        {
            found->second->setQuantity(quantity);
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        
        return true;
    }

    return false;
}

void Inventory::displayInventory() const {

    std::cout<<"----------- Inventory state -----------"<<"\n";

    if(itemsCollection.empty())
    {
        std::cerr<<"Inventory is empty"<<"\n";
    }

    for(auto & val : itemsCollection)
    {
        val.second->displayItem();
        std::cout<<"\n";
    } 
    
    std::cout<<"---------------------------------------"<<"\n";
}


void Inventory::readFromFile(const std::string& path) {
    
    std::ifstream inputFile(path);
    
    if(!inputFile.is_open())
    {
        throw std::runtime_error("File can not be opened: " + path);
    }
    
    std::string line;
    int lineNumber = 0;
    std::vector<std::string> elements;
    
    while(std::getline(inputFile, line))
    {
        lineNumber++;
        split(line, ',', elements);

        if(elements.empty())
        {
            std::cerr << "Warning: Empty line. Skipping line number: " << lineNumber << "\n";
            continue;
        }
        
        const std::string& itemType = elements[0];

        try
        {
            auto it = itemFactoryRegistry.find(itemType);
            if (it == itemFactoryRegistry.end()) 
            {
                throw std::invalid_argument("Unknown item type: " + itemType);
            }
            
            std::unique_ptr<Item> item = it->second(elements);

            //getting id before, to avoid the case that item has been moved first
            std::string currId = item->getItemID();
            
            if(!this->addItem(std::move(item))){
                std::cerr << "Can not add the element with ID: " << currId << ". Item with this ID already present in inventory. Skipping... \n";
            }
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << "Error reading line " <<lineNumber << ": " << e.what() << ". Skipping... \n";
        }
    }

    inputFile.close();
}

void Inventory::saveToFile(const std::string& path) const {

    if(itemsCollection.empty())
    {
        throw std::runtime_error("Save operation aborted: Inventory is empty");
    }

    try {

        std::filesystem::path filePath(path);
        std::filesystem::path directory = filePath.parent_path();

        if(!directory.empty())
        {
            std::filesystem::create_directories(directory);
        }

        std::ofstream outputFile(path);
        if(!outputFile.is_open())
        {
            throw std::runtime_error("File can not be opened: " + path);
        }

        for(const auto& item: itemsCollection){
            item.second->saveItemToFile(outputFile);
            outputFile << "\n";
        }

        outputFile.close();

    } catch (const std::filesystem::filesystem_error& e) {
        throw std::runtime_error("Filesystem error: " + std::string(e.what()));
    }   

}

//helper function
void Inventory::split(const std::string& line, char delimiter, std::vector<std::string>& elements) {
    elements.clear();
    std::string element;
    std::stringstream ss(line);

    while(std::getline(ss, element, delimiter)) 
    {
        elements.push_back(element);
    }
}

const Item* Inventory::findHighestPrice() const {
    
    //O(n) - iterating over whole unordered map
    auto maxPriceItem = std::max_element(itemsCollection.begin(), itemsCollection.end(),
                        [](const auto& item1, const auto& item2)
                        {
                            return item1.second->getPrice() < item2.second->getPrice();
                        }
    );

    return maxPriceItem->second.get();

    
}

void Inventory::findItemsBelowQuantityThreshold(int threshold, std::vector<const Item*>& resultVec) const {

    resultVec.clear();
    //O(n) - iterating over whole unordered map
    for(auto& val: itemsCollection)
    {
        if(val.second->getQuantity() < threshold)
        {
            resultVec.push_back(val.second.get());
        }
    }

}