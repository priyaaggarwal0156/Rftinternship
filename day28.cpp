#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

// ============================================================
// FILE NAMES
// ============================================================

const string PRODUCT_FILE = "products.txt";
const string TRANSACTION_FILE = "inventory_transactions.txt";

// ============================================================
// ADMIN CREDENTIALS
// ============================================================

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "warehouse123";

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------------------------------------------------------
// Current Date
// ------------------------------------------------------------

string getCurrentDate()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_mday
       << "-"
       << setw(2) << localTime->tm_mon + 1
       << "-"
       << localTime->tm_year + 1900;

    return ss.str();
}

// ------------------------------------------------------------
// Current Month
// ------------------------------------------------------------

string getCurrentMonth()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_mon + 1
       << "-"
       << localTime->tm_year + 1900;

    return ss.str();
}

// ============================================================
// PRODUCT CLASS
// ============================================================

class Product
{
private:

    int productId;
    string name;
    string category;
    string supplier;

    int quantity;

    int minimumStock;

    double price;

public:

    Product()
        : productId(0),
          quantity(0),
          minimumStock(0),
          price(0)
    {
    }

    Product(
        int id,
        string name,
        string category,
        string supplier,
        int quantity,
        int minimumStock,
        double price)
        :
        productId(id),
        name(name),
        category(category),
        supplier(supplier),
        quantity(quantity),
        minimumStock(minimumStock),
        price(price)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    int getId() const
    {
        return productId;
    }

    string getName() const
    {
        return name;
    }

    string getCategory() const
    {
        return category;
    }

    string getSupplier() const
    {
        return supplier;
    }

    int getQuantity() const
    {
        return quantity;
    }

    int getMinimumStock() const
    {
        return minimumStock;
    }

    double getPrice() const
    {
        return price;
    }

    // --------------------------------------------------------
    // Update Stock
    // --------------------------------------------------------

    void addStock(int amount)
    {
        quantity += amount;
    }

    bool removeStock(int amount)
    {
        if (amount > quantity)
            return false;

        quantity -= amount;

        return true;
    }

    // --------------------------------------------------------
    // Low Stock Check
    // --------------------------------------------------------

    bool isLowStock() const
    {
        return quantity <= minimumStock;
    }

    // --------------------------------------------------------
    // Display
    // --------------------------------------------------------

    void display() const
    {
        cout << left
             << setw(10) << productId
             << setw(25) << name
             << setw(18) << category
             << setw(20) << supplier
             << setw(12) << quantity
             << setw(15) << minimumStock
             << "Rs. "
             << fixed << setprecision(2)
             << price;

        if (isLowStock())
            cout << "  <-- LOW STOCK";

        cout << '\n';
    }

    // --------------------------------------------------------
    // File Serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << productId << "|"
           << name << "|"
           << category << "|"
           << supplier << "|"
           << quantity << "|"
           << minimumStock << "|"
           << price;

        return ss.str();
    }
};

// ============================================================
// TRANSACTION CLASS
// ============================================================

class Transaction
{
private:

    long long transactionId;

    int productId;

    string productName;

    string type;

    int quantity;

    double amount;

    string date;

public:

    Transaction()
        : transactionId(0),
          productId(0),
          quantity(0),
          amount(0)
    {
    }

    Transaction(
        long long id,
        int productId,
        string productName,
        string type,
        int quantity,
        double amount,
        string date)
        :
        transactionId(id),
        productId(productId),
        productName(productName),
        type(type),
        quantity(quantity),
        amount(amount),
        date(date)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    long long getId() const
    {
        return transactionId;
    }

    int getProductId() const
    {
        return productId;
    }

    string getProductName() const
    {
        return productName;
    }

    string getType() const
    {
        return type;
    }

    int getQuantity() const
    {
        return quantity;
    }

    double getAmount() const
    {
        return amount;
    }

    string getDate() const
    {
        return date;
    }

    // --------------------------------------------------------
    // Display
    // --------------------------------------------------------

