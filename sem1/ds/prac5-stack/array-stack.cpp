#include <iostream>
using namespace std;

class Stack
{
    static const int size = 10;
    int stack[size];
    int top = -1;

public:
    int peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return -1;
        }
        return stack[top];
    }

    void displayStack()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return;
        }

        for (int i = top; i >= 0; i--)
            cout << stack[i] << endl;
    }

    void updateStackElement(int index, int value)
    {
        if (index < 0 || index > top)
        {
            cout << "No element present at index " << index << " to update." << endl;
            return;
        }

        stack[index] = value;
        cout << "Stack value updated at index " << index << endl;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == size - 1;
    }

    void push(int value)
    {
        if (isFull())
        {
            cout << "Stack is full. Element cannot be inserted." << endl;
            return;
        }

        stack[++top] = value;
        cout << value << " was inserted into the stack." << endl;
    }

    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty. Element cannot be deleted." << endl;
            return -1;
        }

        return stack[top--];
    }

    int countNoOfElements()
    {
        return top + 1;
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
            if (!s.isEmpty())
                cout << "Top element: " << s.peek() << endl;
            else
                cout << "Stack is empty." << endl;
            break;
        }

        case 2:
        {
            s.displayStack();
            break;
        }

        case 3:
        {
            int index, value;
            cout << "Enter index to update: ";
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
            if (s.isFull())
                cout << "Stack is full." << endl;
            else
                cout << "Stack is not full." << endl;
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
            if (!s.isEmpty())
                cout << s.pop() << " was deleted from the stack." << endl;
            else
                cout << "Stack is empty. Element cannot be deleted." << endl;
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

