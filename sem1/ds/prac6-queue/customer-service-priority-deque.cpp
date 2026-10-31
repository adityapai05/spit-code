
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Customer
{
    int id;
    string name;
};

class CustomerService
{
    Customer queue[SIZE];
    int front = -1;
    int rear = -1;
    int nextCustomerId = 1;

public:
    int generateId()
    {
        return nextCustomerId++;
    }

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return (front == 0 && rear == SIZE - 1) ||
               (front == rear + 1);
    }

    void insertFront(Customer customer)
    {
        if (isFull())
        {
            cout << "Queue Overflow. Cannot add customer." << endl;
            return;
        }

        if (isEmpty())
        {
            front = 0;
            rear = 0;
        }

        else if (front < 1)
        {
            front = SIZE - 1;
        }
        else
        {
            front = (front - 1) % SIZE;
        }

        queue[front] = customer;

        cout << "Urgent customer added at the front." << endl;
        display();
    }

    void insertRear(Customer customer)
    {
        if (isFull())
        {
            cout << "Queue Overflow. Cannot add customer." << endl;
            return;
        }

        if (isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = customer;

        cout << "Normal customer added at the rear." << endl;
        display();
    }

    void deleteFront()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow. No customers to serve." << endl;
            return;
        }

        cout << "Serving customer: " << queue[front].name
             << " (ID: " << queue[front].id << ")" << endl;

        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
        }

        display();
    }

    void deleteRear()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow. No customers to serve." << endl;
            return;
        }

        cout << "Serving customer: " << queue[rear].name
             << " (ID: " << queue[rear].id << ")" << endl;

        if (front == rear)
        {
            front = rear = -1;
        }
        else if (rear < 1)
        {
            rear = SIZE - 1;
        }
        else
        {
            rear = (rear - 1) % SIZE;
        }

        display();
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No customers waiting." << endl;
            return;
        }

        cout << "\n----- CUSTOMER SERVICE QUEUE -----" << endl;
        cout << "ID\tCustomer Name" << endl;

        int i = front;

        while (true)
        {
            cout << queue[i].id << "\t"
                 << queue[i].name << endl;

            if (i == rear)
                break;

            i = (i + 1) % SIZE;
        }
    }
};

int main()
{
    CustomerService service;
    int option = 0;

    while (option != 7)
    {
        cout << "\n====== CUSTOMER SERVICE SYSTEM ======" << endl;
        cout << "1. Add Normal Customer (Rear)" << endl;
        cout << "2. Add Urgent Customer (Front)" << endl;
        cout << "3. Serve Next Customer (Front)" << endl;
        cout << "4. Serve Last Customer (Rear)" << endl;
        cout << "5. Display Customers" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> option;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (option)
        {
        case 1:
        case 2:
        {
            Customer customer;

            customer.id = service.generateId();

            cout << "Enter customer name: ";
            cin.ignore(1000, '\n');
            getline(cin, customer.name);

            if (customer.name.empty())
            {
                cout << "Customer name cannot be empty." << endl;
                break;
            }

            if (option == 1)
                service.insertRear(customer);
            else
                service.insertFront(customer);

            break;
        }

        case 3:
            service.deleteFront();
            break;

        case 4:
            service.deleteRear();
            break;

        case 5:
            service.display();
            break;

        case 6:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
        }
    }

    return 0;
}
