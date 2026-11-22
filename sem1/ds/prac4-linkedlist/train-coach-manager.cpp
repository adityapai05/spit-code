#include <iostream>
#include <string>
using namespace std;

class Train
{
    struct Coach
    {
        int coachNumber;
        string coachType;
        Coach *next;
    };
    Coach *head;

public:
    Train()
    {
        head = nullptr;
    }

    int countCoaches()
    {
        int count = 0;
        Coach *p = head;
        while (p != nullptr)
        {
            count++;
            p = p->next;
        }
        return count;
    }

    void addAtFront(int num, string type)
    {
        Coach *newCoach = new Coach;
        newCoach->coachNumber = num;
        newCoach->coachType = type;
        newCoach->next = head;
        head = newCoach;
        cout << "\nCoach added at Front\n";
        display();
    }

    void addAtEnd(int num, string type)
    {
        Coach *newCoach = new Coach;
        newCoach->coachNumber = num;
        newCoach->coachType = type;
        newCoach->next = nullptr;

        if (head == nullptr)
        {
            head = newCoach;
        }
        else
        {
            Coach *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = newCoach;
        }
        cout << "\nCoach added at End\n";
        display();
    }

    void addAtPosition(int pos, int num, string type)
    {
        int len = countCoaches();
        if (pos < 1 || pos > len + 1)
        {
            cout << "\nInvalid Position!\n";
            return;
        }

        if (pos == 1)
        {
            addAtFront(num, type);
            return;
        }

        Coach *newCoach = new Coach;
        newCoach->coachNumber = num;
        newCoach->coachType = type;

        Coach *p = head;
        for (int i = 1; i < pos - 1; i++)
        {
            p = p->next;
        }
        newCoach->next = p->next;
        p->next = newCoach;
        cout << "\nCoach added at Position " << pos << "\n";
        display();
    }

    void removeFromFront()
    {
        if (head == nullptr)
        {
            cout << "\nTrain has no coaches to remove\n";
            return;
        }

        Coach *p = head;
        head = head->next;
        cout << "\nRemoved Front Coach: [" << p->coachNumber << " - " << p->coachType << "]\n";
        delete p;
        display();
    }

    void removeFromEnd()
    {
        if (head == nullptr)
        {
            cout << "\nTrain has no coaches to remove\n";
            return;
        }

        if (head->next == nullptr)
        {
            cout << "\nRemoved Rear Coach: [" << head->coachNumber << " - " << head->coachType << "]\n";
            delete head;
            head = nullptr;
            display();
            return;
        }

        Coach *p = head, *q = nullptr;
        while (p->next != nullptr)
        {
            q = p;
            p = p->next;
        }
        q->next = nullptr;
        cout << "\nRemoved Rear Coach: [" << p->coachNumber << " - " << p->coachType << "]\n";
        delete p;
        display();
    }

    void removeAtPosition(int pos)
    {
        int len = countCoaches();
        if (head == nullptr)
        {
            cout << "\nTrain has no coaches to remove\n";
            return;
        }
        if (pos < 1 || pos > len)
        {
            cout << "\nInvalid Position!\n";
            return;
        }
        if (pos == 1)
        {
            removeFromFront();
            return;
        }

        Coach *p = head, *q = nullptr;
        for (int i = 1; i < pos - 1; i++)
        {
            p = p->next;
        }
        q = p->next;
        p->next = q->next;
        cout << "\nRemoved Position " << pos << " Coach: [" << q->coachNumber << " - " << q->coachType << "]\n";
        delete q;
        display();
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "\n[ENGINE] -> (No Coaches)\n";
            return;
        }

        Coach *p = head;
        cout << "\nTrain Sequence:\n[ENGINE]";
        while (p != nullptr)
        {
            cout << " -> [" << p->coachNumber << ":" << p->coachType << "]";
            p = p->next;
        }
        cout << "\n";
    }
};

int main()
{
    Train t;
    int choice, num, pos;
    string type;

    do
    {
        cout << "\n===== TRAIN COACH MANAGEMENT =====\n";
        cout << "1. Add Coach at Front\n";
        cout << "2. Add Coach at End\n";
        cout << "3. Add Coach at Position\n";
        cout << "4. Remove Coach from Front\n";
        cout << "5. Remove Coach from End\n";
        cout << "6. Remove Coach at Position\n";
        cout << "7. Display Train Sequence\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Coach Number: ";
            cin >> num;
            cout << "Enter Coach Type: ";
            cin >> type;
            t.addAtFront(num, type);
            break;

        case 2:
            cout << "Enter Coach Number: ";
            cin >> num;
            cout << "Enter Coach Type: ";
            cin >> type;
            t.addAtEnd(num, type);
            break;

        case 3:
            cout << "Enter Position: ";
            cin >> pos;
            cout << "Enter Coach Number: ";
            cin >> num;
            cout << "Enter Coach Type: ";
            cin >> type;
            t.addAtPosition(pos, num, type);
            break;

        case 4:
            t.removeFromFront();
            break;

        case 5:
            t.removeFromEnd();
            break;

        case 6:
            cout << "Enter Position: ";
            cin >> pos;
            t.removeAtPosition(pos);
            break;

        case 7:
            t.display();
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}