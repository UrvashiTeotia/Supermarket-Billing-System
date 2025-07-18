#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    static double totalProfit;

    Product() {}
    Product(int id, string name, double price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int q) { quantity = q; }

    static void viewAll() {
        ifstream in("products.txt");
        Product p;
        cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(10)
             << "Price" << setw(10) << "Quantity\n";
        while (in >> p.id >> p.name >> p.price >> p.quantity) {
            cout << left << setw(5) << p.id << setw(15) << p.name << setw(10)
                 << p.price << setw(10) << p.quantity << endl;
        }
        in.close();
    }

    static void searchByName(const string &query) {
        ifstream in("products.txt");
        Product p;
        bool found = false;
        while (in >> p.id >> p.name >> p.price >> p.quantity) {
            if (p.name.find(query) != string::npos) {
                cout << p.id << " " << p.name << " " << p.price << " " << p.quantity << endl;
                found = true;
            }
        }
        if (!found) cout << "No product found.\n";
        in.close();
    }

    bool loadProductById(int searchId) {
        ifstream in("products.txt");
        while (in >> id >> name >> price >> quantity) {
            if (id == searchId) {
                in.close();
                return true;
            }
        }
        in.close();
        return false;
    }

    void display() const {
        cout << left << setw(5) << id << setw(15) << name << setw(10)
             << price << setw(10) << quantity << endl;
    }

    static void updateQuantity(int pid, int boughtQty) {
        vector<Product> all;
        ifstream in("products.txt");
        Product p;
        while (in >> p.id >> p.name >> p.price >> p.quantity) {
            if (p.id == pid) {
                p.quantity -= boughtQty;
            }
            all.push_back(p);
        }
        in.close();

        ofstream out("products.txt");
        for (auto &x : all) {
            out << x.id << " " << x.name << " " << x.price << " " << x.quantity << endl;
        }
        out.close();
    }
};

double Product::totalProfit = 0;

#endif
