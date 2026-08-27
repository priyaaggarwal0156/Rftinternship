#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>
#include <cctype>

using namespace std;

// ============================================================
// FILES
// ============================================================

const string TRAIN_FILE = "trains.txt";
const string PASSENGER_FILE = "passengers.txt";
const string TICKET_FILE = "tickets.txt";

// ============================================================
// CONSTANTS
// ============================================================

const int MAX_WAITING_LIST = 10;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "railway123";

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Generate current date
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
// TRAIN CLASS
// ============================================================

class Train
{
private:

    int trainNumber;
    string trainName;
    string source;
    string destination;

    int totalSeats;
    int availableSeats;

    double farePerSeat;

public:

    Train()
    {
        trainNumber = 0;
        totalSeats = 0;
        availableSeats = 0;
        farePerSeat = 0;
    }

    Train(
        int trainNumber,
        const string& trainName,
        const string& source,
        const string& destination,
        int totalSeats,
        double farePerSeat)
        :
        trainNumber(trainNumber),
        trainName(trainName),
        source(source),
        destination(destination),
        totalSeats(totalSeats),
        availableSeats(totalSeats),
        farePerSeat(farePerSeat)
    {
    }

    // ========================================================
    // GETTERS
    // ========================================================

    int getTrainNumber() const
    {
        return trainNumber;
    }

    string getTrainName() const
    {
        return trainName;
    }

    string getSource() const
    {
        return source;
    }

    string getDestination() const
    {
        return destination;
    }

    int getTotalSeats() const
    {
        return totalSeats;
    }

    int getAvailableSeats() const
    {
        return availableSeats;
    }

    double getFare() const
    {
        return farePerSeat;
    }

    // ========================================================
    // SEAT OPERATIONS
    // ========================================================

    bool bookSeat()
    {
        if (availableSeats <= 0)
            return false;

        availableSeats--;
        return true;
    }

    void cancelSeat()
    {
        if (availableSeats < totalSeats)
            availableSeats++;
    }

    // ========================================================
    // DISPLAY
    // ========================================================

    void display() const
    {
        cout << left
             << setw(10) << trainNumber
             << setw(25) << trainName
             << setw(20) << source
             << setw(20) << destination
             << setw(12) << totalSeats
             << setw(15) << availableSeats
             << setw(12)
             << fixed << setprecision(2)
             << farePerSeat
             << '\n';
    }

    // ========================================================
    // FILE SERIALIZATION
    // ========================================================

    string serialize() const
    {
        stringstream ss;

        ss << trainNumber << "|"
           << trainName << "|"
           << source << "|"
           << destination << "|"
           << totalSeats << "|"
           << availableSeats << "|"
           << farePerSeat;

        return ss.str();
    }
};

// ============================================================
// PASSENGER CLASS
// ============================================================

class Passenger
{
private:

    int passengerId;
    string name;
    int age;
    string gender;
    string phone;

public:

    Passenger()
    {
        passengerId = 0;
        age = 0;
    }

    Passenger(
        int passengerId,
        const string& name,
        int age,
        const string& gender,
        const string& phone)
        :
        passengerId(passengerId),
        name(name),
        age(age),
        gender(gender),
        phone(phone)
    {
    }

    int getPassengerId() const
    {
        return passengerId;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    string getGender() const
    {
        return gender;
    }

    string getPhone() const
    {
        return phone;
    }

    void display() const
    {
        cout << left
             << setw(10) << passengerId
             << setw(25) << name
             << setw(8) << age
             << setw(12) << gender
             << setw(18) << phone
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << passengerId << "|"
           << name << "|"
           << age << "|"
           << gender << "|"
           << phone;

        return ss.str();
    }
};

// ============================================================
// TICKET CLASS
// ============================================================

class Ticket
{
private:

    long long pnr;

    int passengerId;
    int trainNumber;

    string passengerName;

    int seatNumber;

    double fare;

    string bookingDate;

    string status;

    // Status:
    // CONFIRMED
    // WAITING
    // CANCELLED

public:

