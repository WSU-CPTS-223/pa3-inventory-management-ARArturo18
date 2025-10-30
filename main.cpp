#include "InventoryManagement.hpp"
#include "Product.hpp"
#include "Inventory.hpp"

using namespace std;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use :quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, Inventory& ourInventory)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        // Look up the appropriate datastructure to find if the inventory exist
        string inventID = line.substr(5);

        Product* product = ourInventory.searchProductID(inventID);

        if(product)
        {
            //print 
            product->print();
        }
        else
        {
            cout << "Inventory/Product not found" << endl;
        }

    }
    // if line starts with listInventory
    // Look up the appropriate datastructure to find all inventory belonging to a specific category
    else if (line.rfind("listInventory", 0) == 0)
    {
        string category = line.substr(14);
        vector<Product> product = ourInventory.products_by_cat(category);

        if(product.empty())
        {
            cout<< "Invalid Category" << endl;
        }
        else 
        {
            for (const auto& p : product)
            {
                cout << "Unique ID:  " << p.unique_id << endl;
                cout << "Product Name: " << p.product_name << endl;
                cout<<endl;
            }
        }
    }
}

void bootStrap(Inventory& ourInventory)
{
    Product parseCSV; 
    parseCSV.parseFILE("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv", ourInventory);
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";

    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices

}

int main(int argc, char const *argv[])
{
    Inventory ourInventory;
    string line;
    bootStrap(ourInventory);
    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, ourInventory);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
