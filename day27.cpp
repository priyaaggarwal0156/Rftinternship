#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

// ============================================================
// FILES
// ============================================================

const string MOVIE_FILE = "movies.txt";
const string SHOW_FILE = "shows.txt";
const string BOOKING_FILE = "bookings.txt";

// ============================================================
// ADMIN CREDENTIALS
// ============================================================

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "movie123";

// ============================================================
// UTILITY
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ============================================================
// MOVIE CLASS
// ============================================================

class Movie
{
private:
    int movieId;
    string name;
    string genre;
    string language;
    int duration;

public:

    Movie() : movieId(0), duration(0) {}

    Movie(int id,
          string name,
          string genre,
          string language,
          int duration)
        : movieId(id),
          name(name),
          genre(genre),
          language(language),
          duration(duration)
    {
    }

    int getId() const
    {
        return movieId;
    }

    string getName() const
    {
        return name;
    }

    string serialize() const
    {
        return to_string(movieId) + "|" +
               name + "|" +
               genre + "|" +
               language + "|" +
               to_string(duration);
    }

    void display() const
    {
        cout << left
             << setw(8) << movieId
             << setw(30) << name
             << setw(18) << genre
             << setw(15) << language
             << setw(10) << duration
             << " mins\n";
    }
};

// ============================================================
// SHOW CLASS
// ============================================================

class Show
{
private:
    int showId;
    int movieId;
    string movieName;
    string date;
    string time;
    int totalSeats;
    double ticketPrice;

public:

    Show()
        : showId(0),
          movieId(0),
          totalSeats(0),
          ticketPrice(0)
    {
    }

    Show(int id,
         int movieId,
         string movieName,
         string date,
         string time,
         int seats,
         double price)
        : showId(id),
          movieId(movieId),
          movieName(movieName),
          date(date),
          time(time),
          totalSeats(seats),
          ticketPrice(price)
    {
    }

    int getId() const
    {
        return showId;
    }

    int getMovieId() const
    {
        return movieId;
    }

    string getMovieName() const
    {
        return movieName;
    }

    string getDate() const
    {
        return date;
    }

    string getTime() const
    {
        return time;
    }

    int getTotalSeats() const
    {
        return totalSeats;
    }

    double getTicketPrice() const
    {
        return ticketPrice;
    }

    void display(int bookedSeats = 0) const
    {
        cout << left
             << setw(8) << showId
             << setw(25) << movieName
             << setw(15) << date
             << setw(12) << time
             << setw(12) << totalSeats
             << setw(15) << bookedSeats
             << "Rs. " << fixed << setprecision(2)
             << ticketPrice
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << showId << "|"
           << movieId << "|"
           << movieName << "|"
           << date << "|"
           << time << "|"
           << totalSeats << "|"
           << ticketPrice;

        return ss.str();
    }
};

// ============================================================
// BOOKING CLASS
// ============================================================

class Booking
{
private:
    long long ticketId;

    int showId;

    string movieName;
    string date;
    string time;

    string customerName;
    string phone;

    vector<int> seats;

    double totalAmount;

    string status;

public:

    Booking()
        : ticketId(0),
          showId(0),
          totalAmount(0)
    {
    }

    Booking(long long ticketId,
            int showId,
            string movieName,
            string date,
            string time,
            string customerName,
            string phone,
            vector<int> seats,
            double amount,
            string status)
        : ticketId(ticketId),
          showId(showId),
          movieName(movieName),
          date(date),
          time(time),
          customerName(customerName),
          phone(phone),
          seats(seats),
          totalAmount(amount),
          status(status)
    {
    }

    long long getTicketId() const
    {
        return ticketId;
    }

    int getShowId() const
    {
        return showId;
    }

    string getMovieName() const
    {
        return movieName;
    }

    string getDate() const
    {
        return date;
    }

    string getTime() const
    {
        return time;
    }

    string getCustomerName() const
    {
        return customerName;
    }