    Ticket()
    {
        pnr = 0;
        passengerId = 0;
        trainNumber = 0;
        seatNumber = -1;
        fare = 0;
        status = "WAITING";
    }

    Ticket(
        long long pnr,
        int passengerId,
        int trainNumber,
        const string& passengerName,
        int seatNumber,
        double fare,
        const string& bookingDate,
        const string& status)
        :
        pnr(pnr),
        passengerId(passengerId),
        trainNumber(trainNumber),
        passengerName(passengerName),
        seatNumber(seatNumber),
        fare(fare),
        bookingDate(bookingDate),
        status(status)
    {
    }

    // ========================================================
    // GETTERS
    // ========================================================

    long long getPNR() const
    {
        return pnr;
    }

    int getPassengerId() const
    {
        return passengerId;
    }

    int getTrainNumber() const
    {
        return trainNumber;
    }

    string getPassengerName() const
    {
        return passengerName;
    }

    int getSeatNumber() const
    {
        return seatNumber;
    }

    double getFare() const
    {
        return fare;
    }

    string getStatus() const
    {
        return status;
    }

    string getBookingDate() const
    {
        return bookingDate;
    }

    void setSeatNumber(int seat)
    {
        seatNumber = seat;
    }

    void setStatus(const string& newStatus)
    {
        status = newStatus;
    }

    void setFare(double newFare)
    {
        fare = newFare;
    }

    // ========================================================
    // DISPLAY
    // ========================================================

    void display() const
    {
        cout << "\n============================================\n";
        cout << "                 TICKET\n";
        cout << "============================================\n";

        cout << "PNR            : " << pnr << '\n';
        cout << "Passenger ID   : " << passengerId << '\n';
        cout << "Passenger Name : " << passengerName << '\n';
        cout << "Train Number   : " << trainNumber << '\n';

        if (seatNumber == -1)
            cout << "Seat Number    : Waiting List\n";
        else
            cout << "Seat Number    : " << seatNumber << '\n';

        cout << "Fare           : Rs. "
             << fixed << setprecision(2)
             << fare << '\n';

        cout << "Booking Date   : " << bookingDate << '\n';
        cout << "Status         : " << status << '\n';

        cout << "============================================\n";
    }

    // ========================================================
    // FILE SERIALIZATION
    // ========================================================

    string serialize() const
    {
        stringstream ss;

        ss << pnr << "|"
           << passengerId << "|"
           << trainNumber << "|"
           << passengerName << "|"
           << seatNumber << "|"
           << fare << "|"
           << bookingDate << "|"
           << status;

        return ss.str();
    }
};

// ============================================================
// WAITING LIST ENTRY
// ============================================================

struct WaitingPassenger
{
    long long pnr;
    int passengerId;
    int trainNumber;
};

// ============================================================
// RAILWAY RESERVATION SYSTEM
// ============================================================

class RailwaySystem
{
private:

    vector<Train> trains;
    vector<Passenger> passengers;
    vector<Ticket> tickets;

    // Waiting lists are maintained separately for each train
    vector<WaitingPassenger> waitingList;

    long long nextPNR = 1000000001;
    int nextPassengerId = 1001;

public:

    // ========================================================
    // FIND TRAIN
    // ========================================================

    Train* findTrain(int trainNumber)
    {
        for (auto& train : trains)
        {
            if (train.getTrainNumber() == trainNumber)
                return &train;
        }

        return nullptr;
    }

    // ========================================================
    // FIND PASSENGER
    // ========================================================

    Passenger* findPassenger(int passengerId)
    {
        for (auto& passenger : passengers)
        {
            if (passenger.getPassengerId() == passengerId)
                return &passenger;
        }

        return nullptr;
    }

    // ========================================================
    // FIND TICKET
    // ========================================================

    Ticket* findTicket(long long pnr)
    {
        for (auto& ticket : tickets)
        {
            if (ticket.getPNR() == pnr)
                return &ticket;
        }

        return nullptr;
    }

