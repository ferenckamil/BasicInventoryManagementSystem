#include <inventory.hpp>

#include <iostream>

/*
returns true if add operation was successful
return false if item with same id already exist in the inventory.
*/
bool Inventory::addItem(const Item& item) {
    
    /*
        A pair consisting of an iterator to the inserted element 
        (or to the element that prevented the insertion) 
        and a bool value set to true if and only if the insertion took place.
    */
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
        std::cout<<"Inventory is empty"<<std::endl;
    }

    for(auto & val : itemsCollection)
    {
        const Item & item = val.second;
        std::cout<<"Item ID: "<<item.getItemID()<<", Name: "<<item.getName()<<", Quantity: "<<item.getQuantity()<<", Price: "<<item.getPrice()<<std::endl;
    } 
    
    std::cout<<"---------------------------------------"<<std::endl;
}
