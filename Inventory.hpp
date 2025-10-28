#pragma once 

#include "InventoryManagement.hpp"
#include "Product.hpp"

class Inventory
{
    public:
        void insertProduct(const Product& product);
        Product* searchProductID(const string& inventoryID);
        vector<Product> products_by_cat(const string& category);


    private:
        //story the inventory by... 
        unordered_map<string, Product> inventory_by_ID;
        unordered_map<string, vector<Product>> inventory_by_category; 

};


Product* Inventory::searchProductID(const string& inventoryID)
{
    //return null is no, if yes return product directly
    if(inventory_by_ID.count(inventoryID) == 0)
    {
        return nullptr;
    }
    else
    {
        return &inventory_by_ID[inventoryID];
    }

}

void Inventory::insertProduct(const Product& product)
{
    //store by the ID then Category

    inventory_by_ID[product.unique_id] = product;

    for (const auto& category : product.categories)
    {
        inventory_by_category[category].push_back(product);
    }

}

vector<Product> Inventory::products_by_cat(const string& category)
{
    //return empty vector if no, otherwise return the list of products in category. 
    if (inventory_by_category.count(category) == 0)
    {
        return vector<Product>();
    }
    else
    {
    return inventory_by_category[category];
    }

}