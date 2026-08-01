#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Product
{
protected:

    int id;
    string name;
    double price;
    int quantity;


public:

    // Constructor
    Product()
    {
        id = 0;
        name = "";
        price = 0;
        quantity = 0;
    }


    Product(int id, string name, double price, int quantity)
    {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }


    // Destructor
    virtual ~Product()
    {
        cout<<"Product destroyed"<<endl;
    }



    virtual void display()
    {
        cout<<"\nProduct ID: "<<id;
        cout<<"\nName: "<<name;
        cout<<"\nPrice: "<<price;
        cout<<"\nQuantity: "<<quantity<<endl;
    }



    virtual void saveToFile(ofstream &file)
    {
        file<<id<<" "
            <<name<<" "
            <<price<<" "
            <<quantity<<endl;
    }



    int getId()
    {
        return id;
    }


    string getName()
    {
        return name;
    }


    double getPrice()
    {
        return price;
    }


    int getQuantity()
    {
        return quantity;
    }


    void update(string n,double p,int q)
    {
        name=n;
        price=p;
        quantity=q;
    }

};

#endif