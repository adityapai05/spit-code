#include <iostream>
using namespace std;

const int SIZE = 100;

class Deque
{
    int queue[SIZE];
    int front = -1;
    int rear = -1;

public:
    void insertFront(int value)
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
        }
        else if (front < 1)
        {
            front = SIZE - 1;
        }
        else
        {
            front = (front - 1) % SIZE;
        }
        queue[front] = value;
        cout << value << " was enqueued." << endl;
        display();
    }

    void insertRear(int value)
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
        }
        else
        {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = value;
        cout << value << " was enqueued." << endl;
        display();
    }

    void deleteFront()
    {
        if (isEmpty())
        {
            cout << "Queue Underflow. Deletion not possible." << endl;
            return;
        }
        cout << queue[front] << " was dequeued." << endl;
        if (front == rear)
        {
            front = -1;
            rear = -1;
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
            cout << "Queue Underflow. Deletion not possible." << endl;
            return;
        }
        cout << queue[rear] << " was dequeued." << endl;
        if (front == rear)
        {
            front = -1;
            rear = -1;
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

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return (front == 0 && rear == SIZE - 1) || front == rear + 1;
    }

    void peekFront()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No front element." << endl;
        }
        else
        {
            cout << "Element at front: " << queue[front] << endl;
        }
    }

    void peekRear()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No rear element." << endl;
        }
        else
        {
            cout << "Element at rear: " << queue[rear] << endl;
        }
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "Elements in the queue: ";
        int i = front;
        do
        {
            cout << queue[i] << " ";

            if (i == rear)
            {
                break;
            }

            i = (i + 1) % SIZE;

        } while (true);
        cout << endl;
    }
};

int main()
{
    Deque q;
    int option = 0;

    while (option != 9)
    {
        cout << "\n========== DEQUE MENU ==========" << endl;
        cout << "1. Insert at Front" << endl;
        cout << "2. Insert at Rear" << endl;
        cout << "3. Delete from Front" << endl;
        cout << "4. Delete from Rear" << endl;
        cout << "5. Check if Deque is Empty" << endl;
        cout << "6. Check if Deque is Full" << endl;
        cout << "7. Display Front and Rear Elements" << endl;
        cout << "8. Display Deque" << endl;
        cout << "9. Exit" << endl;
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
            int value;
            cout << "Enter the element: ";
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter an integer." << endl;
                break;
            }

            q.insertFront(value);
            break;
        }

        case 2:
        {
            int value;
            cout << "Enter the element: ";
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter an integer." << endl;
                break;
            }

            q.insertRear(value);
            break;
        }

        case 3:
            q.deleteFront();
            break;

        case 4:
            q.deleteRear();
            break;

        case 5:
            cout << (q.isEmpty() ? "Deque is empty." : "Deque is not empty.") << endl;
            break;

        case 6:
            cout << (q.isFull() ? "Deque is full." : "Deque is not full.") << endl;
            break;

        case 7:
            q.peekFront();
            q.peekRear();
            break;

        case 8:
            q.display();
            break;

        case 9:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
        }
    }

    return 0;
}