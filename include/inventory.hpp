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

        update1: Using shared_ptr to store derived objects by pointer, which prevents object slicing.
            If an error occurs during object construction (e.g., std::stoi fails inside the constructor),
            std::make_shared ensures that any allocated memory is automatically
            deallocated, preventing a memory leak.
        update2: moving from shared_ptr to shared_ptr

            Switched from std::shared_ptr (exclusive ownership) to std::shared_ptr
            (shared ownership). This allows a single Item object to be "owned" by
            multiple systems simultaneously (e.g., by the 'mainWarehouse' and
            the 'shopFloor' inventory at the same time). The object is automatically
            destroyed only when the last owner (the last shared_ptr) is gone.

            std::shared_ptr provides the same protection against memory leaks during construction (exception safety).
        */
        std::unordered_map<std::string, std::shared_ptr<Item>> itemsCollection;

        //Helper function used to read data from file
        void split(const std::string& line, char delimiter, std::vector<std::string>& elements);
        
        //Defing factory
        using ItemFactoryFunc = std::function<std::shared_ptr<Item>(const std::vector<std::string>&)>;
        std::unordered_map<std::string, ItemFactoryFunc> itemFactoryRegistry;

    public:
        Inventory();

        //Inventory management
        bool addItem(const std::shared_ptr<Item>& item);
        bool removeItem(const std::string& itemID);
        bool updateItem(const std::string& itemID, int quantity);
        void displayInventory() const;

        //File operations
        void readFromFile(const std::string& path);
        void saveToFile(const std::string& path) const;

        //Searching functions
        const Item* findHighestPrice() const;
        void findItemsBelowQuantityThreshold(int threshold, std::vector<const Item*>& resultVec) const;
        //const std::vector<Item*> findItemsBelowQuantityThreshold(int threshold) const;
};