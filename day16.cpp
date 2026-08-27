#include <iostream>
#include <string>
using namespace std;

class TicketQueue
{
private:
    int front;
    int rear;
    int size;
    int capacity;
    string *queue;

public:
    // Constructor
    TicketQueue(int cap)
    {
        capacity = cap;
        queue = new string[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    // Check if queue is empty
    bool isEmpty()
    {
        return size == 0;
    }

    // Check if queue is full
    bool isFull()
    {
        return size == capacity;
    }

    // Add customer to queue
    void enqueue(string customer)
    {
        if (isFull())
        {
            cout << "\nQUEUE FULL! Cannot add more customers.\n";
            return;
        }

        rear = (rear + 1) % capacity; // Circular Queue Logic
        queue[rear] = customer;
        size++;

        cout << "\nCustomer Added Successfully!";
        cout << "\nTicket Issued To: " << customer << endl;
    }

    // Remove customer from queue
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "\nQUEUE EMPTY! No customers in queue.\n";
            return;
        }

        cout << "\nServing Customer: " << queue[front] << endl;

        front = (front + 1) % capacity; // Circular Queue Logic
        size--;
    }

    // Display queue
    void displayQueue()
    {
        if (isEmpty())
        {
            cout << "\nQUEUE EMPTY!\n";
            return;
        }

        cout << "\n===== CURRENT TICKET QUEUE =====\n";

        int index = front;

        for (int i = 0; i < size; i++)
        {
            cout << i + 1 << ". " << queue[index] << endl;
            index = (index + 1) % capacity;
        }
    }

    // Display front customer
    void frontCustomer()
    {
        if (isEmpty())
        {
            cout << "\nQUEUE EMPTY!\n";
            return;
        }

        cout << "\nNext Customer To Be Served: " << queue[front] << endl;
    }

    // Current queue size
    void currentSize()
    {
        cout << "\nCurrent Queue Size: " << size << endl;
    }

    // Destructor
    ~TicketQueue()
    {
        delete[] queue;
    }
};

int main()
{
    int capacity;

    cout << "=====================================\n";
    cout << "     TICKET COUNTER QUEUE SYSTEM     \n";
    cout << "=====================================\n";

    cout << "\nEnter Maximum Queue Capacity: ";
    cin >> capacity;

    TicketQueue tq(capacity);

    int choice;
    string customer;

    do
    {
        cout << "\n\n========= MENU =========\n";
        cout << "1. Add Customer (Enqueue)\n";
        cout << "2. Serve Customer (Dequeue)\n";
        cout << "3. Display Queue\n";
        cout << "4. Next Customer\n";
        cout << "5. Queue Size\n";
        cout << "6. Exit\n";
        cout << "========================\n";

        cout << "Enter Choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "\nEnter Customer Name: ";
            getline(cin, customer);

            tq.enqueue(customer);
            break;

        case 2:
            tq.dequeue();
            break;

        case 3:
            tq.displayQueue();
            break;

        case 4:
            tq.frontCustomer();
            break;

        case 5:
            tq.currentSize();
            break;

        case 6:
            cout << "\nExiting Ticket System...\n";
            cout << "Thank You!\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}