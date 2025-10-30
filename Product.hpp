#pragma once

#include "InventoryManagement.hpp"

class Inventory;

class Product
{
    public:
        string unique_id;
        string product_name;
        string brand_name;
        string asin;
        vector<string> categories;

        Product() {};

        Product(const string& id, const string& name, const vector<string>& cat) : 
                unique_id(id), product_name(name), categories(cat) {} 

        void parseFILE(const string& FILE, Inventory& ourInventory);

        void print();

    private:

};

#include"Inventory.hpp"



void Product::print()
{
    cout<< "Unique ID: " << unique_id << endl;
    cout<< "Product Name: " << product_name << endl;
    cout << "Brand Name: " << brand_name << endl;
    cout << "Asin: " << asin << endl;
    cout<<"Categories: ";

    for(const auto& category : categories)
    {
        cout << category << " ";
    }

    cout << "\n" << endl;

}

//cleans line, then parses into a vector, and puts everything into a new product
void Product::parseFILE(const string& FILE, Inventory& ourInventory)
{
    ifstream infile(FILE);
    string line;

    //skip header
    cin.ignore();
    getline(infile, line);

    //goes through all the lines.
    while(getline(infile, line))
    {
        stringstream ss(line);

        vector<string> lineFields;
        string field;
        bool commaQuotes = false;
        //Commas in Quotes
        for(char c : line)
        {
            if(c == '"')
            {
                commaQuotes = true;
            }
            else if (c == ',' && commaQuotes == true)
            {
                lineFields.push_back(field);
            }
            else
            {
                field += c;
            }
        }

        lineFields.push_back(field);


        cin.ignore();

        
        //assign data and fix it's categories. 
        //only get Unique ID, Product Name, Brand Name, Asin, category
        string product_id = lineFields[0];
        string product_name = lineFields[1];
        string brand_name = lineFields[2];
        string asin = lineFields[3];
        string category = lineFields[4];


        //sort out it's category if emmty, then if its not
        set<string> lineCategories;
        if (category.empty() == 1)
        {
            lineCategories.insert("NA");
        }
        else
        {
            stringstream ss(category);
            string holder;

            while(getline(ss, holder, '|'))
            {
                if(holder.empty() == 0)
                {
                    lineCategories.insert(holder);
                }
            }

        }
        
        //make a new product the line and put them into both structures of id and categories. 
        Product newProduct(product_id, product_name, lineFields);

        ourInventory.insertProduct(newProduct);

    }

    cout<<"SUCCESSS PARSING" << endl;
    infile.close();
    
}