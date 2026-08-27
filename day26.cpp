#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

// ============================================================
// FILE NAMES
// ============================================================

const string CUSTOMER_FILE = "customers.txt";
const string PARCEL_FILE   = "parcels.txt";
const string HISTORY_FILE  = "history.txt";

// ============================================================
// ADMIN CREDENTIALS
// ============================================================

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "courier123";

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------------------------------------------------------
// Get current date
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

// ============================================================
// CUSTOMER CLASS
// ============================================================

class Customer
{
private:

    int customerId;
    string name;
    string phone;
    string email;
    string address;

public:

    Customer()
    {
        customerId = 0;
    }

    Customer(
        int id,
        const string& name,
        const string& phone,
        const string& email,
        const string& address)
        :
        customerId(id),
        name(name),
        phone(phone),
        email(email),
        address(address)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    int getId() const
    {
        return customerId;
    }

    string getName() const
    {
        return name;
    }

    string getPhone() const
    {
        return phone;
    }

    string getEmail() const
    {
        return email;
    }

    string getAddress() const
    {
        return address;
    }

    // --------------------------------------------------------
    // Display
    // --------------------------------------------------------

    void display() const
    {
        cout << left
             << setw(10) << customerId
             << setw(25) << name
             << setw(16) << phone
             << setw(28) << email
             << setw(30) << address
             << '\n';
    }

    // --------------------------------------------------------
    // File serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << customerId << "|"
           << name << "|"
           << phone << "|"
           << email << "|"
           << address;

        return ss.str();
    }
};

// ============================================================
// PARCEL CLASS
// ============================================================

class Parcel
{
private:

    long long trackingId;

    int senderId;
    int receiverId;

    string senderName;
    string receiverName;

    string source;
    string destination;

    double weight;

    string deliveryType;

    double deliveryCharge;

    string bookingDate;

    string status;

public:

    Parcel()
    {
        trackingId = 0;
        senderId = 0;
        receiverId = 0;
        weight = 0;
        deliveryCharge = 0;
        status = "Booked";
    }

    Parcel(
        long long trackingId,
        int senderId,
        int receiverId,
        const string& senderName,
        const string& receiverName,
        const string& source,
        const string& destination,
        double weight,
        const string& deliveryType,
        double deliveryCharge,
        const string& bookingDate,
        const string& status)
        :
        trackingId(trackingId),
        senderId(senderId),
        receiverId(receiverId),
        senderName(senderName),
        receiverName(receiverName),
        source(source),
        destination(destination),
        weight(weight),
        deliveryType(deliveryType),
        deliveryCharge(deliveryCharge),
        bookingDate(bookingDate),
        status(status)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    long long getTrackingId() const
    {
        return trackingId;
    }

    int getSenderId() const
    {
        return senderId;
    }

    int getReceiverId() const
    {
        return receiverId;
    }

    string getSenderName() const
    {
        return senderName;
    }

    string getReceiverName() const
    {
        return receiverName;
    }

    string getSource() const
    {
        return source;
    }

    string getDestination() const
    {
        return destination;
    }

    double getWeight() const
    {
        return weight;
    }

    string getDeliveryType() const
    {
        return deliveryType;
    }

    double getCharge() const
    {
        return deliveryCharge;
    }

    string getBookingDate() const
    {
        return bookingDate;
    }

    string getStatus() const
    {
        return status;
    }

    // --------------------------------------------------------
    // Setter
    // --------------------------------------------------------

    void setStatus(const string& newStatus)
    {
        status = newStatus;
    }

    // --------------------------------------------------------
    // Display
    // --------------------------------------------------------

    void display() const
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "             PARCEL DETAILS\n";
        cout << "============================================\n";

        cout << "Tracking ID     : " << trackingId << '\n';
        cout << "Sender ID       : " << senderId << '\n';
        cout << "Sender Name     : " << senderName << '\n';

