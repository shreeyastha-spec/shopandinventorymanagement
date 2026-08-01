#ifndef CLOTHES_H
#define CLOTHES_H

#include "Product.h"


class Clothes : public Product
{

private:

    string size;
    string material;


public:


    // Constructor
    Clothes()
    {
        size = "";
        material = "";
    }


    Clothes(int id, string name, double price, int quantity,
            string size, string material)
            : Product(id, name, price, quantity)
    {
        this->size = size;
        this->material = material;
    }



    // Destructor
    ~Clothes()
    {
        cout<<"Clothes object destroyed"<<endl;
    }



    void display() override
    {
        cout<<"\n--- Clothes Product ---";
        cout<<"\nID: "<<id;
        cout<<"\nName: "<<name;
        cout<<"\nPrice: "<<price;
        cout<<"\nQuantity: "<<quantity;
        cout<<"\nSize: "<<size;
        cout<<"\nMaterial: "<<material<<endl;
    }



    void saveToFile(ofstream &file) override
    {
        file<<"Clothes "
            <<id<<" "
            <<name<<" "
            <<price<<" "
            <<quantity<<" "
            <<size<<" "
            <<material<<endl;
    }

};


#endif