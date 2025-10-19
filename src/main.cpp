#include <iostream>

#include <inventory.hpp>

//to remove later
#include <electronics.hpp>
#include <groceries.hpp>
#include <chrono>

using namespace std::chrono_literals;
using std::chrono::month;

int main() {
    
    std::cout<<"TEST APP"<<"\n";
    auto item1 = std::make_unique<Item>("1", "Watch", 25, 199.99);
    auto item2 = std::make_unique<Electronics>("4", "Ipad", 7, 1599.99, 2025y / 12 / 1d);
    auto item3 = std::make_unique<Groceries>("3", "Mango", 50, 2000.99, 2025y / 11 / 20d);

    // item1->displayItem();
    // std::cout<<"\n";
    // item2->displayItem();
    // std::cout<<"\n";
    // item3->displayItem();
    // std::cout<<"\n";

    // std::cout<<"Incorrect item"<<'\n';
    // try
    // {
        
    //     auto item3Wrong = std::make_unique<Groceries>("3", "Mango", 50, -1, 2025y / 11 / 20d);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
    

    Inventory store;

    store.displayInventory();
    
    std::cout<<"Adding items..."<<"\n";

    store.addItem(std::move(item1));
    store.addItem(std::move(item2));
    store.addItem(std::move(item3));

    store.displayInventory();

    std::cout<<"Highest price"<<std::endl;
    store.findHighestPrice()->displayItem();
    std::cout<<std::endl;
    std::vector<const Item*> resultVec;
    store.findItemsBelowQuantityThreshold(100, resultVec);

    std::cout<<"Under threshold"<<std::endl;
    for(auto val: resultVec)
    {
        val->displayItem();
        std::cout<<std::endl;
    }
    // std::cout<<"Removing one item..."<<"\n";
    // store.removeItem("1");

    // store.displayInventory();

    // std::cout<<"Updating one item..."<<"\n";
    // store.updateItem("3", 200);

    // store.displayInventory();

    // std::cout<<"Test Inventory read from file..."<<"\n";

    // std::string path = "../text-files/input.txt";
    // std::string path2 = "../text-files/input2.txt";
    // std::string outputPath = "../text-files/output.txt";
    // std::string outputPath2 = "../text-files/output2.txt";
    // Inventory storeFromFile;

    // try{
    //     storeFromFile.readFromFile(path);
    // }
    // catch (const std::runtime_error& e)
    // {
    //     std::cerr<<e.what()<<"\n";
    // }

    // storeFromFile.displayInventory();

    // storeFromFile.addItem(std::move(item2));

    // storeFromFile.displayInventory();

    // storeFromFile.updateItem("1", 200);

    // storeFromFile.displayInventory();

    // std::cout<<"Saving to file..."<<"\n";

    // try{
    //     storeFromFile.saveToFile(outputPath);
    // }
    // catch (const std::runtime_error& e)
    // {
    //     std::cerr<<e.what()<<"\n";
    // }

    // std::cout<<"Test Inventory read from file - cannot add..."<<"\n";

    // Inventory storeFromFile2;

    // storeFromFile2.addItem(std::move(item1));

    // storeFromFile2.displayInventory();

    // try{
    //     storeFromFile2.readFromFile(path);
    // }
    // catch (const std::runtime_error& e)
    // {
    //     std::cerr<<e.what()<<"\n";
    // }

    // storeFromFile2.displayInventory();


    // std::cout<<"Test Inventory read from file - invalid path..."<<"\n";

    // Inventory storeFromFile3;

    // try{
    //     storeFromFile3.readFromFile(path2);
    // }
    // catch (const std::runtime_error& e)
    // {
    //     std::cerr<<e.what()<<"\n";
    // }

    // storeFromFile3.displayInventory();

    // std::cout<<"Test Inventory read from file - empty inventory..."<<"\n";

    // Inventory storeFromFile4;

    // storeFromFile4.displayInventory();

    // try{
    //     storeFromFile4.saveToFile(outputPath2);
    // }
    // catch (const std::runtime_error& e)
    // {
    //     std::cerr<<e.what()<<"\n";
    // }



    return 0;
}