        cout << "Receiver ID     : " << receiverId << '\n';
        cout << "Receiver Name   : " << receiverName << '\n';

        cout << "Source          : " << source << '\n';
        cout << "Destination     : " << destination << '\n';

        cout << "Weight          : "
             << fixed << setprecision(2)
             << weight << " kg\n";

        cout << "Delivery Type   : " << deliveryType << '\n';

        cout << "Delivery Charge : Rs. "
             << fixed << setprecision(2)
             << deliveryCharge << '\n';

        cout << "Booking Date    : " << bookingDate << '\n';

        cout << "Status          : " << status << '\n';

        cout << "============================================\n";
    }

    // --------------------------------------------------------
    // File serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << trackingId << "|"
           << senderId << "|"
           << receiverId << "|"
           << senderName << "|"
           << receiverName << "|"
           << source << "|"
           << destination << "|"
           << weight << "|"
           << deliveryType << "|"
           << deliveryCharge << "|"
           << bookingDate << "|"
           << status;

        return ss.str();
    }
};

// ============================================================
// DELIVERY HISTORY CLASS
// ============================================================

class DeliveryHistory
{
private:

    long long trackingId;
    string date;
    string status;
    string remarks;

public:

    DeliveryHistory()
    {
        trackingId = 0;
    }

    DeliveryHistory(
        long long trackingId,
        const string& date,
        const string& status,
        const string& remarks)
        :
        trackingId(trackingId),
        date(date),
        status(status),
        remarks(remarks)
    {
    }

    long long getTrackingId() const
    {
        return trackingId;
    }

    string getDate() const
    {
        return date;
    }

    string getStatus() const
    {
        return status;
    }

    string getRemarks() const
    {
        return remarks;
    }

    void display() const
    {
        cout << left
             << setw(16) << trackingId
             << setw(15) << date
             << setw(22) << status
             << setw(35) << remarks
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << trackingId << "|"
           << date << "|"
           << status << "|"
           << remarks;

        return ss.str();
    }
};

// ============================================================
// COURIER MANAGEMENT SYSTEM
// ============================================================

class CourierSystem
{
private:

    vector<Customer> customers;
    vector<Parcel> parcels;
    vector<DeliveryHistory> history;

    int nextCustomerId = 1001;
    long long nextTrackingId = 5000000001LL;

public:

    // ========================================================
    // FIND CUSTOMER
    // ========================================================

    Customer* findCustomer(int id)
    {
        for (auto& customer : customers)
        {
            if (customer.getId() == id)
                return &customer;
        }

        return nullptr;
    }

    // ========================================================
    // FIND PARCEL
    // ========================================================

    Parcel* findParcel(long long trackingId)
    {
        for (auto& parcel : parcels)
        {
            if (parcel.getTrackingId() == trackingId)
                return &parcel;
        }

        return nullptr;
    }

    // ========================================================
    // FILE HANDLING - CUSTOMERS
    // ========================================================

    void loadCustomers()
    {
        ifstream file(CUSTOMER_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string phone;
            string email;
            string address;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, email, '|');
            getline(ss, address, '|');

            Customer customer(
                stoi(idStr),
                name,
                phone,
                email,
                address
            );

            customers.push_back(customer);

            if (customer.getId() >= nextCustomerId)
            {
                nextCustomerId =
                    customer.getId() + 1;
            }
        }

