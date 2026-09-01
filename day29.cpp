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
// FILES
// ============================================================

const string MENU_FILE = "menu.txt";
const string ORDER_FILE = "orders.txt";
const string RESERVATION_FILE = "reservations.txt";

// ============================================================
// ADMIN CREDENTIALS
// ============================================================

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "restaurant123";

// ============================================================
// CONSTANTS
// ============================================================

const double GST_RATE = 0.05;

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------------------------------------------------------
// Get Current Date
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
// Get Current Date and Time
// ------------------------------------------------------------

string getCurrentDateTime()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_mday
       << "-"
       << setw(2) << localTime->tm_mon + 1
       << "-"
       << localTime->tm_year + 1900
       << " "
       << setw(2) << localTime->tm_hour
       << ":"
       << setw(2) << localTime->tm_min;

    return ss.str();
}

// ============================================================
// MENU ITEM CLASS
// ============================================================

class MenuItem
{
private:

    int itemId;
    string name;
    string category;
    double price;
    bool available;

public:

    MenuItem()
        : itemId(0),
          price(0),
          available(true)
    {
    }

    MenuItem(
        int id,
        string name,
        string category,
        double price,
        bool available = true)
        :
        itemId(id),
        name(name),
        category(category),
        price(price),
        available(available)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    int getId() const
    {
        return itemId;
    }

    string getName() const
    {
        return name;
    }

    string getCategory() const
    {
        return category;
    }

    double getPrice() const
    {
        return price;
    }

    bool isAvailable() const
    {
        return available;
    }

    // --------------------------------------------------------
    // Availability
    // --------------------------------------------------------

    void setAvailability(bool value)
    {
        available = value;
    }

    // --------------------------------------------------------
    // Display
    // --------------------------------------------------------

    void display() const
    {
        cout << left
             << setw(8) << itemId
             << setw(28) << name
             << setw(18) << category
             << "Rs. "
             << setw(12)
             << fixed << setprecision(2)
             << price;

        if (available)
            cout << "Available";
        else
            cout << "Unavailable";

        cout << '\n';
    }

    // --------------------------------------------------------
    // Serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << itemId << "|"
           << name << "|"
           << category << "|"
           << price << "|"
           << available;

        return ss.str();
    }
};

// ============================================================
// ORDER ITEM CLASS
// ============================================================

class OrderItem
{
private:

    int itemId;
    string itemName;
    int quantity;
    double price;

public:

    OrderItem()
        : itemId(0),
          quantity(0),
          price(0)
    {
    }

    OrderItem(
        int id,
        string name,
        int quantity,
        double price)
        :
        itemId(id),
        itemName(name),
        quantity(quantity),
        price(price)
    {
    }

    int getItemId() const
    {
        return itemId;
    }

    string getItemName() const
    {
        return itemName;
    }

    int getQuantity() const
    {
        return quantity;
    }

    double getPrice() const
    {
        return price;
    }

    double getTotal() const
    {
        return quantity * price;
    }
};

// ============================================================
// ORDER CLASS
// ============================================================

class Order
{
private:

    long long orderId;

    int tableNumber;

    string customerName;

    string date;

    string status;

    vector<OrderItem> items;

public:

    Order()
        : orderId(0),
          tableNumber(0)
    {
    }

    Order(
        long long id,
        int table,
        string customer,
        string date,
        string status,
        vector<OrderItem> items)
        :
        orderId(id),
        tableNumber(table),
        customerName(customer),
        date(date),
        status(status),
        items(items)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    long long getId() const
    {
        return orderId;
    }

    int getTableNumber() const
    {
        return tableNumber;
    }

    string getCustomerName() const
    {
        return customerName;
    }

    string getDate() const
    {
        return date;
    }

    string getStatus() const
    {
        return status;
    }

    vector<OrderItem> getItems() const
    {
        return items;
    }

    // --------------------------------------------------------
    // Status
    // --------------------------------------------------------

    void setStatus(string newStatus)
    {
        status = newStatus;
    }

    // --------------------------------------------------------
    // Subtotal
    // --------------------------------------------------------

    double getSubtotal() const
    {
        double subtotal = 0;

        for (const auto& item : items)
        {
            subtotal += item.getTotal();
        }

        return subtotal;
    }

