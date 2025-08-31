#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <numeric> // For std::accumulate if needed

using namespace std;

// --- Structures ---
struct Phone {
    string brand;
    string model;
    float price; // This will now be the selling price
    float costPrice; // New: To track the cost of the phone
    int stock;
};

struct Salesman {
    string name;
    float salary;
};

struct Sale {
    string phoneModel;
    int quantitySold;
    float salePricePerUnit;
    float costPricePerUnit; // New: To track the cost at the time of sale
};

// --- Global Variables ---
vector<Phone> showroom;
vector<Salesman> salesmen;
vector<Sale> salesHistory; // To store all sales transactions
string showroomName = "SJSM Technology";
// Removed PROFIT_MARGIN as profit will now be calculated based on (salePrice - costPrice)

// --- Initialization Functions ---
void initializeShowroom() {
    showroom.push_back({"Samsung", "Galaxy S21", 79900.00, 65000.00, 10}); // Prices in BDT
    showroom.push_back({"Apple", "iPhone 13", 99900.00, 80000.00, 5});     // Prices in BDT
    showroom.push_back({"OnePlus", "9 Pro", 72900.00, 60000.00, 7});     // Prices in BDT
}

void initializeSalesmen() {
    salesmen.push_back({"Sumon", 25000.00});
    salesmen.push_back({"Niloy", 24000.00});
    salesmen.push_back({"Kaiser", 23000.00});
    salesmen.push_back({"Prottoy", 22000.00});
}

// --- Display Functions ---
void displaySalesmen() {
    cout << "\nSalesmen at " << showroomName << ":\n";
    if (salesmen.empty()) {
        cout << "No salesmen available.\n";
        return;
    }
    for (const auto& s : salesmen) {
        cout << "- " << s.name << " (Salary: BDT " << fixed << setprecision(2) << s.salary << ")\n";
    }
}

void displayPhones() {
    cout << "\nWelcome to " << showroomName << "!\n";
    if (showroom.empty()) {
        cout << "No phones available.\n";
        return;
    }
    cout << "\nAvailable Phones:\n";
    cout << left << setw(15) << "Brand" << setw(15) << "Model" << setw(15) << "Sell Price (BDT)" << setw(10) << "Stock" << "\n"; // Changed "Price" to "Sell Price (BDT)"
    cout << setfill('-') << setw(59) << "" << setfill(' ') << "\n"; // Adjusted width
    for (const auto& p : showroom) {
        cout << left << setw(15) << p.brand << setw(15) << p.model
             << "BDT " << setw(11) << fixed << setprecision(2) << p.price << setw(10) << p.stock << "\n"; // Changed "$" to "BDT "
    }
}

