#include "Groceries.hpp"

#include <iostream>
#include <stdexcept>

Groceries::Groceries(const std::string&  itemID, const std::string& name, int quantity, double price, std::chrono::year_month_day expirationDate) :
    Item(itemID, name, quantity, price), expirationDate(expirationDate) {
        if(!expirationDate.ok())
        {
            throw std::invalid_argument("Given date in wrong format");
        }

        if(expirationDate < std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()))
        {
            throw std::invalid_argument("Given date is in the past");
        }
}

void Groceries::setExpirationDate(std::chrono::year_month_day expirationDate) {
    if(!expirationDate.ok())
    {
        throw std::invalid_argument("Given date in wrong format");
    }

    if(expirationDate < std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()))
    {
        throw std::invalid_argument("Given date is in the past");
    }

    this->expirationDate = expirationDate;

}

std::chrono::year_month_day Groceries::getExpirationDate() const {
    return expirationDate;
}

void Groceries::displayItem() const {
    Item::displayItem();
    std::cout<<", Expiration Date: "<<this->getExpirationDate();

}

void Groceries::saveItemToFile(std::ostream& output) const {
    output << "GROCERIES,"
           << this->getItemID() << ","
           << this->getName() << ","
           << this->getQuantity() << ","
           << this->getPrice() << ","
           << this->getExpirationDate();
}