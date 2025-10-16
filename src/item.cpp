#include "item.hpp"
#include <stdexcept>

Item::Item(const std::string&  itemID, const std::string& name, int quantity, double price) :
    itemID(itemID), name(name), quantity(quantity), price(price) {}

void Item::setItemID(std::string itemID) {
    if(itemID.empty())
    {
        throw std::invalid_argument("Item ID can not be empty");
    }

    /*
    in case of requirment that id can not have space sign there

    if(itemID.find(' ') != std::string::npos)
    {
        throw std::invalid_argument("Item ID can not contain spaces");
    }
    */

    this->itemID = itemID;
}

std::string Item::getItemID() const{
    return itemID;
}

void Item::setName(std::string name) {
    if(name.empty())
    {
        throw std::invalid_argument("Name can not be empty");
    }

    this->name = name;
}

std::string Item::getName() const {
    return name;
}

void Item::setQuantity(int quantity) {
    if(quantity<0)
    {
        throw std::invalid_argument("Quantity can not be less than zero");
    }

    this->quantity = quantity;
}

int Item::getQuantity() const {
    return quantity;
}

void Item::setPrice(double price) {
    if(price<0)
    {
        throw std::invalid_argument("Price can not be less than zero");
    }

    this->price = price;
}

double Item::getPrice() const {
    return price;
}