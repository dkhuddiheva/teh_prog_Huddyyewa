#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Product {
    string id;
    string name;
    string category;
    string price;
    string quantity;
};

const int MAX_PRODUCTS = 1000; // Максимальное количество записей
Product products[MAX_PRODUCTS];
int productCount = 0;

void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    productCount = 0;
    string line;
    while (getline(file, line)) {
        if (productCount >= MAX_PRODUCTS) break;
        stringstream ss(line);
        getline(ss, products[productCount].id, ',');
        getline(ss, products[productCount].name, ',');
        getline(ss, products[productCount].category, ',');
        getline(ss, products[productCount].price, ',');
        getline(ss, products[productCount].quantity, ',');
        productCount++;
    }
    file.close();
}

void saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    for (int i = 0; i < productCount; i++) {
        file << products[i].id << "," << products[i].name << "," 
             << products[i].category << "," << products[i].price << "," 
             << products[i].quantity << endl;
    }
    file.close();
}

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cerr << "Cannot add more products" << endl;
        return;
    }
    cout << "Enter ID: ";
    cin >> products[productCount].id;
    cout << "Enter Name: ";
    cin >> products[productCount].name;
    cout << "Enter Category: ";
    cin >> products[productCount].category;
    cout << "Enter Price: ";
    cin >> products[productCount].price;
    cout << "Enter Quantity: ";
    cin >> products[productCount].quantity;
    productCount++;
}

void editProduct() {
    string id;
    cout << "Enter ID of product to edit: ";
    cin >> id;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "Editing product with ID: " << id << endl;
            cout << "Enter new Name: ";
            cin >> products[i].name;
            cout << "Enter new Category: ";
            cin >> products[i].category;
            cout << "Enter new Price: ";
            cin >> products[i].price;
            cout << "Enter new Quantity: ";
            cin >> products[i].quantity;
            return;
        }
    }
    cout << "Product with ID " << id << " not found." << endl;
}

void deleteProduct() {
    string id;
    cout << "Enter ID of product to delete: ";
    cin >> id;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            cout << "Product with ID " << id << " deleted." << endl;
            return;
        }
    }
    cout << "Product with ID " << id << " not found." << endl;
}

void searchProduct() {
    string id;
    cout << "Enter ID of product to search: ";
    cin >> id;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "Product found:" << endl;
            cout << "ID: " << products[i].id << endl;
            cout << "Name: " << products[i].name << endl;
            cout << "Category: " << products[i].category << endl;
            cout << "Price: " << products[i].price << endl;
            cout << "Quantity: " << products[i].quantity << endl;
            return;
        }
    }
    cout << "Product with ID " << id << " not found." << endl;
}

void displayAllProducts() {
    if (productCount == 0) {
        cout << "No products in the database." << endl;
        return;
    }
    for (int i = 0; i < productCount; i++) {
        cout << "ID: " << products[i].id << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Category: " << products[i].category << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Quantity: " << products[i].quantity << endl;
        cout << "---------------------" << endl;
    }
}

int main() {
    string filename = "products.txt";
    loadFromFile(filename);
    while (true) {
        cout << "1. Add Product" << endl;
        cout << "2. Edit Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Search Product" << endl;
        cout << "5. Display All Products" << endl;
        cout << "6. Save and Exit" << endl;
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                searchProduct();
                break;
            case 5:
                displayAllProducts();
                break;
            case 6:
                saveToFile(filename);
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}