    void display() const
    {
        cout << left
             << setw(15) << transactionId
             << setw(12) << productId
             << setw(25) << productName
             << setw(18) << type
             << setw(12) << quantity
             << setw(15)
             << fixed << setprecision(2)
             << amount
             << date
             << '\n';
    }

    // --------------------------------------------------------
    // Serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << transactionId << "|"
           << productId << "|"
           << productName << "|"
           << type << "|"
           << quantity << "|"
           << amount << "|"
           << date;

        return ss.str();
    }
};

// ============================================================
// WAREHOUSE MANAGEMENT SYSTEM
// ============================================================

class WarehouseSystem
{
private:

    vector<Product> products;

    vector<Transaction> transactions;

    int nextProductId = 1001;

    long long nextTransactionId = 5000001;

public:

    // ========================================================
    // FIND PRODUCT
    // ========================================================

    Product* findProduct(int productId)
    {
        for (auto& product : products)
        {
            if (product.getId() == productId)
                return &product;
        }

        return nullptr;
    }

    // ========================================================
    // LOAD PRODUCTS
    // ========================================================

    void loadProducts()
    {
        ifstream file(PRODUCT_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string name;
            string category;
            string supplier;
            string quantity;
            string minimumStock;
            string price;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, category, '|');
            getline(ss, supplier, '|');
            getline(ss, quantity, '|');
            getline(ss, minimumStock, '|');
            getline(ss, price, '|');

            Product product(
                stoi(id),
                name,
                category,
                supplier,
                stoi(quantity),
                stoi(minimumStock),
                stod(price)
            );

            products.push_back(product);

            nextProductId =
                max(
                    nextProductId,
                    product.getId() + 1
                );
        }