    // ========================================================
    // FILE HANDLING - TRAINS
    // ========================================================

    void loadTrains()
    {
        ifstream file(TRAIN_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string numberStr;
            string name;
            string source;
            string destination;
            string totalSeatsStr;
            string availableSeatsStr;
            string fareStr;

            getline(ss, numberStr, '|');
            getline(ss, name, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, totalSeatsStr, '|');
            getline(ss, availableSeatsStr, '|');
            getline(ss, fareStr, '|');

            Train train(
                stoi(numberStr),
                name,
                source,
                destination,
                stoi(totalSeatsStr),
                stod(fareStr)
            );

            int booked =
                stoi(totalSeatsStr) -
                stoi(availableSeatsStr);

            for (int i = 0; i < booked; i++)
                train.bookSeat();

            trains.push_back(train);
        }

        file.close();
    }

    // ========================================================
    // SAVE TRAINS
    // ========================================================

    void saveTrains()
    {
        ofstream file(TRAIN_FILE);

        for (const auto& train : trains)
        {
            file << train.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD PASSENGERS
    // ========================================================

    void loadPassengers()
    {
        ifstream file(PASSENGER_FILE);

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
            string ageStr;
            string gender;
            string phone;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, ageStr, '|');
            getline(ss, gender, '|');
            getline(ss, phone, '|');

            Passenger passenger(
                stoi(idStr),
                name,
                stoi(ageStr),
                gender,
                phone
            );

            passengers.push_back(passenger);

            if (passenger.getPassengerId() >= nextPassengerId)
            {
                nextPassengerId =
                    passenger.getPassengerId() + 1;
            }
        }

        file.close();
    }

    // ========================================================
    // SAVE PASSENGERS
    // ========================================================

