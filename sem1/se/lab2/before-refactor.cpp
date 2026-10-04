#include <iostream>
#include <vector>
#include <string>

using namespace std;

double fees = 100;
string eventName = "Techfest";

struct EventRegistration
{
    int id;
    string studentName;
    string department;
};

bool validateRegistration(EventRegistration r)
{
    if (r.id <= 0)
    {
        cout << "Invalid Registration ID.\n";
        return false;
    }

    if (r.studentName.empty())
    {
        cout << "Student name cannot be empty.\n";
        return false;
    }

    return true;
}

void addRegistration(vector<EventRegistration> &registrations)
{
    EventRegistration r;

    cout << "\nEnter Registration ID: ";
    cin >> r.id;
    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, r.studentName);

    cout << "Enter Department: ";
    getline(cin, r.department);

    if (validateRegistration(r))
    {
        registrations.push_back(r);
        cout << "Registration successful.\n";
    }
    else
    {
        cout << "Registration failed.\n";
    }
}

void displayRegistration(const vector<EventRegistration> &registrations)
{
    int id;
    bool found = false;

    cout << "\nEnter Registration ID: ";
    cin >> id;

        for (int i = 0; i < registrations.size(); i++)
    {
        if (registrations[i].id == id)
        {
            cout << "\nRegistration ID: " << registrations[i].id << "\n";
            cout << "Student Name: " << registrations[i].studentName << "\n";
            cout << "Department: " << registrations[i].department << "\n";
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
    double total = 0;

    cout << "\n===== Registration Summary =====\n";

    for (int i = 0; i < registrations.size(); i++)
    {
        cout << "ID: " << registrations[i].id
             << " | Name: " << registrations[i].studentName
             << " | Department: " << registrations[i].department
             << " | Status: Registered\n";

        total += 100;
    }

    cout << "\nTotal Registrations: " << registrations.size() << "\n";
    cout << "Total Fee Collected: Rs. " << total << "\n";
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
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}