#include <iostream>

#include <inventory.hpp>

int main() {
    
    std::cout<<"TEST APP"<<std::endl;
    Item item1("1", "Watch", 25, 199.99);
    Item item2("4", "Ipad", 7, 1599.99);
    Item item3("3", "Mango", 50, 7.99);

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

    std::cout<<"Test Inventory read from file..."<<std::endl;

    std::string path = "../text-files/input.txt";
    std::string path2 = "../text-files/input2.txt";
    std::string outputPath = "../text-files/output.txt";
    std::string outputPath2 = "../text-files/output2.txt";
    Inventory storeFromFile;

    try{
        storeFromFile.readFromFile(path);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr<<e.what()<<std::endl;
    }

    storeFromFile.displayInventory();

    storeFromFile.addItem(item2);

    storeFromFile.displayInventory();

    storeFromFile.updateItem("1", 200);

    storeFromFile.displayInventory();

    std::cout<<"Saving to file..."<<std::endl;

    try{
        storeFromFile.saveToFile(outputPath);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr<<e.what()<<std::endl;
    }

    std::cout<<"Test Inventory read from file - cannot add..."<<std::endl;

    Inventory storeFromFile2;

    
    storeFromFile2.addItem(item1);

    storeFromFile2.displayInventory();

    try{
        storeFromFile2.readFromFile(path);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr<<e.what()<<std::endl;
    }

    storeFromFile2.displayInventory();


    std::cout<<"Test Inventory read from file - invalid path..."<<std::endl;

    Inventory storeFromFile3;

    try{
        storeFromFile3.readFromFile(path2);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr<<e.what()<<std::endl;
    }

    storeFromFile3.displayInventory();

    std::cout<<"Test Inventory read from file - empty inventory..."<<std::endl;

    Inventory storeFromFile4;

    storeFromFile4.displayInventory();

    try{
        storeFromFile4.saveToFile(outputPath2);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr<<e.what()<<std::endl;
    }



    return 0;
}