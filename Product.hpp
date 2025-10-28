#pragma once

#include "InventoryManagement.hpp"

class Product
{
    public:
        string unique_id;
        string product_name;
        string brand_name;
        string asin;
        string product_name;
        vector<string> categories;

        Product() {};

        Product(const string& id, const string& name, const vector<string>& cat) : 
                unique_id(id), product_name(name), categories(cat) {} 

        void parseFILE(const string& FILE);
        vector<string> parseLINE(const string& line);

        void print();

    private:

};

void Product::print()
{
    cout<<"Unique ID: " << unique_id << endl;
    cout<<"Product Name: " << product_name << endl;
    cout<<"Categories: ";

    for(const auto& category : categories)
    {
        cout << category << " ";
    }

    cout << endl;

}

vector<string> Product::parseLINE(const string& line)
{

}


void Product::parseFILE(const string& FILE)
{
    ifstream infile(FILE);
    string line;

    //skip header
    cin.ignore();
    getline(infile, line);

    while(getline(infile, line))
    {
        stringstream ss(line);
        vector<string> lineData;
        string info;

        cin.ignore();

        //get all data from line and push to line data.
        //Unique ID, Product Name, Brand Name, Asin
        while(getline(ss, info, ','))
        {
            lineData.push_back(info);
        }

        //assign data to a new Product.
        //only get Unique ID, Product Name, Brand Name, Asin
        Product product;
        product.unique_id = lineData[0];
        product.product_name = lineData[1];
        product.brand_name = lineData[2];
        product.asin = lineData[3];

        //sort out it's category if emmty, then if its not
        string category_line = lineData[4];
        if (category_line.empty() == 0)
        {
            product.categories.push_back("NA");
        }
        else
        {
            stringstream field(category_line);
            string temp;

        }
        

    }
    
}