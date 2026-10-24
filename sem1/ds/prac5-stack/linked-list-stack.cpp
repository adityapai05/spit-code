#include <iostream>
using namespace std;

class Stack
{
    struct Node
    {
        int data;
        Node *next;
    };

    Node *top = nullptr;

public:
    int peek()
    {
        return top->data;
    }

    void displayStack()
    {
        Node *currentNode = top;

        while (currentNode != nullptr)
        {
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }

    void updateStackElement(int index, int value)
    {
        if (index < 0)
        {
            cout << "Invalid index." << endl;
            return;
        }

        Node *currentNode = top;
        int count = 0;

        while (currentNode != nullptr && count < index)
        {
            count++;
            currentNode = currentNode->next;
        }

        if (currentNode == nullptr)
        {
            cout << "No element present at index " << index << " to update." << endl;
            return;
        }

        currentNode->data = value;
        cout << "Stack value updated at index " << index << endl;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    void push(int value)
    {
        Node *node = new Node();
        node->data = value;
        node->next = top;
        top = node;

        cout << value << " was inserted into the stack." << endl;
    }

    int pop()
    {
        int data = top->data;
        Node *prevTop = top;
        top = top->next;
        delete prevTop;
        return data;
    }

    int countNoOfElements()
    {
        int count = 0;
        Node *currentNode = top;

        while (currentNode != nullptr)
        {
            count++;
            currentNode = currentNode->next;
        }

        return count;
    }
};

int main()
{
    Stack s;
    int option = 0;

    while (option != 9)
    {
        cout << "\nMENU\n";
        cout << "1. View the Top Element of the Stack\n";
        cout << "2. Display All Elements in the Stack\n";
        cout << "3. Update an Element in the Stack\n";
        cout << "4. Check if Stack is Empty\n";
        cout << "5. Check if Stack is Full\n";
        cout << "6. Insert an Element at the Top of the Stack\n";
        cout << "7. Delete an Element from the Top of the Stack\n";
        cout << "8. Count Number of Elements in the Stack\n";
        cout << "9. Exit\n";
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
            if (s.isEmpty())
                cout << "Stack is empty." << endl;
            else
                cout << "Top element: " << s.peek() << endl;
            break;
        }

        case 2:
        {
            if (s.isEmpty())
                cout << "Stack is empty." << endl;
            else
            {
                cout << "Elements in stack:" << endl;
                s.displayStack();
            }
            break;
        }

        case 3:
        {
            int index, value;

            cout << "Enter index to update (0 = top): ";
            cin >> index;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid index." << endl;
                break;
            }

            cout << "Enter new value: ";
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid value." << endl;
                break;
            }

            s.updateStackElement(index, value);
            break;
        }

        case 4:
        {
            if (s.isEmpty())
                cout << "Stack is empty." << endl;
            else
                cout << "Stack is not empty." << endl;
            break;
        }

        case 5:
        {
            cout << "A linked-list stack is not limited to a fixed size." << endl;
            break;
        }

        case 6:
        {
            int value;
            cout << "Enter value to insert: ";
            cin >> value;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid value." << endl;
                break;
            }

            s.push(value);
            break;
        }

        case 7:
        {
            if (s.isEmpty())
                cout << "Stack is empty. Element cannot be deleted." << endl;
            else
                cout << s.pop() << " was deleted from the stack." << endl;
            break;
        }

        case 8:
        {
            cout << "Number of elements in stack: "
                 << s.countNoOfElements() << endl;
            break;
        }

        case 9:
        {
            cout << "Exiting program..." << endl;
            break;
        }

        default:
        {
            cout << "Invalid choice. Please enter 1 to 9." << endl;
        }
        }
    }

    return 0;
}