    void savePassengers()
    {
        ofstream file(PASSENGER_FILE);

        for (const auto& passenger : passengers)
        {
            file << passenger.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD TICKETS
    // ========================================================

    void loadTickets()
    {
        ifstream file(TICKET_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string pnrStr;
            string passengerIdStr;
            string trainNumberStr;
            string passengerName;
            string seatNumberStr;
            string fareStr;
            string bookingDate;
            string status;

            getline(ss, pnrStr, '|');
            getline(ss, passengerIdStr, '|');
            getline(ss, trainNumberStr, '|');
            getline(ss, passengerName, '|');
            getline(ss, seatNumberStr, '|');
            getline(ss, fareStr, '|');
            getline(ss, bookingDate, '|');
            getline(ss, status, '|');

            Ticket ticket(
                stoll(pnrStr),
                stoi(passengerIdStr),
                stoi(trainNumberStr),
                passengerName,
                stoi(seatNumberStr),
                stod(fareStr),
                bookingDate,
                status
            );

            tickets.push_back(ticket);

            if (ticket.getPNR() >= nextPNR)
                nextPNR = ticket.getPNR() + 1;
        }

        file.close();

        // Rebuild waiting list
        for (const auto& ticket : tickets)
        {
            if (ticket.getStatus() == "WAITING")
            {
                waitingList.push_back(
                    {
                        ticket.getPNR(),
                        ticket.getPassengerId(),
                        ticket.getTrainNumber()
                    }
                );
            }
        }
    }

    // ========================================================
    // SAVE TICKETS
    // ========================================================

    void saveTickets()
    {
        ofstream file(TICKET_FILE);

        for (const auto& ticket : tickets)
        {
            file << ticket.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // ADD TRAIN
    // ========================================================

    void addTrain()
    {
        int trainNumber;
        string trainName;
        string source;
        string destination;
        int totalSeats;
        double fare;

        clearInput();

        cout << "\n============================================\n";
        cout << "              ADD TRAIN DETAILS\n";
        cout << "============================================\n";

        cout << "Enter Train Number: ";
        cin >> trainNumber;

        if (findTrain(trainNumber) != nullptr)
        {
            cout << "Train number already exists.\n";
            return;
        }

        clearInput();

        cout << "Enter Train Name: ";
        getline(cin, trainName);

        cout << "Enter Source: ";
        getline(cin, source);

        cout << "Enter Destination: ";
        getline(cin, destination);

        cout << "Enter Total Seats: ";
        cin >> totalSeats;

        cout << "Enter Fare Per Seat: Rs. ";
        cin >> fare;

        if (totalSeats <= 0 || fare < 0)
        {
            cout << "Invalid train details.\n";
            return;
        }

        trains.emplace_back(
            trainNumber,
            trainName,
            source,
            destination,
            totalSeats,
            fare
        );

        saveTrains();

        cout << "\nTrain added successfully!\n";
    }

    // ========================================================
    // DISPLAY TRAINS
    // ========================================================

    void displayTrains()
    {
        if (trains.empty())
        {
            cout << "\nNo trains available.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================================\n";
        cout << "                              TRAIN DETAILS\n";
        cout << "====================================================================================\n";

        cout << left
             << setw(10) << "Number"
             << setw(25) << "Train Name"
             << setw(20) << "Source"
             << setw(20) << "Destination"
             << setw(12) << "Total"
             << setw(15) << "Available"
             << setw(12) << "Fare"
             << '\n';

        cout << string(114, '-') << '\n';

        for (const auto& train : trains)
        {
            train.display();
        }

        cout << "====================================================================================\n";
    }

    // ========================================================
    // REGISTER PASSENGER
    // ========================================================

    void registerPassenger()
    {
        string name;
        int age;
        string gender;
        string phone;

        clearInput();

        cout << "\n============================================\n";
        cout << "            PASSENGER REGISTRATION\n";
        cout << "============================================\n";

        cout << "Enter Passenger Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        clearInput();

        cout << "Enter Gender: ";
        getline(cin, gender);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        if (name.empty() || age <= 0)
        {
            cout << "Invalid passenger details.\n";
            return;
        }

        Passenger passenger(
            nextPassengerId,
            name,
            age,
            gender,
            phone
        );

        passengers.push_back(passenger);

        savePassengers();

        cout << "\nPassenger registered successfully!\n";

        cout << "Passenger ID: "
             << nextPassengerId
             << '\n';

        nextPassengerId++;
    }

    // ========================================================
    // FARE CALCULATION
    // ========================================================

    double calculateFare(
        const Train& train,
        int numberOfPassengers)
    {
        return train.getFare() *
               numberOfPassengers;
    }

    // ========================================================
    // SEAT AVAILABILITY
    // ========================================================

    void checkSeatAvailability()
    {
        int trainNumber;

        cout << "\nEnter Train Number: ";
        cin >> trainNumber;

        Train* train =
            findTrain(trainNumber);

        if (train == nullptr)
        {
            cout << "Train not found.\n";
            return;
        }

        cout << "\n============================================\n";
        cout << "           SEAT AVAILABILITY\n";
        cout << "============================================\n";

        cout << "Train Number    : "
             << train->getTrainNumber()
             << '\n';

        cout << "Train Name      : "
             << train->getTrainName()
             << '\n';

        cout << "Total Seats     : "
             << train->getTotalSeats()
             << '\n';

        cout << "Available Seats : "
             << train->getAvailableSeats()
             << '\n';

        cout << "Waiting List    : "
             << countWaitingPassengers(trainNumber)
             << '\n';

        cout << "Fare Per Seat   : Rs. "
             << fixed << setprecision(2)
             << train->getFare()
             << '\n';

        cout << "============================================\n";
    }

    // ========================================================
    // COUNT WAITING PASSENGERS
    // ========================================================

    int countWaitingPassengers(int trainNumber)
    {
        int count = 0;

        for (const auto& ticket : tickets)
        {
            if (ticket.getTrainNumber() == trainNumber &&
                ticket.getStatus() == "WAITING")
            {
                count++;
            }
        }

        return count;
    }

    // ========================================================
    // BOOK TICKET
    // ========================================================

    void bookTicket()
    {
        int passengerId;
        int trainNumber;

        cout << "\nEnter Passenger ID: ";
        cin >> passengerId;

        Passenger* passenger =
            findPassenger(passengerId);

        if (passenger == nullptr)
        {
            cout << "Passenger not found.\n";
            cout << "Please register the passenger first.\n";
            return;
        }

        displayTrains();

        cout << "\nEnter Train Number: ";
        cin >> trainNumber;

        Train* train =
            findTrain(trainNumber);

        if (train == nullptr)
        {
            cout << "Train not found.\n";
            return;
        }

        // ----------------------------------------------------
        // Confirmed ticket
        // ----------------------------------------------------

        if (train->getAvailableSeats() > 0)
        {
            int seatNumber =
                train->getTotalSeats() -
                train->getAvailableSeats() +
                1;

            train->bookSeat();

            double fare =
                calculateFare(*train, 1);

            Ticket ticket(
                nextPNR,
                passengerId,
                trainNumber,
                passenger->getName(),
                seatNumber,
                fare,
                getCurrentDate(),
                "CONFIRMED"
            );

            tickets.push_back(ticket);

            saveTickets();
            saveTrains();

            cout << "\n============================================\n";
            cout << "          TICKET BOOKED SUCCESSFULLY\n";
            cout << "============================================\n";

            cout << "PNR        : "
                 << nextPNR << '\n';

            cout << "Seat Number: "
                 << seatNumber << '\n';

            cout << "Fare       : Rs. "
                 << fixed << setprecision(2)
                 << fare << '\n';

            cout << "Status     : CONFIRMED\n";

            cout << "============================================\n";

            nextPNR++;
        }

        // ----------------------------------------------------
        // Waiting List
        // ----------------------------------------------------

        else
        {
            int waitingCount =
                countWaitingPassengers(trainNumber);

            if (waitingCount >= MAX_WAITING_LIST)
            {
                cout << "\nWaiting list is full.\n";
                return;
            }

            double fare =
                calculateFare(*train, 1);

            Ticket ticket(
                nextPNR,
                passengerId,
                trainNumber,
                passenger->getName(),
                -1,
                fare,
                getCurrentDate(),
                "WAITING"
            );

            tickets.push_back(ticket);

            waitingList.push_back(
                {
                    nextPNR,
                    passengerId,
                    trainNumber
                }
            );

            saveTickets();

            cout << "\n============================================\n";
            cout << "          ADDED TO WAITING LIST\n";
            cout << "============================================\n";

            cout << "PNR    : "
                 << nextPNR << '\n';

            cout << "Status : WAITING\n";

            cout << "Waiting Position: "
                 << waitingCount + 1
                 << '\n';

            cout << "============================================\n";

            nextPNR++;
        }
    }

    // ========================================================
    // PROMOTE WAITING PASSENGER
    // ========================================================

    void promoteWaitingPassenger(
        int trainNumber,
        int freedSeat)
    {
        for (size_t i = 0;
             i < tickets.size();
             i++)
        {
            Ticket& ticket = tickets[i];

            if (ticket.getTrainNumber() == trainNumber &&
                ticket.getStatus() == "WAITING")
            {
                ticket.setSeatNumber(freedSeat);
                ticket.setStatus("CONFIRMED");

                Train* train =
                    findTrain(trainNumber);

                if (train != nullptr)
                {
                    // The freed seat is immediately allocated,
                    // so available count does not increase.
                }

                removeFromWaitingList(
                    ticket.getPNR()
                );

                cout << "\nWaiting passenger promoted!\n";

                cout << "PNR: "
                     << ticket.getPNR()
                     << '\n';

                cout << "Seat: "
                     << freedSeat
                     << '\n';

                return;
            }
        }
    }

    // ========================================================
    // REMOVE FROM WAITING LIST
    // ========================================================

    void removeFromWaitingList(long long pnr)
    {
        waitingList.erase(
            remove_if(
                waitingList.begin(),
                waitingList.end(),
                [pnr](const WaitingPassenger& entry)
                {
                    return entry.pnr == pnr;
                }
            ),
            waitingList.end()
        );
    }

    // ========================================================
    // CANCEL TICKET
    // ========================================================

    void cancelTicket()
    {
        long long pnr;

        cout << "\nEnter PNR to cancel: ";
        cin >> pnr;

        Ticket* ticket =
            findTicket(pnr);

        if (ticket == nullptr)
        {
            cout << "Ticket not found.\n";
            return;
        }

        if (ticket->getStatus() == "CANCELLED")
        {
            cout << "Ticket is already cancelled.\n";
            return;
        }

        Train* train =
            findTrain(ticket->getTrainNumber());

        if (train == nullptr)
        {
            cout << "Associated train not found.\n";
            return;
        }

        // ----------------------------------------------------
        // If confirmed ticket is cancelled
        // ----------------------------------------------------

        if (ticket->getStatus() == "CONFIRMED")
        {
            int freedSeat =
                ticket->getSeatNumber();

            ticket->setStatus("CANCELLED");

            // First check waiting list
            bool waitingExists = false;

            for (const auto& waitingTicket : tickets)
            {
                if (waitingTicket.getTrainNumber() ==
                        ticket->getTrainNumber() &&
                    waitingTicket.getStatus() ==
                        "WAITING")
                {
                    waitingExists = true;
                    break;
                }
            }

            if (waitingExists)
            {
                promoteWaitingPassenger(
                    ticket->getTrainNumber(),
                    freedSeat
                );
            }
            else
            {
                train->cancelSeat();
            }
        }

        // ----------------------------------------------------
        // If waiting ticket is cancelled
        // ----------------------------------------------------

        else if (ticket->getStatus() == "WAITING")
        {
            ticket->setStatus("CANCELLED");

            removeFromWaitingList(
                ticket->getPNR()
            );
        }

        saveTickets();
        saveTrains();

        cout << "\nTicket cancelled successfully.\n";
    }

    // ========================================================
    // SEARCH TICKET BY PNR
    // ========================================================

    void searchTicket()
    {
        long long pnr;

        cout << "\nEnter PNR: ";
        cin >> pnr;

        Ticket* ticket =
            findTicket(pnr);

        if (ticket == nullptr)
        {
            cout << "\nNo ticket found for this PNR.\n";
            return;
        }

        ticket->display();

        Train* train =
            findTrain(ticket->getTrainNumber());

        if (train != nullptr)
        {
            cout << "Train Name    : "
                 << train->getTrainName()
                 << '\n';

            cout << "Route         : "
                 << train->getSource()
                 << " -> "
                 << train->getDestination()
                 << '\n';
        }
    }

    // ========================================================
    // DISPLAY ALL TICKETS
    // ========================================================

    void displayAllTickets()
    {
        if (tickets.empty())
        {
            cout << "\nNo tickets found.\n";
            return;
        }

        cout << "\n";
        cout << "================================================================================\n";
        cout << "                            ALL TICKETS\n";
        cout << "================================================================================\n";

        cout << left
             << setw(14) << "PNR"
             << setw(12) << "Passenger"
             << setw(12) << "Train"
             << setw(10) << "Seat"
             << setw(15) << "Fare"
             << setw(15) << "Status"
             << setw(15) << "Date"
             << '\n';

        cout << string(93, '-') << '\n';

        for (const auto& ticket : tickets)
        {
            cout << left
                 << setw(14)
                 << ticket.getPNR()
                 << setw(12)
                 << ticket.getPassengerName()
                 << setw(12)
                 << ticket.getTrainNumber()
                 << setw(10);

            if (ticket.getSeatNumber() == -1)
                cout << "WAITING";
            else
                cout << ticket.getSeatNumber();

            cout << setw(15)
                 << fixed << setprecision(2)
                 << ticket.getFare()

                 << setw(15)
                 << ticket.getStatus()

                 << setw(15)
                 << ticket.getBookingDate()

                 << '\n';
        }

        cout << "================================================================================\n";
    }

    // ========================================================
    // DISPLAY PASSENGERS
    // ========================================================

    void displayPassengers()
    {
        if (passengers.empty())
        {
            cout << "\nNo passengers registered.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================\n";
        cout << "                       PASSENGER LIST\n";
        cout << "====================================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(8) << "Age"
             << setw(12) << "Gender"
             << setw(18) << "Phone"
             << '\n';

        cout << string(73, '-') << '\n';

        for (const auto& passenger : passengers)
        {
            passenger.display();
        }

        cout << "====================================================================\n";
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
        cout << "                 ADMIN LOGIN\n";
        cout << "============================================\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (username == ADMIN_USERNAME &&
            password == ADMIN_PASSWORD)
        {
            cout << "\nAdmin login successful!\n";
            return true;
        }

        cout << "\nInvalid admin credentials.\n";

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
            cout << "\n============================================\n";
            cout << "              RAILWAY ADMIN PANEL\n";
            cout << "============================================\n";

            cout << "1. Add Train\n";
            cout << "2. Display All Trains\n";
            cout << "3. Display Passengers\n";
            cout << "4. Display All Tickets\n";
            cout << "5. Search Ticket by PNR\n";
            cout << "6. Display Waiting List\n";
            cout << "7. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addTrain();
                    break;

                case 2:
                    displayTrains();
                    break;

                case 3:
                    displayPassengers();
                    break;

                case 4:
                    displayAllTickets();
                    break;

                case 5:
                    searchTicket();
                    break;

                case 6:
                    displayWaitingList();
                    break;

                case 7:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 7);
    }

    // ========================================================
    // DISPLAY WAITING LIST
    // ========================================================

    void displayWaitingList()
    {
        bool found = false;

        cout << "\n";
        cout << "============================================================\n";
        cout << "                     WAITING LIST\n";
        cout << "============================================================\n";

        cout << left
             << setw(14) << "PNR"
             << setw(15) << "Passenger ID"
             << setw(15) << "Train Number"
             << '\n';

        cout << string(44, '-') << '\n';

        for (const auto& entry : waitingList)
        {
            Ticket* ticket =
                findTicket(entry.pnr);

            if (ticket != nullptr &&
                ticket->getStatus() == "WAITING")
            {
                found = true;

                cout << left
                     << setw(14)
                     << entry.pnr
                     << setw(15)
                     << entry.passengerId
                     << setw(15)
                     << entry.trainNumber
                     << '\n';
            }
        }

        if (!found)
        {
            cout << "Waiting list is empty.\n";
        }

        cout << "============================================================\n";
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadTrains();
        loadPassengers();
        loadTickets();

        int choice;

        do
        {
            cout << "\n\n";
            cout << "================================================\n";
            cout << "          RAILWAY RESERVATION SYSTEM\n";
            cout << "================================================\n";

            cout << "1. Add Train Details\n";
            cout << "2. Display Trains\n";
            cout << "3. Register Passenger\n";
            cout << "4. Book Ticket\n";
            cout << "5. Cancel Ticket\n";
            cout << "6. Check Seat Availability\n";
            cout << "7. Search Ticket by PNR\n";
            cout << "8. Display Waiting List\n";
            cout << "9. Admin Panel\n";
            cout << "10. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addTrain();
                    break;

                case 2:
                    displayTrains();
                    break;

                case 3:
                    registerPassenger();
                    break;

                case 4:
                    bookTicket();
                    break;

                case 5:
                    cancelTicket();
                    break;

                case 6:
                    checkSeatAvailability();
                    break;

                case 7:
                    searchTicket();
                    break;

                case 8:
                    displayWaitingList();
                    break;

                case 9:
                    adminPanel();
                    break;

                case 10:
                    saveTrains();
                    savePassengers();
                    saveTickets();

                    cout << "\n============================================\n";
                    cout << " Thank you for using Railway Reservation System!\n";
                    cout << "============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 10);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    RailwaySystem railway;

    railway.run();

    return 0;
}