#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

class Product {
public:
    int id;
    string name;
    float price;
    int quantity;
    static double income;

    void input() {
        cout << "\nEnter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> quantity;
    }

    void saveToFileSorted() {
        vector<tuple<int, string, float, int>> products;
        ifstream infile("products.txt");

        int pid, qty;
        float pr;
        string pname;

        while (infile >> pid >> pname >> pr >> qty) {
            products.push_back({pid, pname, pr, qty});
        }
        infile.close();

        auto it = lower_bound(products.begin(), products.end(), id,
            [](const tuple<int, string, float, int>& a, int val) {
                return get<0>(a) < val;
            });

        products.insert(it, {id, name, price, quantity});

        ofstream outfile("products.txt");
        for (auto& p : products) {
            outfile << get<0>(p) << " " << get<1>(p) << " "
                    << get<2>(p) << " " << get<3>(p) << "\n";
        }
        outfile.close();

        cout << "Product added in sorted order!\n";
    }

    static void viewAll() {
        ifstream file("products.txt");
        if (!file) {
            cout << "Error opening file!\n";
            return;
        }

        Product p;
        cout << "\n--- Product List ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name"
             << setw(10) << "Price" << setw(10) << "Qty" << "\n";
        cout << "-----------------------------------------------\n";

        while (file >> p.id >> p.name >> p.price >> p.quantity) {
            cout << left << setw(10) << p.id << setw(20) << p.name
                 << setw(10) << p.price << setw(10) << p.quantity << "\n";
        }
        file.close();
    }

    static void searchById(int searchId) {
        ifstream file("products.txt");
        if (!file) {
            cout << "File not found!\n";
            return;
        }

        bool found = false;
        int id, quantity;
        float price;
        string name;

        while (file >> id >> name >> price >> quantity) {
            if (id == searchId) {
                cout << "Product Found:\n";
                cout << "ID: " << id
                     << " | Name: " << name
                     << " | Price: " << price
                     << " | Quantity: " << quantity << "\n";
                found = true;
                break;
            }
        }

        file.close();
        if (!found) {
            cout << "Product with ID " << searchId << " not found.\n";
        }
    }

    static void updateById(int updateId) {
        ifstream file("products.txt");
        ofstream temp("temp.txt");
        if (!file || !temp) {
            cout << "File couldn't be opened!\n";
            return;
        }

        int id, quantity;
        float price;
        string name;
        bool found = false;

        while (file >> id >> name >> price >> quantity) {
            if (id == updateId) {
                cout << "Enter new name: ";
                cin >> name;
                cout << "Enter new price: ";
                cin >> price;
                cout << "Enter new quantity: ";
                cin >> quantity;
                found = true;
                cout << "Product updated successfully!\n";
            }
            temp << id << " " << name << " " << price << " " << quantity << "\n";
        }

        file.close();
        temp.close();

        remove("products.txt");
        rename("temp.txt", "products.txt");

        if (!found) {
            cout << "Product with ID " << updateId << " not found.\n";
        }
    }

    static void deleteById(int deleteId) {
        ifstream file("products.txt");
        ofstream temp("temp.txt");
        if (!file || !temp) {
            cout << "File couldn't be opened!\n";
            return;
        }

        int id, quantity;
        float price;
        string name;
        bool found = false;

        while (file >> id >> name >> price >> quantity) {
            if (id == deleteId) {
                found = true;
                cout << "Product with ID " << deleteId << " deleted successfully!\n";
                continue;
            }
            temp << id << " " << name << " " << price << " " << quantity << "\n";
        }

        file.close();
        temp.close();

        remove("products.txt");
        rename("temp.txt", "products.txt");

        if (!found) {
            cout << "Product with ID " << deleteId << " not found.\n";
        }
    }

