#ifndef SHOES_H
#define SHOES_H

#include "Product.h"


class Shoes : public Product
{

private:

    int shoeSize;
    string brand;


public:


    // Default Constructor
    Shoes()
    {
        shoeSize = 0;
        brand = "";
    }



    // Parameterized Constructor
    Shoes(int id, string name, double price, int quantity,
          int shoeSize, string brand)
          : Product(id, name, price, quantity)
    {
        this->shoeSize = shoeSize;
        this->brand = brand;
    }



    // Destructor
    ~Shoes()
    {
        cout<<"Shoes object destroyed"<<endl;
    }



    void display() override
    {
        cout<<"\n--- Shoes Product ---";
        cout<<"\nID: "<<id;
        cout<<"\nName: "<<name;
        cout<<"\nPrice: "<<price;
        cout<<"\nQuantity: "<<quantity;
        cout<<"\nShoe Size: "<<shoeSize;
        cout<<"\nBrand: "<<brand<<endl;
    }



    void saveToFile(ofstream &file) override
    {
        file<<"Shoes "
            <<id<<" "
            <<name<<" "
            <<price<<" "
            <<quantity<<" "
            <<shoeSize<<" "
            <<brand<<endl;
    }

};


#endif