        file.close();
    }

    // ========================================================
    // SAVE PRODUCTS
    // ========================================================

    void saveProducts()
    {
        ofstream file(PRODUCT_FILE);

        for (const auto& product : products)
        {
            file << product.serialize()
                 << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD TRANSACTIONS
    // ========================================================

    void loadTransactions()
    {
        ifstream file(TRANSACTION_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string productId;
            string productName;
            string type;
            string quantity;
            string amount;
            string date;

            getline(ss, id, '|');
            getline(ss, productId, '|');
            getline(ss, productName, '|');
            getline(ss, type, '|');
            getline(ss, quantity, '|');
            getline(ss, amount, '|');
            getline(ss, date, '|');

            Transaction transaction(
                stoll(id),
                stoi(productId),
                productName,
                type,
                stoi(quantity),
                stod(amount),
                date
            );

            transactions.push_back(transaction);

            nextTransactionId =
                max(
                    nextTransactionId,
                    transaction.getId() + 1
                );
        }

        file.close();
    }

    // ========================================================
    // SAVE TRANSACTIONS
    // ========================================================

    void saveTransactions()
    {
        ofstream file(TRANSACTION_FILE);

        for (const auto& transaction :
             transactions)
        {
            file << transaction.serialize()
                 << '\n';
        }

        file.close();
    }

    // ========================================================
    // ADD TRANSACTION
    // ========================================================

    void addTransaction(
        int productId,
        string productName,
        string type,
        int quantity,
        double amount)
    {
        Transaction transaction(
            nextTransactionId,
            productId,
            productName,
            type,
            quantity,
            amount,
            getCurrentDate()
        );

        transactions.push_back(transaction);

        saveTransactions();

        nextTransactionId++;
    }

    // ========================================================
    // ADD PRODUCT
    // ========================================================

    void addProduct()
    {
        string name;
        string category;
        string supplier;

        int quantity;
        int minimumStock;

        double price;

        clearInput();

        cout << "\n===============================================\n";
        cout << "                 ADD PRODUCT\n";
        cout << "===============================================\n";

        cout << "Product Name: ";
        getline(cin, name);

        cout << "Category: ";
        getline(cin, category);

        cout << "Supplier: ";
        getline(cin, supplier);

        cout << "Initial Quantity: ";
        cin >> quantity;

        cout << "Minimum Stock Level: ";
        cin >> minimumStock;

        cout << "Price per Unit: Rs. ";
        cin >> price;

        if (name.empty() ||
            quantity < 0 ||
            minimumStock < 0 ||
            price < 0)
        {
            cout << "\nInvalid product details.\n";
            return;
        }

        Product product(
            nextProductId,
            name,
            category,
            supplier,
            quantity,
            minimumStock,
            price
        );

        products.push_back(product);

        saveProducts();

        cout << "\nProduct added successfully!\n";

        cout << "Product ID: "
             << nextProductId
             << '\n';

        if (product.isLowStock())
        {
            cout << "\nWARNING: Product is currently "
                 << "at or below minimum stock level!\n";
        }

        nextProductId++;
    }

    // ========================================================
    // DISPLAY INVENTORY
    // ========================================================

    void displayInventory()
    {
        if (products.empty())
        {
            cout << "\nInventory is empty.\n";
            return;
        }

        cout << "\n";
        cout << "================================================================================================\n";
        cout << "                              WAREHOUSE INVENTORY\n";
        cout << "================================================================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Product"
             << setw(18) << "Category"
             << setw(20) << "Supplier"
             << setw(12) << "Quantity"
             << setw(15) << "Min Stock"
             << "Price\n";

        cout << string(100, '-') << '\n';

        for (const auto& product :
             products)
        {
            product.display();
        }

        cout << "================================================================================================\n";
    }

    // ========================================================
    // UPDATE STOCK
    // ========================================================

    void updateStock()
    {
        int productId;

        cout << "\nEnter Product ID: ";
        cin >> productId;

        Product* product =
            findProduct(productId);

        if (product == nullptr)
        {
            cout << "\nProduct not found.\n";
            return;
        }

        cout << "\nProduct: "
             << product->getName()
             << '\n';

        cout << "Current Stock: "
             << product->getQuantity()
             << '\n';

        cout << "\n1. Add Stock\n";
        cout << "2. Remove Stock\n";

        int choice;

        cout << "Enter choice: ";
        cin >> choice;

        int quantity;

        cout << "Enter quantity: ";
        cin >> quantity;

        if (quantity <= 0)
        {
            cout << "\nQuantity must be greater than zero.\n";
            return;
        }

        if (choice == 1)
        {
            product->addStock(quantity);

            addTransaction(
                product->getId(),
                product->getName(),
                "Stock Added",
                quantity,
                quantity * product->getPrice()
            );

            saveProducts();

            cout << "\nStock added successfully.\n";
        }
        else if (choice == 2)
        {
            if (!product->removeStock(quantity))
            {
                cout << "\nInsufficient stock!\n";
                cout << "Available Stock: "
                     << product->getQuantity()
                     << '\n';

                return;
            }

            addTransaction(
                product->getId(),
                product->getName(),
                "Stock Removed",
                quantity,
                quantity * product->getPrice()
            );

            saveProducts();

            cout << "\nStock removed successfully.\n";
        }
        else
        {
            cout << "\nInvalid choice.\n";
            return;
        }

        cout << "Updated Stock: "
             << product->getQuantity()
             << '\n';

        if (product->isLowStock())
        {
            cout << "\nLOW STOCK ALERT!\n";
            cout << "Minimum Required: "
                 << product->getMinimumStock()
                 << '\n';
        }
    }

    // ========================================================
    // SEARCH INVENTORY
    // ========================================================

    void searchInventory()
    {
        clearInput();

        string keyword;

        cout << "\nEnter product name/category/supplier: ";

        getline(cin, keyword);

        if (keyword.empty())
        {
            cout << "\nSearch term cannot be empty.\n";
            return;
        }

        // Convert search term to lowercase
        string searchKeyword = keyword;

        transform(
            searchKeyword.begin(),
            searchKeyword.end(),
            searchKeyword.begin(),
            ::tolower
        );

        bool found = false;

        cout << "\nSearch Results:\n";

        cout << string(100, '-') << '\n';

        for (const auto& product :
             products)
        {
            string name = product.getName();
            string category = product.getCategory();
            string supplier = product.getSupplier();

            transform(
                name.begin(),
                name.end(),
                name.begin(),
                ::tolower
            );

            transform(
                category.begin(),
                category.end(),
                category.begin(),
                ::tolower
            );

            transform(
                supplier.begin(),
                supplier.end(),
                supplier.begin(),
                ::tolower
            );

            if (name.find(searchKeyword) != string::npos ||
                category.find(searchKeyword) != string::npos ||
                supplier.find(searchKeyword) != string::npos)
            {
                product.display();

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo matching product found.\n";
        }

        cout << string(100, '-') << '\n';
    }

    // ========================================================
    // DISPATCH ORDER
    // ========================================================

    void dispatchOrder()
    {
        int productId;
        int quantity;

        cout << "\n===============================================\n";
        cout << "                DISPATCH ORDER\n";
        cout << "===============================================\n";

        cout << "Enter Product ID: ";
        cin >> productId;

        Product* product =
            findProduct(productId);

        if (product == nullptr)
        {
            cout << "\nProduct not found.\n";
            return;
        }

        cout << "Product Name: "
             << product->getName()
             << '\n';

        cout << "Available Stock: "
             << product->getQuantity()
             << '\n';

        cout << "Quantity to Dispatch: ";
        cin >> quantity;

        if (quantity <= 0)
        {
            cout << "\nInvalid quantity.\n";
            return;
        }

        if (!product->removeStock(quantity))
        {
            cout << "\nCannot dispatch order.\n";
            cout << "Insufficient stock!\n";
            return;
        }

        double amount =
            quantity *
            product->getPrice();

        addTransaction(
            product->getId(),
            product->getName(),
            "Order Dispatched",
            quantity,
            amount
        );

        saveProducts();

        cout << "\nOrder dispatched successfully!\n";

        cout << "Product       : "
             << product->getName()
             << '\n';

        cout << "Quantity      : "
             << quantity
             << '\n';

        cout << "Order Value   : Rs. "
             << fixed << setprecision(2)
             << amount
             << '\n';

        cout << "Remaining Stock: "
             << product->getQuantity()
             << '\n';

        if (product->isLowStock())
        {
            cout << "\n*** LOW STOCK ALERT ***\n";
        }
    }

    // ========================================================
    // RECEIVE SHIPMENT
    // ========================================================

    void receiveShipment()
    {
        int productId;
        int quantity;

        cout << "\n===============================================\n";
        cout << "               RECEIVE SHIPMENT\n";
        cout << "===============================================\n";

        cout << "Enter Product ID: ";
        cin >> productId;

        Product* product =
            findProduct(productId);

        if (product == nullptr)
        {
            cout << "\nProduct not found.\n";
            return;
        }

        cout << "Product Name: "
             << product->getName()
             << '\n';

        cout << "Current Stock: "
             << product->getQuantity()
             << '\n';

        cout << "Quantity Received: ";
        cin >> quantity;

        if (quantity <= 0)
        {
            cout << "\nInvalid quantity.\n";
            return;
        }

        product->addStock(quantity);

        double amount =
            quantity *
            product->getPrice();

        addTransaction(
            product->getId(),
            product->getName(),
            "Shipment Received",
            quantity,
            amount
        );

        saveProducts();

        cout << "\nShipment received successfully!\n";

        cout << "Quantity Added: "
             << quantity
             << '\n';

        cout << "Updated Stock: "
             << product->getQuantity()
             << '\n';
    }

    // ========================================================
    // LOW STOCK ALERTS
    // ========================================================

    void lowStockAlerts()
    {
        bool found = false;

        cout << "\n";
        cout << "===============================================\n";
        cout << "                LOW STOCK ALERTS\n";
        cout << "===============================================\n";

        for (const auto& product :
             products)
        {
            if (product.isLowStock())
            {
                cout << "\nProduct ID     : "
                     << product.getId();

                cout << "\nProduct Name   : "
                     << product.getName();

                cout << "\nCurrent Stock  : "
                     << product.getQuantity();

                cout << "\nMinimum Stock  : "
                     << product.getMinimumStock();

                cout << "\n-----------------------------------------------\n";

                found = true;
            }
        }

        if (!found)
        {
            cout << "\nNo low-stock products.\n";
        }
    }

    // ========================================================
    // INVENTORY REPORT
    // ========================================================

    void inventoryReport()
    {
        if (products.empty())
        {
            cout << "\nNo inventory data available.\n";
            return;
        }

        int totalProducts = 0;
        int totalUnits = 0;
        int lowStockProducts = 0;

        double totalInventoryValue = 0;

        for (const auto& product :
             products)
        {
            totalProducts++;

            totalUnits +=
                product.getQuantity();

            totalInventoryValue +=
                product.getQuantity()
                *
                product.getPrice();

            if (product.isLowStock())
                lowStockProducts++;
        }

        cout << "\n";
        cout << "====================================================\n";
        cout << "              INVENTORY REPORT\n";
        cout << "====================================================\n";

        cout << "Total Products       : "
             << totalProducts
             << '\n';

        cout << "Total Units in Stock : "
             << totalUnits
             << '\n';

        cout << "Low Stock Products   : "
             << lowStockProducts
             << '\n';

        cout << "Inventory Value      : Rs. "
             << fixed << setprecision(2)
             << totalInventoryValue
             << '\n';

        cout << "====================================================\n";
    }

    // ========================================================
    // MONTHLY INVENTORY SUMMARY
    // ========================================================

    void monthlyInventorySummary()
    {
        string currentMonth =
            getCurrentMonth();

        int received = 0;
        int dispatched = 0;
        int added = 0;
        int removed = 0;

        double receivedValue = 0;
        double dispatchedValue = 0;

        for (const auto& transaction :
             transactions)
        {
            string date =
                transaction.getDate();

            // Date format is DD-MM-YYYY
            string monthYear =
                date.substr(3, 7);

            if (monthYear != currentMonth)
                continue;

            string type =
                transaction.getType();

            if (type == "Shipment Received")
            {
                received +=
                    transaction.getQuantity();

                receivedValue +=
                    transaction.getAmount();
            }
            else if (type == "Order Dispatched")
            {
                dispatched +=
                    transaction.getQuantity();

                dispatchedValue +=
                    transaction.getAmount();
            }
            else if (type == "Stock Added")
            {
                added +=
                    transaction.getQuantity();
            }
            else if (type == "Stock Removed")
            {
                removed +=
                    transaction.getQuantity();
            }
        }

        cout << "\n";
        cout << "====================================================\n";
        cout << "          MONTHLY INVENTORY SUMMARY\n";
        cout << "====================================================\n";

        cout << "Month : "
             << currentMonth
             << '\n';

        cout << "\nSHIPMENTS RECEIVED\n";

        cout << "Units Received      : "
             << received
             << '\n';

        cout << "Received Value      : Rs. "
             << fixed << setprecision(2)
             << receivedValue
             << '\n';

        cout << "\nORDERS DISPATCHED\n";

        cout << "Units Dispatched    : "
             << dispatched
             << '\n';

        cout << "Dispatched Value    : Rs. "
             << fixed << setprecision(2)
             << dispatchedValue
             << '\n';

        cout << "\nMANUAL STOCK CHANGES\n";

        cout << "Stock Added         : "
             << added
             << '\n';

        cout << "Stock Removed       : "
             << removed
             << '\n';

        cout << "====================================================\n";
    }

    // ========================================================
    // TRANSACTION HISTORY
    // ========================================================

    void transactionHistory()
    {
        if (transactions.empty())
        {
            cout << "\nNo transactions available.\n";
            return;
        }

        cout << "\n";
        cout << "================================================================================================\n";
        cout << "                         INVENTORY TRANSACTION HISTORY\n";
        cout << "================================================================================================\n";

        cout << left
             << setw(15) << "Transaction ID"
             << setw(12) << "Product ID"
             << setw(25) << "Product"
             << setw(18) << "Type"
             << setw(12) << "Quantity"
             << setw(15) << "Amount"
             << "Date\n";

        cout << string(110, '-') << '\n';

        for (const auto& transaction :
             transactions)
        {
            transaction.display();
        }

        cout << "================================================================================================\n";
    }

    // ========================================================
    // ADMIN LOGIN
    // ========================================================

    bool adminLogin()
    {
        string username;
        string password;

        clearInput();

        cout << "\n===============================================\n";
        cout << "                ADMIN LOGIN\n";
        cout << "===============================================\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (username == ADMIN_USERNAME &&
            password == ADMIN_PASSWORD)
        {
            cout << "\nLogin successful!\n";
            return true;
        }

        cout << "\nInvalid username or password.\n";

        return false;
    }

    // ========================================================
    // ADMIN DASHBOARD
    // ========================================================

    void adminDashboard()
    {
        if (!adminLogin())
            return;

        int choice;

        do
        {
            cout << "\n";
            cout << "====================================================\n";
            cout << "              WAREHOUSE ADMIN DASHBOARD\n";
            cout << "====================================================\n";

            cout << "1. Add Product\n";
            cout << "2. Display Inventory\n";
            cout << "3. Update Stock\n";
            cout << "4. Search Inventory\n";
            cout << "5. Dispatch Order\n";
            cout << "6. Receive Shipment\n";
            cout << "7. Low Stock Alerts\n";
            cout << "8. Inventory Report\n";
            cout << "9. Monthly Inventory Summary\n";
            cout << "10. Transaction History\n";
            cout << "11. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addProduct();
                    break;

                case 2:
                    displayInventory();
                    break;

                case 3:
                    updateStock();
                    break;

                case 4:
                    searchInventory();
                    break;

                case 5:
                    dispatchOrder();
                    break;

                case 6:
                    receiveShipment();
                    break;

                case 7:
                    lowStockAlerts();
                    break;

                case 8:
                    inventoryReport();
                    break;

                case 9:
                    monthlyInventorySummary();
                    break;

                case 10:
                    transactionHistory();
                    break;

                case 11:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 11);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadProducts();
        loadTransactions();

        int choice;

        do
        {
            cout << "\n\n";

            cout << "====================================================\n";
            cout << "             WAREHOUSE INVENTORY SYSTEM\n";
            cout << "====================================================\n";

            cout << "1. View Inventory\n";
            cout << "2. Search Inventory\n";
            cout << "3. Update Stock\n";
            cout << "4. Dispatch Order\n";
            cout << "5. Receive Shipment\n";
            cout << "6. Inventory Report\n";
            cout << "7. Low Stock Alerts\n";
            cout << "8. Transaction History\n";
            cout << "9. Admin Login\n";
            cout << "10. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayInventory();
                    break;

                case 2:
                    searchInventory();
                    break;

                case 3:
                    updateStock();
                    break;

                case 4:
                    dispatchOrder();
                    break;

                case 5:
                    receiveShipment();
                    break;

                case 6:
                    inventoryReport();
                    break;

                case 7:
                    lowStockAlerts();
                    break;

                case 8:
                    transactionHistory();
                    break;

                case 9:
                    adminDashboard();
                    break;

                case 10:

                    saveProducts();
                    saveTransactions();

                    cout << "\n";
                    cout << "====================================================\n";
                    cout << "     Thank you for using Warehouse System!\n";
                    cout << "====================================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }

        } while (choice != 10);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    WarehouseSystem system;

    system.run();

    return 0;
}