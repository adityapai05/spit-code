#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const double fees = 100;
const string eventName = "Techfest";

struct EventRegistration
{
    int id;
    string studentName;
    string department;
};

bool validateRegistration(const EventRegistration &r)
{
    if (r.id <= 0)
    {
        cout << "Invalid Registration ID. ID must be greater than 0.\n";
        return false;
    }

    if (r.studentName.empty())
    {
        cout << "Student name cannot be empty.\n";
        return false;
    }

    if (r.department.empty())
    {
        cout << "Department cannot be empty.\n";
        return false;
    }

    return true;
}

bool isDuplicateID(const vector<EventRegistration> &registrations, int id)
{
    return any_of(registrations.begin(), registrations.end(), [id](const EventRegistration &r) {
        return r.id == id;
    });
}

bool inputRegistration(EventRegistration &r)
{
    cout << "\nEnter Registration ID: ";
    cin >> r.id;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Registration ID must be a number.\n";
        return false;
    }

    cin.ignore(1000, '\n');

    cout << "Enter Student Name: ";
    getline(cin, r.studentName);

    cout << "Enter Department: ";
    getline(cin, r.department);

    return true;
}

void addRegistration(vector<EventRegistration> &registrations)
{
    EventRegistration r;

    if (!inputRegistration(r))
    {
        cout << "Registration failed.\n";
        return;
    }

    if (!validateRegistration(r))
    {
        cout << "Registration failed.\n";
        return;
    }

    if (isDuplicateID(registrations, r.id))
    {
        cout << "Registration ID already exists.\n";
        return;
    }

    registrations.push_back(r);
    cout << "Registration successful.\n";
}

double calculateTotalFee(const vector<EventRegistration> &registrations)
{
    return static_cast<double>(registrations.size()) * fees;
}

void displayRegistration(const vector<EventRegistration> &registrations)
{
    int id;
    bool found = false;

    cout << "\nEnter Registration ID: ";
    cin >> id;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Registration ID must be a number.\n";
        return;
    }

    cin.ignore(1000, '\n');

    for (const auto &registration : registrations)
    {
        if (registration.id == id)
        {
            cout << "\nRegistration ID: " << registration.id << "\n";
            cout << "Student Name: " << registration.studentName << "\n";
            cout << "Department: " << registration.department << "\n";
            cout << "Event: " << eventName << "\n";
            cout << "Fee: Rs. " << fees << "\n";
            cout << "Status: Registered\n";

            found = true;
            break;
        }
    }

    if (!found)
        cout << "Registration not found.\n";
}

void displaySummary(const vector<EventRegistration> &registrations)
{
    cout << "\n===== Registration Summary =====\n";

    for (const auto &registration : registrations)
    {
        cout << "ID: " << registration.id
             << " | Name: " << registration.studentName
             << " | Department: " << registration.department
             << " | Status: Registered\n";
    }

    cout << "\nTotal Registrations: "
         << registrations.size() << "\n";

    cout << "Total Fee Collected: Rs. "
         << calculateTotalFee(registrations) << "\n";
}

int main()
{
    vector<EventRegistration> registrations;
    int choice;

    do
    {
        cout << "\n===== Department Event Registration System =====\n";
        cout << "1. Register for Event\n";
        cout << "2. Display Registration\n";
        cout << "3. Display All Registrations and Summary\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please enter a number from 1 to 4.\n";
            continue;
        }

        cin.ignore(1000, '\n');

        if (choice == 1)
        {
            addRegistration(registrations);
        }
        else if (choice == 2)
        {
            if (registrations.empty())
                cout << "No registrations found.\n";
            else
                displayRegistration(registrations);
        }
        else if (choice == 3)
        {
            if (registrations.empty())
                cout << "No registrations found.\n";
            else
                displaySummary(registrations);
        }
        else if (choice == 4)
        {
            cout << "Program ended.\n";
        }
        else
        {
            cout << "Invalid choice. Please enter a number from 1 to 4.\n";
        }

    } while (choice != 4);

    return 0;
}