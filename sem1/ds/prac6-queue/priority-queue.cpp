
#include <iostream>
using namespace std;

const int SIZE = 10;

class PriorityQueue
{
    int queue[SIZE];
    int priority[SIZE];
    int front = -1;
    int rear = -1;

public:
    void enqueue(int value, int p)
    {
        if (isFull())
        {
            cout << "Queue Overflow. Insertion not possible." << endl;
            return;
        }

        if (isEmpty())
        {
            front = 0;
            rear = 0;
            queue[rear] = value;
            priority[rear] = p;
        }
        else
        {
            int i;

            for (i = rear; i >= front; i--)
            {
                if (p > priority[i])
                {
                    queue[i + 1] = queue[i];
                    priority[i + 1] = priority[i];
                }
                else
                {
                    break;
                }
            }

            queue[i + 1] = value;
            priority[i + 1] = p;
            rear++;
        }

        cout << value << " was enqueued with priority " << p << "." << endl;
        display();
    }
    
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow. Deletion not possible." << endl;
            return;
        }

        cout << queue[front] << " was dequeued. Priority: "
             << priority[front] << endl;

        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            for (int i = front; i < rear; i++)
            {
                queue[i] = queue[i + 1];
                priority[i] = priority[i + 1];
            }

            rear--;
        }

        display();
    }

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return rear == SIZE - 1;
    }

    void peek()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No highest priority element." << endl;
            return;
        }

        cout << "Highest Priority Element: " << queue[front]
             << " | Priority: " << priority[front] << endl;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "\nElements in the Priority Queue:" << endl;
        cout << "Priority\tElement" << endl;

        for (int i = front; i <= rear; i++)
        {
            cout << priority[i] << "\t\t" << queue[i] << endl;
        }
    }
};

int main()
{
    PriorityQueue q;
    int option = 0;

    while (option != 7)
    {
        cout << "\n====== PRIORITY QUEUE MENU ======" << endl;
        cout << "1. Enqueue (Insert)" << endl;
        cout << "2. Dequeue (Delete)" << endl;
        cout << "3. Check if Queue is Empty" << endl;
        cout << "4. Check if Queue is Full" << endl;
        cout << "5. Peek Highest Priority Element" << endl;
        cout << "6. Display Queue" << endl;
        cout << "7. Exit" << endl;
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
        {
            int value, p;

            cout << "Enter the element: ";
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter an integer." << endl;
                break;
            }

            cout << "Enter its priority (larger number = higher priority): ";
            cin >> p;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter an integer." << endl;
                break;
            }

            q.enqueue(value, p);
            break;
        }

        case 2:
            q.dequeue();
            break;

        case 3:
            if (q.isEmpty())
                cout << "Queue is empty." << endl;
            else
                cout << "Queue is not empty." << endl;
            break;

        case 4:
            if (q.isFull())
                cout << "Queue is full." << endl;
            else
                cout << "Queue is not full." << endl;
            break;

        case 5:
            q.peek();
            break;

        case 6:
            q.display();
            break;

        case 7:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
        }
    }

    return 0;
}
