#include <iostream>
#include <string>
using namespace std;

class Stack
{
    static const int size = 100;
    int stack[size];
    int top = -1;

public:
    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == size - 1;
    }

    bool push(int value)
    {
        if (isFull())
            return false;

        stack[++top] = value;
        return true;
    }

    int pop()
    {
        if (isEmpty())
            return -1;

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
    string expression;
    bool valid = true;

    cout << "Enter postfix expression: ";
    getline(cin, expression);

    for (int i = 0; i < expression.size(); i++)
    {
        char ch = expression[i];

        if (ch == ' ')
            continue;

        if (ch >= '0' && ch <= '9')
        {
            if (!s.push(ch - '0'))
            {
                cout << "Stack Overflow" << endl;
                return 0;
            }
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (s.countNoOfElements() < 2)
            {
                valid = false;
                break;
            }

            int b = s.pop();
            int a = s.pop();

            switch (ch)
            {
            case '+':
                s.push(a + b);
                break;
            case '-':
                s.push(a - b);
                break;
            case '*':
                s.push(a * b);
                break;
            case '/':
                if (b == 0)
                {
                    cout << "Division by zero." << endl;
                    return 0;
                }
                s.push(a / b);
                break;
            }
        }
        else
        {
            valid = false;
            break;
        }
    }

    if (!valid || s.countNoOfElements() != 1)
        cout << "Invalid postfix expression." << endl;
    else
        cout << "Result: " << s.pop() << endl;

    return 0;
}