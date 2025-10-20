#pragma once

#include "Item.hpp"

#include <chrono>

class Electronics : public Item {
    private:
        //year_month_day is supported from C++20, in older version the good approach would be a creation of Date class
        std::chrono::year_month_day warrantyPeriod;

    public:
        Electronics(const std::string&  itemID, const std::string& name, int quantity, double price, std::chrono::year_month_day warrantyPeriod);

        void setWarrantyPeriod(std::chrono::year_month_day expDate);
        std::chrono::year_month_day getWarrantyPeriod() const;

        virtual void displayItem() const override;
        virtual void saveItemToFile(std::ostream& output) const override;

};