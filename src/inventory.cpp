#include <inventory.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <filesystem>

/*
returns true if add operation was successful
return false if item with same id already exist in the inventory.
*/
bool Inventory::addItem(const Item& item) {

    auto result = itemsCollection.emplace(std::make_pair(item.getItemID(), item));

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
        found->second.setQuantity(quantity);
        return true;
    }

    return false;
}

void Inventory::displayInventory() const {

    std::cout<<"----------- Inventory state -----------"<<std::endl;

    if(itemsCollection.empty())
    {
        std::cerr<<"Inventory is empty"<<std::endl;
    }

    for(auto & val : itemsCollection)
    {
        const Item & item = val.second;
        std::cout<<"Item ID: "<<item.getItemID()<<", Name: "<<item.getName()<<", Quantity: "<<item.getQuantity()<<", Price: "<<item.getPrice()<<std::endl;
    } 
    
    std::cout<<"---------------------------------------"<<std::endl;
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

        if(elements.size() != 4)
        {
            std::cerr << "Warning: Incorrect line format. Skipping line number: " << lineNumber << std::endl;
            continue;
        }
        
        Item item(elements[0], elements[1], std::stoi(elements[2]), std::stod(elements[3]));

        if(!this->addItem(item)){
            std::cerr << "Can not add the element with ID: " + item.getItemID() + ". Item with this ID already present in inventory. Skipping..."<<std::endl;
            continue;
        }

    }

    inputFile.close();
}

void Inventory::saveToFile(const std::string& path) const {

    if(itemsCollection.empty())
    {
        throw std::runtime_error("Save operation aborted: Inventory is empty");
    }

    try{

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
            outputFile << item.second.getItemID() << ","
                    << item.second.getName() << ","
                    << item.second.getQuantity() << ","
                    << item.second.getPrice()<< "\n";
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

    while(std::getline(ss, element, delimiter)) {
        elements.push_back(element);
    }
}