// --- Phone Management Functions ---
void addPhone() {
    Phone p;
    cout << "Enter brand: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, p.brand);
    cout << "Enter model: ";
    getline(cin, p.model);
    cout << "Enter selling price (BDT): "; // Changed prompt
    while (!(cin >> p.price)) {
        cout << "Invalid input. Please enter a valid selling price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter cost price (BDT): "; // New prompt for cost price
    while (!(cin >> p.costPrice)) {
        cout << "Invalid input. Please enter a valid cost price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter stock quantity: ";
    while (!(cin >> p.stock)) {
        cout << "Invalid input. Please enter a valid stock quantity: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    showroom.push_back(p);
    cout << "Phone added successfully.\n";
}

void searchPhone() {
    string model;
    cout << "Enter model to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, model);
    bool found = false;
    cout << "\nSearch Results:\n";
    cout << left << setw(15) << "Brand" << setw(15) << "Model" << setw(15) << "Sell Price (BDT)" << setw(10) << "Stock" << "\n"; // Changed "Price" to "Sell Price (BDT)"
    cout << setfill('-') << setw(59) << "" << setfill(' ') << "\n"; // Adjusted width
    for (const auto& p : showroom) {
        if (p.model == model) {
            cout << left << setw(15) << p.brand << setw(15) << p.model
                 << "BDT " << setw(11) << fixed << setprecision(2) << p.price << setw(10) << p.stock << "\n"; // Changed "$" to "BDT "
            found = true;
        }
    }
    if (!found)
        cout << "Phone with model '" << model << "' not found.\n";
}

void deletePhone() {
    string model;
    cout << "Enter model to delete: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, model);
    for (auto it = showroom.begin(); it != showroom.end(); ++it) {
        if (it->model == model) {
            showroom.erase(it);
            cout << "Phone deleted successfully.\n";
            return;
        }
    }
    cout << "Phone with model '" << model << "' not found.\n";
}

void sellPhone() {
    string model;
    int quantity;
    cout << "Enter model to sell: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, model);
    cout << "Enter quantity to sell: ";
    cin >> quantity;

    for (auto& p : showroom) {
        if (p.model == model) {
            if (quantity <= 0) {
                cout << "Invalid quantity to sell.\n";
            } else if (p.stock >= quantity) {
                p.stock -= quantity;
                // Record the sale, including cost price
                salesHistory.push_back({p.model, quantity, p.price, p.costPrice});
                cout << quantity << " unit(s) of " << p.brand << " " << p.model << " sold successfully.\n";
            } else {
                cout << "Not enough stock. Available: " << p.stock << "\n";
            }
            return;
        }
    }
    cout << "Phone with model '" << model << "' not found.\n";
}

void updatePhonePrice() {
    string model;
    float newPrice;
    cout << "Enter model to update selling price: "; // Changed prompt
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, model);
    cout << "Enter new selling price (BDT): "; // Changed prompt
    while (!(cin >> newPrice)) {
        cout << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (auto& p : showroom) {
        if (p.model == model) {
            p.price = newPrice;
            cout << "Updated selling price of " << p.brand << " " << p.model << " to BDT " << fixed << setprecision(2) << newPrice << ".\n"; // Changed "$" to "BDT "
            return;
        }
    }
    cout << "Phone with model '" << model << "' not found.\n";
}

// --- Salesman Management Functions ---
void addSalesman() {
    Salesman s;
    cout << "Enter salesman's name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, s.name);
    cout << "Enter salesman's salary (BDT): "; // Changed prompt
    while (!(cin >> s.salary)) {
        cout << "Invalid salary. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    salesmen.push_back(s);
    cout << "Salesman '" << s.name << "' added successfully.\n";
}

// --- Reporting Functions ---
void showTodaysSalesReport() {
    cout << "\n--- Today's Sales Report ---\n";
    if (salesHistory.empty()) {
        cout << "No sales recorded yet today.\n";
        return;
    }

    int totalPhonesSold = 0;
    float totalRevenue = 0.0f;
    float totalProfit = 0.0f;
    float totalLoss = 0.0f; // New: To track losses

    cout << left << setw(20) << "Phone Model" << setw(10) << "Qty Sold" << setw(18) << "Revenue (BDT)" << setw(15) << "Profit/Loss (BDT)" << "\n"; // Adjusted headers
    cout << setfill('-') << setw(63) << "" << setfill(' ') << "\n"; // Adjusted width

    for (const auto& sale : salesHistory) {
        float individualRevenue = sale.quantitySold * sale.salePricePerUnit;
        float individualProfitLoss = (sale.salePricePerUnit - sale.costPricePerUnit) * sale.quantitySold;

        totalPhonesSold += sale.quantitySold;
        totalRevenue += individualRevenue;

        if (individualProfitLoss >= 0) {
            totalProfit += individualProfitLoss;
        } else {
            totalLoss += individualProfitLoss; // Accumulate negative values as loss
        }

        cout << left << setw(20) << sale.phoneModel << setw(10) << sale.quantitySold
             << "BDT " << setw(14) << fixed << setprecision(2) << individualRevenue;

        // Display profit or loss clearly
        if (individualProfitLoss >= 0) {
            cout << "BDT +" << setw(13) << fixed << setprecision(2) << individualProfitLoss << "\n";
        } else {
            cout << "BDT -" << setw(13) << fixed << setprecision(2) << abs(individualProfitLoss) << "\n"; // Display loss as positive number
        }
    }

    cout << setfill('-') << setw(63) << "" << setfill(' ') << "\n"; // Adjusted width
    cout << "Total Phones Sold: " << totalPhonesSold << "\n";
    cout << "Total Revenue: BDT " << fixed << setprecision(2) << totalRevenue << "\n";
    cout << "Total Profit: BDT " << fixed << setprecision(2) << totalProfit << "\n";
    cout << "Total Loss: BDT " << fixed << setprecision(2) << abs(totalLoss) << "\n"; // Display total loss as positive
}


// --- Main Function ---
int main() {
    initializeShowroom();
    initializeSalesmen();

    cout << "\nWelcome to " << showroomName << "!\n";
    displaySalesmen(); // Display salesmen on startup

    int choice;
    do {
        cout << "\n--- " << showroomName << " Management ---\n";
        cout << "1. Display Phones\n2. Add Phone\n3. Search Phone\n4. Delete Phone\n5. Sell Phone\n";
        cout << "6. Add Salesman\n7. Display Salesmen\n8. Update Phone Selling Price\n9. Show Today's Sales Report\n10. Exit\n"; // Changed option 8 and 9
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: displayPhones(); break;
            case 2: addPhone(); break;
            case 3: searchPhone(); break;
            case 4: deletePhone(); break;
            case 5: sellPhone(); break;
            case 6: addSalesman(); break;
            case 7: displaySalesmen(); break;
            case 8: updatePhonePrice(); break;
            case 9: showTodaysSalesReport(); break;
            case 10: cout << "Exiting...\n"; break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 10.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    } while (choice != 10);

    return 0;
}