    string getPhone() const
    {
        return phone;
    }

    vector<int> getSeats() const
    {
        return seats;
    }

    double getAmount() const
    {
        return totalAmount;
    }

    string getStatus() const
    {
        return status;
    }

    void cancel()
    {
        status = "Cancelled";
    }

    // --------------------------------------------------------
    // Display Receipt
    // --------------------------------------------------------

    void printReceipt() const
    {
        cout << "\n";
        cout << "===============================================\n";
        cout << "              MOVIE TICKET RECEIPT\n";
        cout << "===============================================\n";

        cout << "Ticket ID     : " << ticketId << '\n';
        cout << "Movie         : " << movieName << '\n';
        cout << "Date          : " << date << '\n';
        cout << "Show Time     : " << time << '\n';

        cout << "Customer      : " << customerName << '\n';
        cout << "Phone         : " << phone << '\n';

        cout << "Seats         : ";

        for (size_t i = 0; i < seats.size(); i++)
        {
            cout << seats[i];

            if (i != seats.size() - 1)
                cout << ", ";
        }

        cout << '\n';

        cout << "Tickets       : "
             << seats.size() << '\n';

        cout << "Total Amount  : Rs. "
             << fixed << setprecision(2)
             << totalAmount << '\n';

        cout << "Status        : " << status << '\n';

        cout << "===============================================\n";
        cout << "          Thank you for booking!\n";
        cout << "===============================================\n";
    }

    // --------------------------------------------------------
    // File Serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << ticketId << "|"
           << showId << "|"
           << movieName << "|"
           << date << "|"
           << time << "|"
           << customerName << "|"
           << phone << "|";

        for (size_t i = 0; i < seats.size(); i++)
        {
            ss << seats[i];

            if (i != seats.size() - 1)
                ss << ",";
        }

        ss << "|"
           << totalAmount << "|"
           << status;

        return ss.str();
    }
};

// ============================================================
// MAIN SYSTEM
// ============================================================

class MovieTicketSystem
{
private:

    vector<Movie> movies;
    vector<Show> shows;
    vector<Booking> bookings;

    int nextMovieId = 101;
    int nextShowId = 1001;
    long long nextTicketId = 5000001;

public:

    // ========================================================
    // FIND MOVIE
    // ========================================================

    Movie* findMovie(int id)
    {
        for (auto& movie : movies)
        {
            if (movie.getId() == id)
                return &movie;
        }

        return nullptr;
    }

    // ========================================================
    // FIND SHOW
    // ========================================================

    Show* findShow(int id)
    {
        for (auto& show : shows)
        {
            if (show.getId() == id)
                return &show;
        }

        return nullptr;
    }

    // ========================================================
    // FIND BOOKING
    // ========================================================

    Booking* findBooking(long long ticketId)
    {
        for (auto& booking : bookings)
        {
            if (booking.getTicketId() == ticketId)
                return &booking;
        }

        return nullptr;
    }

    // ========================================================
    // COUNT BOOKED SEATS
    // ========================================================

    int getBookedSeatCount(int showId)
    {
        int count = 0;

        for (const auto& booking : bookings)
        {
            if (booking.getShowId() == showId &&
                booking.getStatus() != "Cancelled")
            {
                count += booking.getSeats().size();
            }
        }

        return count;
    }

    // ========================================================
    // CHECK WHETHER SEAT IS BOOKED
    // ========================================================

    bool isSeatBooked(int showId, int seatNumber)
    {
        for (const auto& booking : bookings)
        {
            if (booking.getShowId() == showId &&
                booking.getStatus() != "Cancelled")
            {
                for (int seat : booking.getSeats())
                {
                    if (seat == seatNumber)
                        return true;
                }
            }
        }

        return false;
    }

    // ========================================================
    // FILE HANDLING - MOVIES
    // ========================================================

