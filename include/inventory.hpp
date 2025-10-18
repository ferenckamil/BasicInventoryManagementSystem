#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <functional>

#include <item.hpp>

class Inventory{
    private:

        /*
        There's no requirement to maintain item order,
        unordered_map provides the best average time complexity (O(1)) for key operations:
        insertion, deletion, and searching by key.

        Using unique_ptr to store derived objects by pointer, which prevents object slicing.
        */
        std::unordered_map<std::string, std::unique_ptr<Item>> itemsCollection;

        //helper function used to read data from file
        void split(const std::string& line, char delimiter, std::vector<std::string>& elements);
        
        //Defing factory
        using ItemFactoryFunc = std::function<std::unique_ptr<Item>(const std::vector<std::string>&)>;
        std::unordered_map<std::string, ItemFactoryFunc> itemFactoryRegistry;

    public:
        Inventory();

        bool addItem(std::unique_ptr<Item> item);
        bool removeItem(const std::string& itemID);
        bool updateItem(const std::string& itemID, int quantity);
        void displayInventory() const;

        void readFromFile(const std::string& path);
        void saveToFile(const std::string& path) const;
};