    // --------------------------------------------------------
    // GST
    // --------------------------------------------------------

    double getGST() const
    {
        return getSubtotal() * GST_RATE;
    }

    // --------------------------------------------------------
    // Final Total
    // --------------------------------------------------------

    double getTotal() const
    {
        return getSubtotal() + getGST();
    }

    // --------------------------------------------------------
    // Receipt
    // --------------------------------------------------------

    void printBill() const
    {
        cout << "\n";
        cout << "====================================================\n";
        cout << "              RESTAURANT BILL\n";
        cout << "====================================================\n";

        cout << "Order ID       : "
             << orderId << '\n';

        cout << "Customer       : "
             << customerName << '\n';

        cout << "Table Number   : "
             << tableNumber << '\n';

        cout << "Date           : "
             << date << '\n';

        cout << "Status         : "
             << status << '\n';

        cout << "----------------------------------------------------\n";

        cout << left
             << setw(25) << "Item"
             << setw(10) << "Qty"
             << setw(15) << "Price"
             << "Total\n";

        cout << "----------------------------------------------------\n";

        for (const auto& item : items)
        {
            cout << left
                 << setw(25) << item.getItemName()
                 << setw(10) << item.getQuantity()
                 << setw(15)
                 << fixed << setprecision(2)
                 << item.getPrice()
                 << item.getTotal()
                 << '\n';
        }

        cout << "----------------------------------------------------\n";

        cout << right
             << setw(38)
             << "Subtotal: Rs. "
             << fixed << setprecision(2)
             << getSubtotal()
             << '\n';

        cout << setw(38)
             << "GST (5%): Rs. "
             << getGST()
             << '\n';

        cout << setw(38)
             << "Grand Total: Rs. "
             << getTotal()
             << '\n';

        cout << "====================================================\n";
        cout << "              Thank you! Visit Again!\n";
        cout << "====================================================\n";
    }

    // --------------------------------------------------------
    // Serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << orderId << "|"
           << tableNumber << "|"
           << customerName << "|"
           << date << "|"
           << status << "|";

        for (size_t i = 0; i < items.size(); i++)
        {
            ss << items[i].getItemId()
               << ","
               << items[i].getItemName()
               << ","
               << items[i].getQuantity()
               << ","
               << items[i].getPrice();

            if (i != items.size() - 1)
                ss << ";";
        }

        return ss.str();
    }
};

// ============================================================
// RESERVATION CLASS
// ============================================================

class Reservation
{
private:

    int reservationId;

    string customerName;
    string phone;

    int tableNumber;

    string date;
    string time;

    int guests;

    string status;

public:

    Reservation()
        : reservationId(0),
          tableNumber(0),
          guests(0)
    {
    }

    Reservation(
        int id,
        string customer,
        string phone,
        int table,
        string date,
        string time,
        int guests,
        string status)
        :
        reservationId(id),
        customerName(customer),
        phone(phone),
        tableNumber(table),
        date(date),
        time(time),
        guests(guests),
        status(status)
    {
    }

    int getId() const
    {
        return reservationId;
    }

    int getTableNumber() const
    {
        return tableNumber;
    }

    string getDate() const
    {
        return date;
    }

    string getTime() const
    {
        return time;
    }

    string getStatus() const
    {
        return status;
    }

    void cancel()
    {
        status = "Cancelled";
    }

    void display() const
    {
        cout << left
             << setw(10) << reservationId
             << setw(22) << customerName
             << setw(15) << phone
             << setw(10) << tableNumber
             << setw(15) << date
             << setw(10) << time
             << setw(10) << guests
             << status
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << reservationId << "|"
           << customerName << "|"
           << phone << "|"
           << tableNumber << "|"
           << date << "|"
           << time << "|"
           << guests << "|"
           << status;

        return ss.str();
    }
};

// ============================================================
// RESTAURANT MANAGEMENT SYSTEM
// ============================================================

class RestaurantSystem
{
private:

    vector<MenuItem> menu;

    vector<Order> orders;

    vector<Reservation> reservations;

    int nextItemId = 101;

    long long nextOrderId = 500001;

    int nextReservationId = 1001;

    const int TOTAL_TABLES = 20;

public:

