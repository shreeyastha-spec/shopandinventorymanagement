

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class Product {
private:
    string productId;
    string productName;
    string quantity;
    string price;

    static string fileName() {
        return "products.txt";
    }

    static string header() {
        return "productId,productName,quantity,price";
    }

    static void ensureFile() {
        ifstream in(fileName(), ios::ate | ios::binary);
        bool missingOrEmpty = !in.is_open() || in.tellg() == 0;

        if (missingOrEmpty) {
            ofstream out(fileName(), ios::trunc);
            out << header() << endl;
        }
    }

    static vector<string> loadRecords() {
        vector<string> records;
        ifstream in(fileName());

        string line;
        getline(in, line);

        while (getline(in, line)) {
            if (!line.empty())
                records.push_back(line);
        }

        return records;
    }

    static void saveRecords(const vector<string>& records) {
        ofstream out(fileName(), ios::trunc);
        out << header() << endl;

        for (const string& line : records)
            out << line << endl;
    }

    static Product fromLine(string line) {
        auto p1 = line.find(',');
        auto p2 = line.find(',', p1 + 1);
        auto p3 = line.find(',', p2 + 1);

        string id = line.substr(0, p1);
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string qty = line.substr(p2 + 1, p3 - p2 - 1);
        string pr = line.substr(p3 + 1);

        return Product(id, name, qty, pr);
    }

public:
    Product() {}

    Product(string id, string name, string qty, string pr) {
        productId = id;
        productName = name;
        quantity = qty;
        price = pr;
    }

    string toRecord() const {
        return productId + "," + productName + "," + quantity + "," + price;
    }

    void displayProduct() const {
        cout << "Product ID : " << productId << endl;
        cout << "Name       : " << productName << endl;
        cout << "Quantity   : " << quantity << endl;
        cout << "Price      : " << price << endl;
    }

    static void createProduct(string id, string name, string qty, string price) {

        ensureFile();

        Product p(id, name, qty, price);

        ofstream out(fileName(), ios::app);
        out << p.toRecord() << endl;

        cout << "Product added successfully.\n";
    }

    static void displayAllProducts() {

        ensureFile();

        vector<string> records = loadRecords();

        if (records.empty()) {
            cout << "No products found.\n";
            return;
        }

        for (const string& line : records) {
            Product p = fromLine(line);
            p.displayProduct();
            cout << "----------------------\n";
        }
    }

    static void searchProduct(string id) {

        ensureFile();

        vector<string> records = loadRecords();

        for (const string& line : records) {

            auto pos = line.find(',');

            if (line.substr(0, pos) == id) {
                Product p = fromLine(line);
                p.displayProduct();
                return;
            }
        }

        cout << "Product not found.\n";
    }

    static void updateProduct(string id, string name, string qty, string price) {

        ensureFile();

        vector<string> records = loadRecords();

        bool found = false;

        for (string& line : records) {

            auto pos = line.find(',');

            if (line.substr(0, pos) == id) {

                Product p(id, name, qty, price);
                line = p.toRecord();
                found = true;
                break;
            }
        }

        if (found) {
            saveRecords(records);
            cout << "Product updated successfully.\n";
        } else {
            cout << "Product not found.\n";
        }
    }

    static void deleteProduct(string id) {

        ensureFile();

        vector<string> records = loadRecords();
        vector<string> newRecords;

        bool found = false;

        for (const string& line : records) {

            auto pos = line.find(',');

            if (line.substr(0, pos) == id)
                found = true;
            else
                newRecords.push_back(line);
        }

        if (found) {
            saveRecords(newRecords);
            cout << "Product deleted successfully.\n";
        } else {
            cout << "Product not found.\n";
        }
    }
};

static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    while (true) {
        cout << "\nProduct Management\n";
        cout << "1. Add product\n";
        cout << "2. Display all products\n";
        cout << "3. Search product\n";
        cout << "4. Update product\n";
        cout << "5. Delete product\n";
        cout << "6. Exit\n";
        cout << "Select an option: ";

        int option;
        if (!(cin >> option)) {
            cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        clearInput();

        if (option == 6)
            break;

        string id, name, qty, price;

        switch (option) {
            case 1:
                cout << "Enter product ID: ";
                getline(cin, id);
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter quantity: ";
                getline(cin, qty);
                cout << "Enter price: ";
                getline(cin, price);
                Product::createProduct(id, name, qty, price);
                break;
            case 2:
                Product::displayAllProducts();
                break;
            case 3:
                cout << "Enter product ID to search: ";
                getline(cin, id);
                Product::searchProduct(id);
                break;
            case 4:
                cout << "Enter product ID to update: ";
                getline(cin, id);
                cout << "Enter new product name: ";
                getline(cin, name);
                cout << "Enter new quantity: ";
                getline(cin, qty);
                cout << "Enter new price: ";
                getline(cin, price);
                Product::updateProduct(id, name, qty, price);
                break;
            case 5:
                cout << "Enter product ID to delete: ";
                getline(cin, id);
                Product::deleteProduct(id);
                break;
            default:
                cout << "Invalid option. Please choose 1-6.\n";
                break;
        }
    }

    cout << "Exiting program.\n";
    return 0;
}