    void loadMovies()
    {
        ifstream file(MOVIE_FILE);

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
            string genre;
            string language;
            string duration;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, genre, '|');
            getline(ss, language, '|');
            getline(ss, duration, '|');

            Movie movie(
                stoi(id),
                name,
                genre,
                language,
                stoi(duration)
            );

            movies.push_back(movie);

            nextMovieId =
                max(nextMovieId, movie.getId() + 1);
        }

        file.close();
    }

    // ========================================================
    // SAVE MOVIES
    // ========================================================

    void saveMovies()
    {
        ofstream file(MOVIE_FILE);

        for (const auto& movie : movies)
        {
            file << movie.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // FILE HANDLING - SHOWS
    // ========================================================

    void loadShows()
    {
        ifstream file(SHOW_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string id;
            string movieId;
            string movieName;
            string date;
            string time;
            string seats;
            string price;

            getline(ss, id, '|');
            getline(ss, movieId, '|');
            getline(ss, movieName, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, seats, '|');
            getline(ss, price, '|');

            Show show(
                stoi(id),
                stoi(movieId),
                movieName,
                date,
                time,
                stoi(seats),
                stod(price)
            );

            shows.push_back(show);

            nextShowId =
                max(nextShowId, show.getId() + 1);
        }

        file.close();
    }

    // ========================================================
    // SAVE SHOWS
    // ========================================================

    void saveShows()
    {
        ofstream file(SHOW_FILE);

        for (const auto& show : shows)
        {
            file << show.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // FILE HANDLING - BOOKINGS
    // ========================================================

    void loadBookings()
    {
        ifstream file(BOOKING_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string ticketId;
            string showId;
            string movieName;
            string date;
            string time;
            string customerName;
            string phone;
            string seatsString;
            string amount;
            string status;

            getline(ss, ticketId, '|');
            getline(ss, showId, '|');
            getline(ss, movieName, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, customerName, '|');
            getline(ss, phone, '|');
            getline(ss, seatsString, '|');
            getline(ss, amount, '|');
            getline(ss, status, '|');

            vector<int> seats;

            stringstream seatStream(seatsString);
            string seat;

            while (getline(seatStream, seat, ','))
            {
                seats.push_back(stoi(seat));
            }

            Booking booking(
                stoll(ticketId),
                stoi(showId),
                movieName,
                date,
                time,
                customerName,
                phone,
                seats,
                stod(amount),
                status
            );

            bookings.push_back(booking);

            nextTicketId =
                max(nextTicketId,
                    booking.getTicketId() + 1);
        }

        file.close();
    }

    // ========================================================
    // SAVE BOOKINGS
    // ========================================================

    void saveBookings()
    {
        ofstream file(BOOKING_FILE);

        for (const auto& booking : bookings)
        {
            file << booking.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // ADD MOVIE
    // ========================================================

    void addMovie()
    {
        string name;
        string genre;
        string language;
        int duration;

        clearInput();

        cout << "\n===============================================\n";
        cout << "                 ADD MOVIE\n";
        cout << "===============================================\n";

        cout << "Movie Name: ";
        getline(cin, name);

        cout << "Genre: ";
        getline(cin, genre);

        cout << "Language: ";
        getline(cin, language);

        cout << "Duration (minutes): ";
        cin >> duration;

        if (name.empty() || duration <= 0)
        {
            cout << "\nInvalid movie details.\n";
            return;
        }

        Movie movie(
            nextMovieId,
            name,
            genre,
            language,
            duration
        );

        movies.push_back(movie);

        saveMovies();

        cout << "\nMovie added successfully!\n";
        cout << "Movie ID: "
             << nextMovieId << '\n';

        nextMovieId++;
    }

    // ========================================================
    // DISPLAY MOVIES
    // ========================================================

    void displayMovies()
    {
        if (movies.empty())
        {
            cout << "\nNo movies available.\n";
            return;
        }

        cout << "\n";
        cout << "==========================================================================\n";
        cout << "                              MOVIES\n";
        cout << "==========================================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(30) << "Movie"
             << setw(18) << "Genre"
             << setw(15) << "Language"
             << setw(10) << "Duration"
             << '\n';

        cout << string(75, '-') << '\n';

        for (const auto& movie : movies)
        {
            movie.display();
        }

        cout << "==========================================================================\n";
    }

    // ========================================================
    // ADD SHOW
    // ========================================================

    void addShow()
    {
        if (movies.empty())
        {
            cout << "\nPlease add a movie first.\n";
            return;
        }

        int movieId;
        string date;
        string time;
        int seats;
        double price;

        displayMovies();

        cout << "\nEnter Movie ID: ";
        cin >> movieId;

        Movie* movie =
            findMovie(movieId);

        if (movie == nullptr)
        {
            cout << "\nMovie not found.\n";
            return;
        }

        clearInput();

        cout << "Enter Show Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter Show Time (HH:MM): ";
        getline(cin, time);

        cout << "Enter Total Seats: ";
        cin >> seats;

        cout << "Enter Ticket Price: Rs. ";
        cin >> price;

        if (seats <= 0 || price <= 0)
        {
            cout << "\nInvalid show details.\n";
            return;
        }

        Show show(
            nextShowId,
            movieId,
            movie->getName(),
            date,
            time,
            seats,
            price
        );

        shows.push_back(show);

        saveShows();

        cout << "\nShow added successfully!\n";
        cout << "Show ID: "
             << nextShowId << '\n';

        nextShowId++;
    }

    // ========================================================
    // DISPLAY SHOWS
    // ========================================================

    void displayShows()
    {
        if (shows.empty())
        {
            cout << "\nNo shows available.\n";
            return;
        }

        cout << "\n";
        cout << "=========================================================================================\n";
        cout << "                                  SHOW TIMINGS\n";
        cout << "=========================================================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(25) << "Movie"
             << setw(15) << "Date"
             << setw(12) << "Time"
             << setw(12) << "Total"
             << setw(15) << "Booked"
             << "Price\n";

        cout << string(100, '-') << '\n';

        for (const auto& show : shows)
        {
            show.display(
                getBookedSeatCount(show.getId())
            );
        }

        cout << "=========================================================================================\n";
    }

    // ========================================================
    // DISPLAY SEAT MAP
    // ========================================================

    void displaySeats(int showId)
    {
        Show* show =
            findShow(showId);

        if (show == nullptr)
        {
            cout << "\nShow not found.\n";
            return;
        }

        cout << "\n===============================================\n";
        cout << "                 SEAT MAP\n";
        cout << "===============================================\n";

        cout << "Movie : "
             << show->getMovieName()
             << '\n';

        cout << "Date  : "
             << show->getDate()
             << '\n';

        cout << "Time  : "
             << show->getTime()
             << '\n';

        cout << "\n";
        cout << "[X] = Booked    [O] = Available\n\n";

        for (int seat = 1;
             seat <= show->getTotalSeats();
             seat++)
        {
            if (isSeatBooked(showId, seat))
                cout << "[X] ";
            else
                cout << "[O] ";

            cout << setw(3)
                 << seat;

            if (seat % 10 == 0)
                cout << '\n';
        }

        cout << "\n===============================================\n";
    }

    // ========================================================
    // BOOK TICKETS
    // ========================================================

    void bookTickets()
    {
        if (shows.empty())
        {
            cout << "\nNo shows available.\n";
            return;
        }

        displayShows();

        int showId;

        cout << "\nEnter Show ID: ";
        cin >> showId;

        Show* show =
            findShow(showId);

        if (show == nullptr)
        {
            cout << "\nShow not found.\n";
            return;
        }

        int available =
            show->getTotalSeats()
            - getBookedSeatCount(showId);

        if (available <= 0)
        {
            cout << "\nSorry! House full.\n";
            return;
        }

        displaySeats(showId);

        int numberOfTickets;

        cout << "\nAvailable Seats: "
             << available
             << '\n';

        cout << "Number of tickets: ";
        cin >> numberOfTickets;

        if (numberOfTickets <= 0 ||
            numberOfTickets > available)
        {
            cout << "\nInvalid number of tickets.\n";
            return;
        }

        vector<int> selectedSeats;

        for (int i = 0;
             i < numberOfTickets;
             i++)
        {
            int seat;

            cout << "Enter Seat Number "
                 << i + 1
                 << ": ";

            cin >> seat;

            if (seat < 1 ||
                seat > show->getTotalSeats())
            {
                cout << "\nInvalid seat number.\n";
                return;
            }

            if (isSeatBooked(showId, seat))
            {
                cout << "\nSeat "
                     << seat
                     << " is already booked.\n";

                return;
            }

            if (find(selectedSeats.begin(),
                     selectedSeats.end(),
                     seat)
                != selectedSeats.end())
            {
                cout << "\nYou selected the same seat twice.\n";
                return;
            }

            selectedSeats.push_back(seat);
        }

        clearInput();

        string customerName;
        string phone;

        cout << "Customer Name: ";
        getline(cin, customerName);

        cout << "Phone Number: ";
        getline(cin, phone);

        double totalAmount =
            numberOfTickets *
            show->getTicketPrice();

        Booking booking(
            nextTicketId,
            showId,
            show->getMovieName(),
            show->getDate(),
            show->getTime(),
            customerName,
            phone,
            selectedSeats,
            totalAmount,
            "Confirmed"
        );

        bookings.push_back(booking);

        saveBookings();

        cout << "\nBooking successful!\n";

        booking.printReceipt();

        nextTicketId++;
    }

    // ========================================================
    // CANCEL TICKET
    // ========================================================

    void cancelTicket()
    {
        long long ticketId;

        cout << "\nEnter Ticket ID: ";
        cin >> ticketId;

        Booking* booking =
            findBooking(ticketId);

        if (booking == nullptr)
        {
            cout << "\nBooking not found.\n";
            return;
        }

        if (booking->getStatus() == "Cancelled")
        {
            cout << "\nThis ticket is already cancelled.\n";
            return;
        }

        booking->cancel();

        saveBookings();

        cout << "\nTicket cancelled successfully.\n";

        cout << "Refund Amount: Rs. "
             << fixed << setprecision(2)
             << booking->getAmount()
             << '\n';
    }

    // ========================================================
    // SEARCH BOOKING
    // ========================================================

    void searchBooking()
    {
        long long ticketId;

        cout << "\nEnter Ticket ID: ";
        cin >> ticketId;

        Booking* booking =
            findBooking(ticketId);

        if (booking == nullptr)
        {
            cout << "\nNo booking found.\n";
            return;
        }

        booking->printReceipt();
    }

    // ========================================================
    // REVENUE REPORT
    // ========================================================

    void revenueReport()
    {
        double revenue = 0;

        int confirmedBookings = 0;
        int cancelledBookings = 0;
        int totalTickets = 0;

        for (const auto& booking : bookings)
        {
            if (booking.getStatus() == "Confirmed")
            {
                revenue += booking.getAmount();

                confirmedBookings++;

                totalTickets +=
                    booking.getSeats().size();
            }
            else if (booking.getStatus() == "Cancelled")
            {
                cancelledBookings++;
            }
        }

        cout << "\n";
        cout << "===============================================\n";
        cout << "                REVENUE REPORT\n";
        cout << "===============================================\n";

        cout << "Confirmed Bookings : "
             << confirmedBookings
             << '\n';

        cout << "Cancelled Bookings : "
             << cancelledBookings
             << '\n';

        cout << "Tickets Sold       : "
             << totalTickets
             << '\n';

        cout << "Total Revenue      : Rs. "
             << fixed << setprecision(2)
             << revenue
             << '\n';

        cout << "===============================================\n";
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
        cout << "                  ADMIN LOGIN\n";
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
            cout << "===============================================\n";
            cout << "             ADMIN DASHBOARD\n";
            cout << "===============================================\n";

            cout << "1. Add Movie\n";
            cout << "2. Display Movies\n";
            cout << "3. Add Show Timing\n";
            cout << "4. Display Shows\n";
            cout << "5. Display All Bookings\n";
            cout << "6. Revenue Report\n";
            cout << "7. Search Booking\n";
            cout << "8. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addMovie();
                    break;

                case 2:
                    displayMovies();
                    break;

                case 3:
                    addShow();
                    break;

                case 4:
                    displayShows();
                    break;

                case 5:
                    displayAllBookings();
                    break;

                case 6:
                    revenueReport();
                    break;

                case 7:
                    searchBooking();
                    break;

                case 8:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 8);
    }

    // ========================================================
    // DISPLAY ALL BOOKINGS
    // ========================================================

    void displayAllBookings()
    {
        if (bookings.empty())
        {
            cout << "\nNo bookings available.\n";
            return;
        }

        cout << "\n";
        cout << "================================================================================================\n";
        cout << "                                  ALL BOOKINGS\n";
        cout << "================================================================================================\n";

        cout << left
             << setw(14) << "Ticket ID"
             << setw(25) << "Movie"
             << setw(20) << "Customer"
             << setw(15) << "Date"
             << setw(12) << "Time"
             << setw(15) << "Amount"
             << "Status\n";

        cout << string(110, '-') << '\n';

        for (const auto& booking : bookings)
        {
            cout << left
                 << setw(14)
                 << booking.getTicketId()

                 << setw(25)
                 << booking.getMovieName()

                 << setw(20)
                 << booking.getCustomerName()

                 << setw(15)
                 << booking.getDate()

                 << setw(12)
                 << booking.getTime()

                 << setw(15)
                 << fixed << setprecision(2)
                 << booking.getAmount()

                 << booking.getStatus()
                 << '\n';
        }

        cout << "================================================================================================\n";
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadMovies();
        loadShows();
        loadBookings();

        int choice;

        do
        {
            cout << "\n\n";
            cout << "====================================================\n";
            cout << "           MOVIE TICKET BOOKING SYSTEM\n";
            cout << "====================================================\n";

            cout << "1. View Movies\n";
            cout << "2. View Show Timings\n";
            cout << "3. Display Seat Availability\n";
            cout << "4. Book Tickets\n";
            cout << "5. Cancel Ticket\n";
            cout << "6. Search Booking by Ticket ID\n";
            cout << "7. Print Ticket Receipt\n";
            cout << "8. Admin Login\n";
            cout << "9. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayMovies();
                    break;

                case 2:
                    displayShows();
                    break;

                case 3:
                {
                    int showId;

                    displayShows();

                    cout << "\nEnter Show ID: ";
                    cin >> showId;

                    displaySeats(showId);

                    break;
                }

                case 4:
                    bookTickets();
                    break;

                case 5:
                    cancelTicket();
                    break;

                case 6:
                    searchBooking();
                    break;

                case 7:
                {
                    long long ticketId;

                    cout << "\nEnter Ticket ID: ";
                    cin >> ticketId;

                    Booking* booking =
                        findBooking(ticketId);

                    if (booking == nullptr)
                    {
                        cout << "\nBooking not found.\n";
                    }
                    else
                    {
                        booking->printReceipt();
                    }

                    break;
                }

                case 8:
                    adminDashboard();
                    break;

                case 9:

                    saveMovies();
                    saveShows();
                    saveBookings();

                    cout << "\n";
                    cout << "===============================================\n";
                    cout << " Thank you for using Movie Ticket System!\n";
                    cout << "===============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 9);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    MovieTicketSystem system;

    system.run();

    return 0;
}