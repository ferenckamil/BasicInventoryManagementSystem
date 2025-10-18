#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include <item.hpp>

class Inventory{
    private:

        /*
        There's no requirement to maintain item order,
        unordered_map provides the best average time complexity (O(1)) for key operations:
        insertion, deletion, and searching by key.
        */
        std::unordered_map<std::string, Item> itemsCollection;

        //helper function used to read data from file
        void split(const std::string& line, char delimiter, std::vector<std::string>& elements);

    public:
        bool addItem(const Item& item);
        bool removeItem(const std::string& itemID);
        bool updateItem(const std::string& itemID, int quantity);
        void displayInventory() const;

        void readFromFile(const std::string& path);
        void saveToFile(const std::string& path) const;
};