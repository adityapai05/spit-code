#include <iostream>
using namespace std;

const int SIZE = 100;

class CircularQueue
{
    int queue[SIZE];
    int front = -1;
    int rear = -1;

public:
    void enqueue(int value)
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

    void dequeue()
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

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return front == (rear + 1) % SIZE;
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
    CircularQueue q;
    int option = 0;

    while (option != 7)
    {
        cout << "\n====== CIRCULAR QUEUE MENU ======" << endl;
        cout << "1. Enqueue (Insert)" << endl;
        cout << "2. Dequeue (Delete)" << endl;
        cout << "3. Check if Queue is Empty" << endl;
        cout << "4. Check if Queue is Full" << endl;
        cout << "5. Display Front Element" << endl;
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
            int value;

            cout << "Enter the element to enqueue: ";
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter an integer." << endl;
                break;
            }

            q.enqueue(value);
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
            q.peekFront();
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