        file.close();
    }

    // ========================================================
    // SAVE CUSTOMERS
    // ========================================================

    void saveCustomers()
    {
        ofstream file(CUSTOMER_FILE);

        for (const auto& customer : customers)
        {
            file << customer.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // FILE HANDLING - PARCELS
    // ========================================================

    void loadParcels()
    {
        ifstream file(PARCEL_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string trackingIdStr;
            string senderIdStr;
            string receiverIdStr;
            string senderName;
            string receiverName;
            string source;
            string destination;
            string weightStr;
            string deliveryType;
            string chargeStr;
            string bookingDate;
            string status;

            getline(ss, trackingIdStr, '|');
            getline(ss, senderIdStr, '|');
            getline(ss, receiverIdStr, '|');
            getline(ss, senderName, '|');
            getline(ss, receiverName, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, weightStr, '|');
            getline(ss, deliveryType, '|');
            getline(ss, chargeStr, '|');
            getline(ss, bookingDate, '|');
            getline(ss, status, '|');

            Parcel parcel(
                stoll(trackingIdStr),
                stoi(senderIdStr),
                stoi(receiverIdStr),
                senderName,
                receiverName,
                source,
                destination,
                stod(weightStr),
                deliveryType,
                stod(chargeStr),
                bookingDate,
                status
            );

            parcels.push_back(parcel);

            if (parcel.getTrackingId() >= nextTrackingId)
            {
                nextTrackingId =
                    parcel.getTrackingId() + 1;
            }
        }

        file.close();
    }

    // ========================================================
    // SAVE PARCELS
    // ========================================================

    void saveParcels()
    {
        ofstream file(PARCEL_FILE);

        for (const auto& parcel : parcels)
        {
            file << parcel.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD HISTORY
    // ========================================================

    void loadHistory()
    {
        ifstream file(HISTORY_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string trackingIdStr;
            string date;
            string status;
            string remarks;

            getline(ss, trackingIdStr, '|');
            getline(ss, date, '|');
            getline(ss, status, '|');
            getline(ss, remarks, '|');

            history.emplace_back(
                stoll(trackingIdStr),
                date,
                status,
                remarks
            );
        }

        file.close();
    }

    // ========================================================
    // SAVE HISTORY
    // ========================================================

    void saveHistory()
    {
        ofstream file(HISTORY_FILE);

        for (const auto& record : history)
        {
            file << record.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // ADD HISTORY RECORD
    // ========================================================

    void addHistory(
        long long trackingId,
        const string& status,
        const string& remarks)
    {
        history.emplace_back(
            trackingId,
            getCurrentDate(),
            status,
            remarks
        );

        saveHistory();
    }

    // ========================================================
    // REGISTER CUSTOMER
    // ========================================================

    void registerCustomer()
    {
        string name;
        string phone;
        string email;
        string address;

        clearInput();

        cout << "\n============================================\n";
        cout << "             CUSTOMER REGISTRATION\n";
        cout << "============================================\n";

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Email: ";
        getline(cin, email);

        cout << "Enter Address: ";
        getline(cin, address);

        if (name.empty() || phone.empty())
        {
            cout << "\nInvalid customer details.\n";
            return;
        }

        Customer customer(
            nextCustomerId,
            name,
            phone,
            email,
            address
        );

        customers.push_back(customer);

        saveCustomers();

        cout << "\nCustomer registered successfully!\n";
        cout << "Customer ID: "
             << nextCustomerId
             << '\n';

        nextCustomerId++;
    }

    // ========================================================
    // DISPLAY CUSTOMERS
    // ========================================================

    void displayCustomers()
    {
        if (customers.empty())
        {
            cout << "\nNo customers registered.\n";
            return;
        }

        cout << "\n";
        cout << "=======================================================================================\n";
        cout << "                              CUSTOMER LIST\n";
        cout << "=======================================================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(16) << "Phone"
             << setw(28) << "Email"
             << setw(30) << "Address"
             << '\n';

        cout << string(109, '-') << '\n';

        for (const auto& customer : customers)
        {
            customer.display();
        }

        cout << "=======================================================================================\n";
    }

    // ========================================================
    // CALCULATE DELIVERY CHARGE
    // ========================================================

    double calculateDeliveryCharge(
        double weight,
        const string& deliveryType)
    {
        /*
            Normal:
            Base charge = Rs. 50
            First 1 kg = Rs. 50
            Every additional kg = Rs. 30

            Express:
            2x normal charge
        */

        double charge = 50.0;

        if (weight > 1.0)
        {
            charge +=
                (weight - 1.0) * 30.0;
        }

        if (deliveryType == "Express")
        {
            charge *= 2.0;
        }

        return charge;
    }

    // ========================================================
    // BOOK PARCEL
    // ========================================================

    void bookParcel()
    {
        int senderId;
        int receiverId;

        string receiverName;
        string source;
        string destination;

        double weight;

        int deliveryChoice;

        cout << "\n============================================\n";
        cout << "               BOOK PARCEL\n";
        cout << "============================================\n";

        cout << "Enter Sender Customer ID: ";
        cin >> senderId;

        Customer* sender =
            findCustomer(senderId);

        if (sender == nullptr)
        {
            cout << "\nSender not found.\n";
            cout << "Please register the customer first.\n";
            return;
        }

        cout << "Enter Receiver Customer ID: ";
        cin >> receiverId;

        Customer* receiver =
            findCustomer(receiverId);

        if (receiver == nullptr)
        {
            cout << "\nReceiver not found.\n";
            return;
        }

        clearInput();

        cout << "Enter Receiver Name: ";
        getline(cin, receiverName);

        cout << "Enter Source City: ";
        getline(cin, source);

        cout << "Enter Destination City: ";
        getline(cin, destination);

        cout << "Enter Parcel Weight (kg): ";
        cin >> weight;

        if (weight <= 0)
        {
            cout << "\nInvalid weight.\n";
            return;
        }

        cout << "\nDelivery Type:\n";
        cout << "1. Normal Delivery\n";
        cout << "2. Express Delivery\n";

        cout << "Enter choice: ";
        cin >> deliveryChoice;

        string deliveryType;

        if (deliveryChoice == 1)
        {
            deliveryType = "Normal";
        }
        else if (deliveryChoice == 2)
        {
            deliveryType = "Express";
        }
        else
        {
            cout << "\nInvalid delivery type.\n";
            return;
        }

        double charge =
            calculateDeliveryCharge(
                weight,
                deliveryType
            );

        Parcel parcel(
            nextTrackingId,
            senderId,
            receiverId,
            sender->getName(),
            receiverName,
            source,
            destination,
            weight,
            deliveryType,
            charge,
            getCurrentDate(),
            "Booked"
        );

        parcels.push_back(parcel);

        saveParcels();

        addHistory(
            nextTrackingId,
            "Booked",
            "Parcel successfully booked"
        );

        cout << "\n============================================\n";
        cout << "          PARCEL BOOKED SUCCESSFULLY\n";
        cout << "============================================\n";

        cout << "Tracking ID     : "
             << nextTrackingId
             << '\n';

        cout << "Sender          : "
             << sender->getName()
             << '\n';

        cout << "Receiver        : "
             << receiverName
             << '\n';

        cout << "Delivery Type   : "
             << deliveryType
             << '\n';

        cout << "Weight          : "
             << fixed << setprecision(2)
             << weight
             << " kg\n";

        cout << "Delivery Charge : Rs. "
             << fixed << setprecision(2)
             << charge
             << '\n';

        cout << "Status          : Booked\n";

        cout << "============================================\n";

        nextTrackingId++;
    }

    // ========================================================
    // TRACK SHIPMENT
    // ========================================================

    void trackShipment()
    {
        long long trackingId;

        cout << "\nEnter Tracking ID: ";
        cin >> trackingId;

        Parcel* parcel =
            findParcel(trackingId);

        if (parcel == nullptr)
        {
            cout << "\nParcel not found.\n";
            return;
        }

        parcel->display();

        cout << "\nDelivery History:\n";

        cout << string(85, '-') << '\n';

        cout << left
             << setw(16) << "Tracking ID"
             << setw(15) << "Date"
             << setw(22) << "Status"
             << setw(35) << "Remarks"
             << '\n';

        cout << string(85, '-') << '\n';

        bool found = false;

        for (const auto& record : history)
        {
            if (record.getTrackingId() ==
                trackingId)
            {
                record.display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No history available.\n";
        }

        cout << string(85, '-') << '\n';
    }

    // ========================================================
    // UPDATE DELIVERY STATUS
    // ========================================================

    void updateDeliveryStatus()
    {
        long long trackingId;

        cout << "\nEnter Tracking ID: ";
        cin >> trackingId;

        Parcel* parcel =
            findParcel(trackingId);

        if (parcel == nullptr)
        {
            cout << "\nParcel not found.\n";
            return;
        }

        cout << "\nCurrent Status: "
             << parcel->getStatus()
             << '\n';

        cout << "\nSelect New Status:\n";

        cout << "1. Booked\n";
        cout << "2. Picked Up\n";
        cout << "3. In Transit\n";
        cout << "4. Out for Delivery\n";
        cout << "5. Delivered\n";
        cout << "6. Delivery Failed\n";
        cout << "7. Cancelled\n";

        int choice;

        cout << "\nEnter choice: ";
        cin >> choice;

        string newStatus;

        switch (choice)
        {
            case 1:
                newStatus = "Booked";
                break;

            case 2:
                newStatus = "Picked Up";
                break;

            case 3:
                newStatus = "In Transit";
                break;

            case 4:
                newStatus = "Out for Delivery";
                break;

            case 5:
                newStatus = "Delivered";
                break;

            case 6:
                newStatus = "Delivery Failed";
                break;

            case 7:
                newStatus = "Cancelled";
                break;

            default:
                cout << "\nInvalid choice.\n";
                return;
        }

        clearInput();

        string remarks;

        cout << "Enter remarks: ";
        getline(cin, remarks);

        parcel->setStatus(newStatus);

        saveParcels();

        addHistory(
            trackingId,
            newStatus,
            remarks
        );

        cout << "\nDelivery status updated successfully!\n";
    }

    // ========================================================
    // SEARCH PARCEL BY TRACKING ID
    // ========================================================

    void searchParcel()
    {
        long long trackingId;

        cout << "\nEnter Tracking ID: ";
        cin >> trackingId;

        Parcel* parcel =
            findParcel(trackingId);

        if (parcel == nullptr)
        {
            cout << "\nNo parcel found for Tracking ID "
                 << trackingId
                 << ".\n";

            return;
        }

        parcel->display();
    }

    // ========================================================
    // DISPLAY DELIVERY HISTORY
    // ========================================================

    void displayHistory()
    {
        if (history.empty())
        {
            cout << "\nNo delivery history available.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================================\n";
        cout << "                         DELIVERY HISTORY\n";
        cout << "====================================================================================\n";

        cout << left
             << setw(16) << "Tracking ID"
             << setw(15) << "Date"
             << setw(22) << "Status"
             << setw(35) << "Remarks"
             << '\n';

        cout << string(88, '-') << '\n';

        for (const auto& record : history)
        {
            record.display();
        }

        cout << "====================================================================================\n";
    }

    // ========================================================
    // DISPLAY ALL PARCELS
    // ========================================================

    void displayAllParcels()
    {
        if (parcels.empty())
        {
            cout << "\nNo parcels available.\n";
            return;
        }

        cout << "\n";
        cout << "========================================================================================================\n";
        cout << "                                  ALL PARCELS\n";
        cout << "========================================================================================================\n";

        cout << left
             << setw(16) << "Tracking ID"
             << setw(20) << "Sender"
             << setw(20) << "Receiver"
             << setw(18) << "Destination"
             << setw(12) << "Weight"
             << setw(15) << "Type"
             << setw(20) << "Status"
             << '\n';

        cout << string(121, '-') << '\n';

        for (const auto& parcel : parcels)
        {
            cout << left
                 << setw(16)
                 << parcel.getTrackingId()

                 << setw(20)
                 << parcel.getSenderName()

                 << setw(20)
                 << parcel.getReceiverName()

                 << setw(18)
                 << parcel.getDestination()

                 << setw(12)
                 << fixed << setprecision(2)
                 << parcel.getWeight()

                 << setw(15)
                 << parcel.getDeliveryType()

                 << setw(20)
                 << parcel.getStatus()

                 << '\n';
        }

        cout << "========================================================================================================\n";
    }

    // ========================================================
    // ADMIN LOGIN
    // ========================================================

    bool adminLogin()
    {
        string username;
        string password;

        clearInput();

        cout << "\n============================================\n";
        cout << "                ADMIN LOGIN\n";
        cout << "============================================\n";

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
            cout << "\n============================================\n";
            cout << "            COURIER ADMIN DASHBOARD\n";
            cout << "============================================\n";

            cout << "1. Display Customers\n";
            cout << "2. Display All Parcels\n";
            cout << "3. Update Delivery Status\n";
            cout << "4. Search Parcel\n";
            cout << "5. Delivery History\n";
            cout << "6. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayCustomers();
                    break;

                case 2:
                    displayAllParcels();
                    break;

                case 3:
                    updateDeliveryStatus();
                    break;

                case 4:
                    searchParcel();
                    break;

                case 5:
                    displayHistory();
                    break;

                case 6:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 6);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        // Load saved data
        loadCustomers();
        loadParcels();
        loadHistory();

        int choice;

        do
        {
            cout << "\n\n";

            cout << "================================================\n";
            cout << "         COURIER & PARCEL TRACKING SYSTEM\n";
            cout << "================================================\n";

            cout << "1. Register Customer\n";
            cout << "2. Display Customers\n";
            cout << "3. Book Parcel\n";
            cout << "4. Track Shipment\n";
            cout << "5. Update Delivery Status\n";
            cout << "6. Search Parcel by Tracking ID\n";
            cout << "7. Delivery History\n";
            cout << "8. Calculate Delivery Charges\n";
            cout << "9. Admin Dashboard\n";
            cout << "10. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    registerCustomer();
                    break;

                case 2:
                    displayCustomers();
                    break;

                case 3:
                    bookParcel();
                    break;

                case 4:
                    trackShipment();
                    break;

                case 5:
                    updateDeliveryStatus();
                    break;

                case 6:
                    searchParcel();
                    break;

                case 7:
                    displayHistory();
                    break;

                case 8:
                {
                    double weight;
                    int choice;

                    cout << "\nEnter parcel weight (kg): ";
                    cin >> weight;

                    cout << "\n1. Normal Delivery\n";
                    cout << "2. Express Delivery\n";

                    cout << "Enter choice: ";
                    cin >> choice;

                    if (weight <= 0 ||
                        (choice != 1 && choice != 2))
                    {
                        cout << "\nInvalid input.\n";
                        break;
                    }

                    string type =
                        (choice == 1)
                        ? "Normal"
                        : "Express";

                    double charge =
                        calculateDeliveryCharge(
                            weight,
                            type
                        );

                    cout << "\n============================================\n";
                    cout << "        DELIVERY CHARGE CALCULATOR\n";
                    cout << "============================================\n";

                    cout << "Weight        : "
                         << fixed << setprecision(2)
                         << weight
                         << " kg\n";

                    cout << "Delivery Type : "
                         << type
                         << '\n';

                    cout << "Charge        : Rs. "
                         << fixed << setprecision(2)
                         << charge
                         << '\n';

                    cout << "============================================\n";

                    break;
                }

                case 9:
                    adminDashboard();
                    break;

                case 10:

                    // Save everything before exiting
                    saveCustomers();
                    saveParcels();
                    saveHistory();

                    cout << "\n============================================\n";
                    cout << " Thank you for using Courier Tracking System!\n";
                    cout << "============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 10);
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    CourierSystem system;

    system.run();

    return 0;
}