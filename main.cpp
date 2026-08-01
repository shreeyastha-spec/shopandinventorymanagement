#include <iostream>
#include <vector>
#include <fstream>
#include <limits>

#include "Product.h"
#include "Clothes.h"
#include "Shoes.h"

using namespace std;


vector<Product*> products;
void loadDefaultProducts()
{
    products.push_back(new Clothes(1,"Shirt",1200,10,"M","Cotton"));
    products.push_back(new Clothes(2,"Pant",1500,8,"L","Jeans"));
    products.push_back(new Clothes(3,"Jacket",2500,5,"XL","Leather"));
    products.push_back(new Clothes(4,"Tshirt",800,15,"M","Cotton"));
    products.push_back(new Clothes(5,"Hoodie",2000,7,"L","Wool"));

    products.push_back(new Shoes(6,"Nike Air",5000,4,42,"Nike"));
    products.push_back(new Shoes(7,"Running Shoe",3500,6,41,"Adidas"));
    products.push_back(new Shoes(8,"Formal Shoe",3000,5,40,"Bata"));
}
void addProduct()
{
    int choice;

    cout<<"\n1. Clothes";
    cout<<"\n2. Shoes";
    cout<<"\nChoose Product Type: ";
    cin>>choice;


    int id, quantity;
    string name;
    double price;


    try
    {
        cout<<"Enter ID: ";
        cin>>id;

        cout<<"Enter Name: ";
        cin>>name;

        cout<<"Enter Price: ";
        cin>>price;

        if(price < 0)
            throw "Price cannot be negative";


        cout<<"Enter Quantity: ";
        cin>>quantity;


        if(quantity < 0)
            throw "Quantity cannot be negative";



        if(choice == 1)
        {
            string size, material;

            cout<<"Enter Size: ";
            cin>>size;

            cout<<"Enter Material: ";
            cin>>material;


            products.push_back(
                new Clothes(id,name,price,quantity,size,material)
            );
        }


        else if(choice == 2)
        {
            int shoeSize;
            string brand;


            cout<<"Enter Shoe Size: ";
            cin>>shoeSize;


            cout<<"Enter Brand: ";
            cin>>brand;


            products.push_back(
                new Shoes(id,name,price,quantity,shoeSize,brand)
            );
        }

        else
        {
            cout<<"Invalid choice";
        }


        cout<<"\nProduct Added Successfully\n";

    }

    catch(const char* msg)
    {
        cout<<"Error: "<<msg<<endl;
    }

}




void displayProducts()
{

    if(products.empty())
    {
        cout<<"\nNo Products Available\n";
        return;
    }


    for(Product* p : products)
    {
        p->display();
        cout<<"-----------------\n";
    }

}




void updateProduct()
{
    int id;

    cout<<"Enter Product ID to Update: ";
    cin>>id;


    for(Product* p : products)
    {
        if(p->getId()==id)
        {
            string name;
            double price;
            int quantity;


            cout<<"New Name: ";
            cin>>name;

            cout<<"New Price: ";
            cin>>price;

            cout<<"New Quantity: ";
            cin>>quantity;


            p->update(name,price,quantity);


            cout<<"Updated Successfully\n";
            return;
        }
    }


    cout<<"Product not found\n";

}




void deleteProduct()
{

    int id;

    cout<<"Enter Product ID to Delete: ";
    cin>>id;


    for(int i=0;i<products.size();i++)
    {

        if(products[i]->getId()==id)
        {
            delete products[i];

            products.erase(products.begin()+i);


            cout<<"Deleted Successfully\n";
            return;
        }

    }


    cout<<"Product not found\n";

}




void saveData()
{

    ofstream file("inventory.txt");


    for(Product* p : products)
    {
        p->saveToFile(file);
    }


    file.close();


    cout<<"Data Saved Successfully\n";

}




int main()
{
  loadDefaultProducts();
    int choice;


    while(true)
    {

        cout<<"\n====== SHOP INVENTORY MANAGEMENT ======\n";

        cout<<"1. Add Product\n";
        cout<<"2. Display Products\n";
        cout<<"3. Update Product\n";
        cout<<"4. Delete Product\n";
        cout<<"5. Save Data\n";
        cout<<"0. Exit\n";


        cout<<"Enter Choice: ";


        try
        {
            cin>>choice;


            if(cin.fail())
            {
                throw "Invalid input";
            }



            switch(choice)
            {

            case 1:
                addProduct();
                break;


            case 2:
                displayProducts();
                break;


            case 3:
                updateProduct();
                break;


            case 4:
                deleteProduct();
                break;


            case 5:
                saveData();
                break;


            case 0:

                for(Product* p : products)
                {
                    delete p;
                }

                cout<<"Thank You\n";
                return 0;



            default:
                cout<<"Invalid Choice\n";

            }

        }


        catch(const char* msg)
        {
            cout<<"Error: "<<msg<<endl;

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

    }


}