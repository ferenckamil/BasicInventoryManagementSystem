#pragma once

#include <string>
#include <ostream>

class Item {
    private:
        std::string itemID;
        std::string name;
        int quantity;
        double price;

    public:
    
        Item(const std::string&  itemID, const std::string& name, int quantity, double price);
        virtual ~Item() = default;

        void setItemID(std::string id);
        std::string getItemID() const;

        void setName(std::string name);
        std::string getName() const;

        void setQuantity(int quantity);
        int getQuantity() const;

        void setPrice(double price);
        double getPrice() const;

        virtual void displayItem() const;
        virtual void saveItemToFile(std::ostream& output) const;
};