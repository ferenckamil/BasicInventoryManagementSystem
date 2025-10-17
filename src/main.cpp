#include <iostream>

#include <item.hpp>
#include <inventory.hpp>

int main() {
    
    std::cout<<"TEST APP"<<std::endl;
    Item item1("1", "Phone", 10, 699.99);
    Item item2("2", "Laptop", 5, 1099.99);
    Item item3("3", "Apple", 100, 0.99);

    Inventory store;

    store.displayInventory();
    
    std::cout<<"Adding items..."<<std::endl;

    store.addItem(item1);
    store.addItem(item2);
    store.addItem(item3);

    store.displayInventory();

    std::cout<<"Removing one item..."<<std::endl;
    store.removeItem("2");

    store.displayInventory();

    std::cout<<"Updating one item..."<<std::endl;
    store.updateItem("1", 200);

    store.displayInventory();


    return 0;
}