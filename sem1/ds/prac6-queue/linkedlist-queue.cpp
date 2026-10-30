#include <iostream>
using namespace std;

class Queue
{
    struct Node
    {
        int data;
        Node *next;
        Node(int value)
        {
            data = value;
            next = nullptr;
        }
    };

    Node *front = nullptr;
    Node *rear = nullptr;

public:
    void enqueue(int value)
    {
        Node *node = new Node(value);
        if (front == nullptr && rear == nullptr)
        {
            front = node;
            rear = node;
        }
        else
        {
            rear->next = node;
            rear = node;
        }
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

        cout << front->data << " was dequeued." << endl;

        Node *temp = front;
        if (front == rear)
        {
            front = nullptr;
            rear = nullptr;
        }
        else
        {
            front = front->next;
        }
        delete temp;
        display();
    }

    bool isEmpty()
    {
        return front == nullptr;
    }

    void peekFront()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. No front element." << endl;
        }
        else
        {
            cout << "Element at front: " << front->data << endl;
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
            cout << "Element at rear: " << rear->data << endl;
        }
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty. Nothing to display." << endl;
        }
        else
        {
            cout << "Elements in the queue: ";
            Node *current = front;
            while (current != nullptr)
            {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main()
{
    Queue q;
    int option = 0;

    while (option != 7)
    {
        cout << "\n========== QUEUE MENU ==========" << endl;
        cout << "1. Enqueue (Insert)" << endl;
        cout << "2. Dequeue (Delete)" << endl;
        cout << "3. Check if Queue is Empty" << endl;
        cout << "4. Display Front Element" << endl;
        cout << "5. Display Rear Element" << endl;
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
            q.peekFront();
            break;

        case 5:
            q.peekRear();
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