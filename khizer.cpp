#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Product {
    string brand, flavor;
    int stock;
    double price;
};

struct Customer {
    string name, contact;
    vector<string> purchaseHistory;
};

vector<Product> inventory;
vector<Customer> customers;

void loadInventory() {
    ifstream file("inventory.txt");
    if (!file) return;
    Product p;
    while (file >> p.brand >> p.flavor >> p.stock >> p.price)
        inventory.push_back(p);
    file.close();
}

void saveInventory() {
    ofstream file("inventory.txt");
    for (const auto &p : inventory)
        file << p.brand << " " << p.flavor << " " << p.stock << " " << p.price << endl;
    file.close();
}

void addProduct() {
    Product p;
    cout << "Enter Brand: "; cin >> p.brand;
    cout << "Enter Flavor: "; cin >> p.flavor;
    cout << "Enter Stock: "; cin >> p.stock;
    cout << "Enter Price: "; cin >> p.price;
    inventory.push_back(p);
    saveInventory();
}

void displayInventory() {
    cout << "\nInventory:\n";
    for (const auto &p : inventory)
        cout << "Brand: " << p.brand << ", Flavor: " << p.flavor << ", Stock: " << p.stock << ", Price: $" << p.price << endl;
}

void recordSale() {
    string brand, flavor, customerName;
    int quantity;
    cout << "Enter Customer Name: "; cin >> customerName;
    cout << "Enter Brand: "; cin >> brand;
    cout << "Enter Flavor: "; cin >> flavor;
    cout << "Enter Quantity: "; cin >> quantity;
    
    for (auto &p : inventory) {
        if (p.brand == brand && p.flavor == flavor && p.stock >= quantity) {
            p.stock -= quantity;
            saveInventory();
            cout << "Sale recorded successfully!\n";
            return;
        }
    }
    cout << "Product not available or insufficient stock!\n";
}

void generateReport() {
    cout << "\nSales Report:\n";
    for (const auto &p : inventory)
        cout << "Brand: " << p.brand << ", Flavor: " << p.flavor << ", Remaining Stock: " << p.stock << endl;
}

int main() {
    loadInventory();
    int choice;
    do {
        cout << "\nVape Store Management System\n";
        cout << "1. Add Product\n2. View Inventory\n3. Record Sale\n4. Generate Report\n5. Exit\nChoose: ";
        cin >> choice;
        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayInventory(); break;
            case 3: recordSale(); break;
            case 4: generateReport(); break;
            case 5: saveInventory(); break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}