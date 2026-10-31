
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Packet
{
    int id;
    string data;
};

class NetworkBuffer
{
    Packet queue[SIZE];
    int front = -1;
    int rear = -1;
    int nextPacketId = 1;

public:
    void enqueue(string data)
    {
        if (isFull())
        {
            cout << "Buffer Overflow. Cannot receive packet." << endl;
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

        queue[rear].id = nextPacketId++;
        queue[rear].data = data;

        cout << "Packet " << queue[rear].id
             << " received successfully." << endl;

        display();
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Buffer Underflow. No packets to process." << endl;
            return;
        }

        cout << "Processing Packet " << queue[front].id
             << " | Data: " << queue[front].data << endl;

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
            cout << "Buffer is empty. No packet to process." << endl;
        }
        else
        {
            cout << "Next Packet: " << queue[front].id
                 << " | Data: " << queue[front].data << endl;
        }
    }

    void peekRear()
    {
        if (isEmpty())
        {
            cout << "Buffer is empty. No recently received packet." << endl;
        }
        else
        {
            cout << "Last Received Packet: " << queue[rear].id
                 << " | Data: " << queue[rear].data << endl;
        }
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Network buffer is empty." << endl;
            return;
        }

        cout << "\n----- NETWORK PACKET BUFFER -----" << endl;
        cout << "Packet ID\tPacket Data" << endl;

        int i = front;

        do
        {
            cout << queue[i].id << "\t\t"
                 << queue[i].data << endl;

            if (i == rear)
            {
                break;
            }

            i = (i + 1) % SIZE;

        } while (true);
    }
};

int main()
{
    NetworkBuffer buffer;
    int option = 0;

    while (option != 7)
    {
        cout << "\n====== NETWORK DATA BUFFER ======" << endl;
        cout << "1. Receive Packet (Enqueue)" << endl;
        cout << "2. Process Packet (Dequeue)" << endl;
        cout << "3. Check if Buffer is Empty" << endl;
        cout << "4. Check if Buffer is Full" << endl;
        cout << "5. Display Next Packet" << endl;
        cout << "6. Display Buffer" << endl;
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
            string data;

            cin.ignore(1000, '\n');

            cout << "Enter packet data: ";
            getline(cin, data);

            if (data.empty())
            {
                cout << "Packet data cannot be empty." << endl;
                break;
            }

            buffer.enqueue(data);
            break;
        }

        case 2:
            buffer.dequeue();
            break;

        case 3:
            if (buffer.isEmpty())
                cout << "Buffer is empty." << endl;
            else
                cout << "Buffer is not empty." << endl;
            break;

        case 4:
            if (buffer.isFull())
                cout << "Buffer is full." << endl;
            else
                cout << "Buffer is not full." << endl;
            break;

        case 5:
            buffer.peekFront();
            break;

        case 6:
            buffer.display();
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
