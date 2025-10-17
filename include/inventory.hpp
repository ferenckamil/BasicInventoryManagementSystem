#pragma once

#include <unordered_map>
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

    public:
        bool addItem(const Item& item);
        bool removeItem(const std::string& itemID);
        bool updateItem(const std::string& itemID, int quantity);
        void displayInventory() const;

};