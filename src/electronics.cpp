#include "Electronics.hpp"

#include <iostream>
#include <stdexcept>

Electronics::Electronics(const std::string&  itemID, const std::string& name, int quantity, double price, std::chrono::year_month_day warrantyPeriod) :
    Item(itemID, name, quantity, price), warrantyPeriod(warrantyPeriod) {
        if(!warrantyPeriod.ok())
        {
            throw std::invalid_argument("Invalid date");
        }

        if(auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()); warrantyPeriod < today)
        {
            throw std::invalid_argument("Given date is in the past");
        }
}

void Electronics::setWarrantyPeriod(std::chrono::year_month_day warrantyPeriod) {
    if(!warrantyPeriod.ok())
    {
        throw std::invalid_argument("Invalid date");
    }

    if(auto today = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()); warrantyPeriod < today)
    {
        throw std::invalid_argument("Given date is in the past");
    }

    this->warrantyPeriod = warrantyPeriod;

}

std::chrono::year_month_day Electronics::getWarrantyPeriod() const {
    return warrantyPeriod;
}

void Electronics::displayItem() const {
    Item::displayItem();
    std::cout<<", Warranty Period: "<<this->getWarrantyPeriod();

}

void Electronics::saveItemToFile(std::ostream& output) const {
    output << "ELECTRONICS,"
           << this->getItemID() << ","
           << this->getName() << ","
           << this->getQuantity() << ","
           << this->getPrice() << ","
           << this->getWarrantyPeriod();
}