#include <iostream>
#include <string>
using namespace std;

class Stack
{
    static const int size = 100;
    char stack[size];
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

    bool push(char value)
    {
        if (isFull())
            return false;

        stack[++top] = value;
        return true;
    }

    char pop()
    {
        if (isEmpty())
            return -1;

        return stack[top--];
    }

    char peek()
    {
        if (isEmpty())
            return -1;

        return stack[top];
    }
};

int checkPrecedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;

    return 0;
}

int main()
{
    Stack s;
    string infix, postfix = "";
    bool valid = true;

    cout << "Enter infix expression: ";
    getline(cin, infix);

    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix[i];

        if (ch == ' ')
            continue;

        if ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9'))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            if (!s.push(ch))
            {
                valid = false;
                break;
            }
        }
        else if (ch == ')')
        {
            while (!s.isEmpty() && s.peek() != '(')
                postfix += s.pop();

            if (s.isEmpty())
            {
                valid = false;
                break;
            }

            s.pop();
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/' || ch == '^')
        {
            while (!s.isEmpty() && s.peek() != '(' &&
                   (checkPrecedence(s.peek()) > checkPrecedence(ch) ||
                    (checkPrecedence(s.peek()) == checkPrecedence(ch) && ch != '^')))
            {
                postfix += s.pop();
            }

            if (!s.push(ch))
            {
                valid = false;
                break;
            }
        }
        else
        {
            valid = false;
            break;
        }
    }

    while (valid && !s.isEmpty())
    {
        if (s.peek() == '(')
        {
            valid = false;
            break;
        }

        postfix += s.pop();
    }

    if (valid)
        cout << "Postfix expression: " << postfix << endl;
    else
        cout << "Invalid infix expression." << endl;

    return 0;
}