    // ========================================================
    // FIND MENU ITEM
    // ========================================================

    MenuItem* findMenuItem(int id)
    {
        for (auto& item : menu)
        {
            if (item.getId() == id)
                return &item;
        }

        return nullptr;
    }

    // ========================================================
    // FIND ORDER
    // ========================================================

    Order* findOrder(long long id)
    {
        for (auto& order : orders)
        {
            if (order.getId() == id)
                return &order;
        }

        return nullptr;
    }

    // ========================================================
    // LOAD MENU
    // ========================================================

    void loadMenu()
    {
        ifstream file(MENU_FILE);

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
            string price;
            string available;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, category, '|');
            getline(ss, price, '|');
            getline(ss, available, '|');

            MenuItem item(
                stoi(id),
                name,
                category,
                stod(price),
                stoi(available)
            );

            menu.push_back(item);

            nextItemId =
                max(
                    nextItemId,
                    item.getId() + 1
                );
        }

        file.close();
    }

    // ========================================================
    // SAVE MENU
    // ========================================================

    void saveMenu()
    {
        ofstream file(MENU_FILE);

        for (const auto& item : menu)
        {
            file << item.serialize()
                 << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD RESERVATIONS
    // ========================================================

    void loadReservations()
    {
        ifstream file(RESERVATION_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string customer;
            string phone;
            string table;
            string date;
            string time;
            string guests;
            string status;

            getline(ss, id, '|');
            getline(ss, customer, '|');
            getline(ss, phone, '|');
            getline(ss, table, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, guests, '|');
            getline(ss, status, '|');

            Reservation reservation(
                stoi(id),
                customer,
                phone,
                stoi(table),
                date,
                time,
                stoi(guests),
                status
            );

            reservations.push_back(reservation);

            nextReservationId =
                max(
                    nextReservationId,
                    reservation.getId() + 1
                );
        }

        file.close();
    }

    // ========================================================
    // SAVE RESERVATIONS
    // ========================================================

    void saveReservations()
    {
        ofstream file(RESERVATION_FILE);

        for (const auto& reservation :
             reservations)
        {
            file << reservation.serialize()
                 << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD ORDERS
    // ========================================================

    void loadOrders()
    {
        ifstream file(ORDER_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string table;
            string customer;
            string date;
            string status;
            string itemData;

            getline(ss, id, '|');
            getline(ss, table, '|');
            getline(ss, customer, '|');
            getline(ss, date, '|');
            getline(ss, status, '|');
            getline(ss, itemData, '|');

            vector<OrderItem> items;

            stringstream itemStream(itemData);

            string itemRecord;

            while (getline(
                itemStream,
                itemRecord,
                ';'))
            {
                stringstream itemSS(itemRecord);

                string itemId;
                string itemName;
                string quantity;
                string price;

                getline(itemSS, itemId, ',');
                getline(itemSS, itemName, ',');
                getline(itemSS, quantity, ',');
                getline(itemSS, price, ',');

                items.emplace_back(
                    stoi(itemId),
                    itemName,
                    stoi(quantity),
                    stod(price)
                );
            }

            Order order(
                stoll(id),
                stoi(table),
                customer,
                date,
                status,
                items
            );

            orders.push_back(order);

            nextOrderId =
                max(
                    nextOrderId,
                    order.getId() + 1
                );
        }

        file.close();
    }

    // ========================================================
    // SAVE ORDERS
    // ========================================================

    void saveOrders()
    {
        ofstream file(ORDER_FILE);

        for (const auto& order : orders)
        {
            file << order.serialize()
                 << '\n';
        }

        file.close();
    }

    // ========================================================
    // DISPLAY MENU
    // ========================================================

    void displayMenu()
    {
        if (menu.empty())
        {
            cout << "\nMenu is empty.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================\n";
        cout << "                         RESTAURANT MENU\n";
        cout << "====================================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(28) << "Item"
             << setw(18) << "Category"
             << setw(12) << "Price"
             << "Status\n";

        cout << string(70, '-') << '\n';

        for (const auto& item : menu)
        {
            item.display();
        }

        cout << "====================================================================\n";
    }

    // ========================================================
    // ADD MENU ITEM
    // ========================================================

    void addMenuItem()
    {
        string name;
        string category;

        double price;

        clearInput();

        cout << "\n===============================================\n";
        cout << "               ADD MENU ITEM\n";
        cout << "===============================================\n";

        cout << "Item Name: ";
        getline(cin, name);

        cout << "Category: ";
        getline(cin, category);

        cout << "Price: Rs. ";
        cin >> price;

        if (name.empty() ||
            category.empty() ||
            price <= 0)
        {
            cout << "\nInvalid menu item details.\n";
            return;
        }

        MenuItem item(
            nextItemId,
            name,
            category,
            price,
            true
        );

        menu.push_back(item);

        saveMenu();

        cout << "\nMenu item added successfully!\n";

        cout << "Item ID: "
             << nextItemId
             << '\n';

        nextItemId++;
    }

    // ========================================================
    // CHANGE ITEM AVAILABILITY
    // ========================================================

    void updateMenuAvailability()
    {
        displayMenu();

        int id;

        cout << "\nEnter Item ID: ";
        cin >> id;

        MenuItem* item =
            findMenuItem(id);

        if (item == nullptr)
        {
            cout << "\nItem not found.\n";
            return;
        }

        cout << "\n1. Mark Available\n";
        cout << "2. Mark Unavailable\n";

        int choice;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            item->setAvailability(true);
        }
        else if (choice == 2)
        {
            item->setAvailability(false);
        }
        else
        {
            cout << "\nInvalid choice.\n";
            return;
        }

        saveMenu();

        cout << "\nMenu item updated successfully.\n";
    }

    // ========================================================
    // PLACE ORDER
    // ========================================================

    void placeOrder()
    {
        if (menu.empty())
        {
            cout << "\nMenu is empty.\n";
            return;
        }

        displayMenu();

        string customerName;

        int tableNumber;

        clearInput();

        cout << "\nCustomer Name: ";
        getline(cin, customerName);

        cout << "Table Number (0 for takeaway): ";
        cin >> tableNumber;

        if (tableNumber < 0 ||
            tableNumber > TOTAL_TABLES)
        {
            cout << "\nInvalid table number.\n";
            return;
        }

        vector<OrderItem> orderItems;

        while (true)
        {
            int itemId;

            cout << "\nEnter Item ID (0 to finish): ";
            cin >> itemId;

            if (itemId == 0)
                break;

            MenuItem* item =
                findMenuItem(itemId);

            if (item == nullptr)
            {
                cout << "\nItem not found.\n";
                continue;
            }

            if (!item->isAvailable())
            {
                cout << "\nThis item is currently unavailable.\n";
                continue;
            }

            int quantity;

            cout << "Quantity: ";
            cin >> quantity;

            if (quantity <= 0)
            {
                cout << "\nInvalid quantity.\n";
                continue;
            }

            orderItems.emplace_back(
                item->getId(),
                item->getName(),
                quantity,
                item->getPrice()
            );

            cout << "\nItem added to order.\n";
        }

        if (orderItems.empty())
        {
            cout << "\nNo items selected. Order cancelled.\n";
            return;
        }

        Order order(
            nextOrderId,
            tableNumber,
            customerName,
            getCurrentDate(),
            "Pending",
            orderItems
        );

        orders.push_back(order);

        saveOrders();

        cout << "\nOrder placed successfully!\n";

        cout << "Order ID: "
             << nextOrderId
             << '\n';

        order.printBill();

        nextOrderId++;
    }

    // ========================================================
    // UPDATE ORDER STATUS
    // ========================================================

    void updateOrderStatus()
    {
        long long id;

        cout << "\nEnter Order ID: ";
        cin >> id;

        Order* order =
            findOrder(id);

        if (order == nullptr)
        {
            cout << "\nOrder not found.\n";
            return;
        }

        cout << "\nCurrent Status: "
             << order->getStatus()
             << '\n';

        cout << "\n1. Pending\n";
        cout << "2. Preparing\n";
        cout << "3. Ready\n";
        cout << "4. Served\n";
        cout << "5. Cancelled\n";

        int choice;

        cout << "Select new status: ";
        cin >> choice;

        string status;

        switch (choice)
        {
            case 1:
                status = "Pending";
                break;

            case 2:
                status = "Preparing";
                break;

            case 3:
                status = "Ready";
                break;

            case 4:
                status = "Served";
                break;

            case 5:
                status = "Cancelled";
                break;

            default:
                cout << "\nInvalid choice.\n";
                return;
        }

        order->setStatus(status);

        saveOrders();

        cout << "\nOrder status updated successfully.\n";
    }

    // ========================================================
    // SEARCH ORDER
    // ========================================================

    void searchOrder()
    {
        long long id;

        cout << "\nEnter Order ID: ";
        cin >> id;

        Order* order =
            findOrder(id);

        if (order == nullptr)
        {
            cout << "\nOrder not found.\n";
            return;
        }

        order->printBill();
    }

    // ========================================================
    // GENERATE BILL
    // ========================================================

    void generateBill()
    {
        long long id;

        cout << "\nEnter Order ID: ";
        cin >> id;

        Order* order =
            findOrder(id);

        if (order == nullptr)
        {
            cout << "\nOrder not found.\n";
            return;
        }

        order->printBill();
    }

    // ========================================================
    // DISPLAY ALL ORDERS
    // ========================================================

    void displayAllOrders()
    {
        if (orders.empty())
        {
            cout << "\nNo orders available.\n";
            return;
        }

        cout << "\n";
        cout << "================================================================================================\n";
        cout << "                              ALL ORDERS\n";
        cout << "================================================================================================\n";

        cout << left
             << setw(14) << "Order ID"
             << setw(20) << "Customer"
             << setw(10) << "Table"
             << setw(15) << "Date"
             << setw(15) << "Status"
             << "Amount\n";

        cout << string(100, '-') << '\n';

        for (const auto& order : orders)
        {
            cout << left
                 << setw(14)
                 << order.getId()

                 << setw(20)
                 << order.getCustomerName()

                 << setw(10)
                 << order.getTableNumber()

                 << setw(15)
                 << order.getDate()

                 << setw(15)
                 << order.getStatus()

                 << "Rs. "
                 << fixed << setprecision(2)
                 << order.getTotal()

                 << '\n';
        }

        cout << "================================================================================================\n";
    }

    // ========================================================
    // TABLE RESERVATION
    // ========================================================

    bool isTableReserved(
        int table,
        string date,
        string time)
    {
        for (const auto& reservation :
             reservations)
        {
            if (
                reservation.getTableNumber() == table &&
                reservation.getDate() == date &&
                reservation.getTime() == time &&
                reservation.getStatus() != "Cancelled"
            )
            {
                return true;
            }
        }

        return false;
    }

    // ========================================================
    // MAKE RESERVATION
    // ========================================================

    void makeReservation()
    {
        string customer;
        string phone;
        string date;
        string time;

        int table;
        int guests;

        clearInput();

        cout << "\n===============================================\n";
        cout << "              TABLE RESERVATION\n";
        cout << "===============================================\n";

        cout << "Customer Name: ";
        getline(cin, customer);

        cout << "Phone Number: ";
        getline(cin, phone);

        cout << "Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Time (HH:MM): ";
        getline(cin, time);

        cout << "Table Number (1-20): ";
        cin >> table;

        if (table < 1 ||
            table > TOTAL_TABLES)
        {
            cout << "\nInvalid table number.\n";
            return;
        }

        if (isTableReserved(
            table,
            date,
            time))
        {
            cout << "\nThis table is already reserved "
                 << "for the selected time.\n";

            return;
        }

        cout << "Number of Guests: ";
        cin >> guests;

        if (guests <= 0)
        {
            cout << "\nInvalid number of guests.\n";
            return;
        }

        Reservation reservation(
            nextReservationId,
            customer,
            phone,
            table,
            date,
            time,
            guests,
            "Confirmed"
        );

        reservations.push_back(reservation);

        saveReservations();

        cout << "\nReservation confirmed!\n";

        cout << "Reservation ID: "
             << nextReservationId
             << '\n';

        nextReservationId++;
    }

    // ========================================================
    // DISPLAY RESERVATIONS
    // ========================================================

    void displayReservations()
    {
        if (reservations.empty())
        {
            cout << "\nNo reservations available.\n";
            return;
        }

        cout << "\n";
        cout << "================================================================================================\n";
        cout << "                              TABLE RESERVATIONS\n";
        cout << "================================================================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(22) << "Customer"
             << setw(15) << "Phone"
             << setw(10) << "Table"
             << setw(15) << "Date"
             << setw(10) << "Time"
             << setw(10) << "Guests"
             << "Status\n";

        cout << string(100, '-') << '\n';

        for (const auto& reservation :
             reservations)
        {
            reservation.display();
        }

        cout << "================================================================================================\n";
    }

    // ========================================================
    // DAILY SALES REPORT
    // ========================================================

    void dailySalesReport()
    {
        string today =
            getCurrentDate();

        double sales = 0;

        int completedOrders = 0;
        int cancelledOrders = 0;

        for (const auto& order : orders)
        {
            if (order.getDate() != today)
                continue;

            if (order.getStatus() == "Cancelled")
            {
                cancelledOrders++;
            }
            else
            {
                sales += order.getTotal();
                completedOrders++;
            }
        }

        cout << "\n";
        cout << "====================================================\n";
        cout << "                DAILY SALES REPORT\n";
        cout << "====================================================\n";

        cout << "Date               : "
             << today
             << '\n';

        cout << "Valid Orders       : "
             << completedOrders
             << '\n';

        cout << "Cancelled Orders   : "
             << cancelledOrders
             << '\n';

        cout << "Total Sales        : Rs. "
             << fixed << setprecision(2)
             << sales
             << '\n';

        cout << "====================================================\n";
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
        cout << "                 ADMIN LOGIN\n";
        cout << "===============================================\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (
            username == ADMIN_USERNAME &&
            password == ADMIN_PASSWORD
        )
        {
            cout << "\nLogin successful!\n";
            return true;
        }

        cout << "\nInvalid username or password.\n";

        return false;
    }

    // ========================================================
    // ADMIN PANEL
    // ========================================================

    void adminPanel()
    {
        if (!adminLogin())
            return;

        int choice;

        do
        {
            cout << "\n";
            cout << "====================================================\n";
            cout << "                ADMIN PANEL\n";
            cout << "====================================================\n";

            cout << "1. Add Menu Item\n";
            cout << "2. View Menu\n";
            cout << "3. Update Item Availability\n";
            cout << "4. View All Orders\n";
            cout << "5. Update Order Status\n";
            cout << "6. Daily Sales Report\n";
            cout << "7. View Reservations\n";
            cout << "8. Transaction / Order Search\n";
            cout << "9. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addMenuItem();
                    break;

                case 2:
                    displayMenu();
                    break;

                case 3:
                    updateMenuAvailability();
                    break;

                case 4:
                    displayAllOrders();
                    break;

                case 5:
                    updateOrderStatus();
                    break;

                case 6:
                    dailySalesReport();
                    break;

                case 7:
                    displayReservations();
                    break;

                case 8:
                    searchOrder();
                    break;

                case 9:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 9);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadMenu();
        loadOrders();
        loadReservations();

        int choice;

        do
        {
            cout << "\n\n";

            cout << "====================================================\n";
            cout << "          RESTAURANT ORDER MANAGEMENT SYSTEM\n";
            cout << "====================================================\n";

            cout << "1. View Menu\n";
            cout << "2. Place Order\n";
            cout << "3. Update Order Status\n";
            cout << "4. Generate Bill\n";
            cout << "5. Search Order\n";
            cout << "6. Make Table Reservation\n";
            cout << "7. View Reservations\n";
            cout << "8. Admin Panel\n";
            cout << "9. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayMenu();
                    break;

                case 2:
                    placeOrder();
                    break;

                case 3:
                    updateOrderStatus();
                    break;

                case 4:
                    generateBill();
                    break;

                case 5:
                    searchOrder();
                    break;

                case 6:
                    makeReservation();
                    break;

                case 7:
                    displayReservations();
                    break;

                case 8:
                    adminPanel();
                    break;

                case 9:

                    saveMenu();
                    saveOrders();
                    saveReservations();

                    cout << "\n";
                    cout << "====================================================\n";
                    cout << "     Thank you for visiting! Have a great day!\n";
                    cout << "====================================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }

        } while (choice != 9);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    RestaurantSystem system;

    system.run();

    return 0;
}