    #include <algorithm> // for transform

static void searchByName(const string& keyword) {
    ifstream file("products.txt");
    if (!file) {
        cout << "File not found!\n";
        return;
    }

    Product p;
    bool found = false;


    string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    cout << "\n--- Matching Products ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name"
         << setw(10) << "Price" << setw(10) << "Qty" << "\n";
    cout << "-----------------------------------------------\n";

    while (file >> p.id >> p.name >> p.price >> p.quantity) {
        string lowerName = p.name;
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (lowerName.find(lowerKeyword) == 0) {
            cout << left << setw(10) << p.id << setw(20) << p.name
                 << setw(10) << p.price << setw(10) << p.quantity << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No products found with name starting from '" << keyword << "'.\n";
    }

    file.close();
}

    bool loadProductById(int searchId) {
        ifstream file("products.txt");
        if (!file) return false;

        while (file >> id >> name >> price >> quantity) {
            if (id == searchId) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    static void reduceStock(int id, int qtyToReduce) {
        ifstream file("products.txt");
        ofstream temp("temp.txt");

        int pid, quantity;
        float price;
        string name;

        while (file >> pid >> name >> price >> quantity) {
            if (pid == id) {
                quantity -= qtyToReduce;
                if (quantity < 0) quantity = 0;
            }
            temp << pid << " " << name << " " << price << " " << quantity << "\n";
        }

        file.close();
        temp.close();
        remove("products.txt");
        rename("temp.txt", "products.txt");
    }

    void display() const {
        cout << "ID: " << id << " | Name: " << name << " | Price: ₹" << price << " | Qty: " << quantity << "\n";
    }

    void display(ofstream &out) const {
        out << "ID: " << id << " | Name: " << name << " | Price: ₹" << price << " | Qty: " << quantity << "\n";
    }

    void setQuantity(int q) { quantity = q; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
};

double Product::income = 0;

// ----------------- Admin --------------------
void adminMenu() {
    int ch;
    while(true) {
        cout << "\n=== Admin Panel ===\n";
        cout << "1. Add Product\n";
        cout << "2. Search Product\n";
        cout << "3. Update Product\n";
        cout << "4. Delete Product\n";
        cout << "5. Display All\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        if(ch == 0) break;

        switch(ch) {
            case 1: {
                Product p;
                p.input();
                p.saveToFileSorted();
                break;
            }
            case 2: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                Product::searchById(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter ID to update: ";
                cin >> id;
                Product::updateById(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                Product::deleteById(id);
                break;
            }
            case 5:
                Product::viewAll();
                break;
            default:
                cout << "Invalid Option\n";
        }
    }
}

// ---------------- Customer ------------------
void customerPanel() {
    vector<Product> cart;
    int choice;

    while (true) {
        cout << "\n========== Customer Panel ==========\n";
        cout << "1. View All Products\n";
        cout << "2. Search Products by Name\n";
        cout << "3. Add Product to Cart\n";
        cout << "4. View Cart\n";
        cout << "5. Generate Bill\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Product::viewAll();
        }
        else if (choice == 2) {
            string query;
            cout << "Enter name or starting letter: ";
            cin >> query;
            Product::searchByName(query);
        }
        else if (choice == 3) {
            int id, qty;
            cout << "Enter Product ID to add to cart: ";
            cin >> id;
            Product p;
            if (p.loadProductById(id)) {
                cout << "Enter quantity: ";
                cin >> qty;
                if (qty > p.getQuantity()) {
                    cout << "Only " << p.getQuantity() << " available. Choose less quantity!\n";
                } else {
                    p.setQuantity(qty);
                    cart.push_back(p);
                    cout << "Product added to cart.\n";
                }
            } else {
                cout << "Product not found.\n";
            }
        }
        else if (choice == 4) {
            if (cart.empty()) {
                cout << "Cart is empty.\n";
            } else {
                double total = 0;
                for (auto &item : cart) {
                    item.display();
                    double cost = item.getPrice() * item.getQuantity();
                    total += cost;
                }
                cout << "Total Cart Value: " << total << "\n";
            }
        }
        else if (choice == 5) {
            if (cart.empty()) {
                cout << "Cart is empty.\n";
                continue;
            }
            double total = 0;
            ofstream fout("bill.txt");
            fout << "========== Final Bill ==========\n";

            for (auto& item : cart) {
                item.display();
                item.display(fout);
                double cost = item.getPrice() * item.getQuantity();
                fout << "Subtotal: ₹" << cost << "\n\n";
                total += cost;

                Product::reduceStock(item.id, item.getQuantity());
            }

            fout << "Grand Total: ₹" << total << "\n";
            cout << "Grand Total: " << total << "\n";
            fout.close();
            Product::income += total;

            cout << "Bill generated and saved to 'bill.txt'\n";
            cart.clear();
        }
        else if (choice == 6) {
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
}

// ---------------- MAIN ----------------------
int main() {
    int choice;
    cout << "=============================\n";
    cout << "   Welcome to SuperMarket   \n";
    cout << "=============================\n";
    cout << "1. Admin Panel\n";
    cout << "2. Customer Panel\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if(choice == 1) {
        adminMenu();
    } else if(choice == 2) {
        customerPanel();
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}
