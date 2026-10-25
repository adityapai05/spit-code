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

    int peek()
    {
        if (isEmpty())
            return -1;

        return stack[top];
    }

    int countNoOfElements()
    {
        return top + 1;
    }
};

int precedence(char op)
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
    string infix, postfix;
    int choice;

    cout << "============================================\n";
    cout << "          ARITHMETIC CALCULATOR\n";
    cout << "============================================\n";
    cout << "  Supports: +  -  *  /  ^  ( )\n";
    cout << "  Example : (2+3)*4\n";
    cout << "============================================\n";

    do
    {
        cout << "\n--------------- MAIN MENU -----------------\n";
        cout << "1. Evaluate Expression\n";
        cout << "2. Exit Calculator\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1)
        {
            infix = "";
            postfix = "";
            Stack operators, values;
            bool valid = true;

            cout << "\n--------------- CALCULATOR ----------------\n";
            cout << "Enter an arithmetic expression: ";
            getline(cin, infix);

            for (int i = 0; i < infix.size(); i++)
            {
                char ch = infix[i];

                if (ch == ' ')
                    continue;

                if (ch >= '0' && ch <= '9')
                {
                    postfix += ch;
                }
                else if (ch == '(')
                {
                    if (!operators.push(ch))
                    {
                        valid = false;
                        break;
                    }
                }
                else if (ch == ')')
                {
                    while (!operators.isEmpty() && operators.peek() != '(')
                        postfix += (char)operators.pop();

                    if (operators.isEmpty())
                    {
                        valid = false;
                        break;
                    }

                    operators.pop();
                }
                else if (ch == '+' || ch == '-' || ch == '*' ||
                         ch == '/' || ch == '^')
                {
                    while (!operators.isEmpty() && operators.peek() != '(' &&
                           (precedence(operators.peek()) > precedence(ch) ||
                            (precedence(operators.peek()) == precedence(ch) && ch != '^')))
                    {
                        postfix += (char)operators.pop();
                    }

                    if (!operators.push(ch))
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

            while (valid && !operators.isEmpty())
            {
                if (operators.peek() == '(')
                {
                    valid = false;
                    break;
                }

                postfix += (char)operators.pop();
            }

            if (!valid)
            {
                cout << "\nError: Invalid expression or unmatched parentheses.\n";
                continue;
            }

            for (int i = 0; i < postfix.size(); i++)
            {
                char ch = postfix[i];

                if (ch >= '0' && ch <= '9')
                {
                    if (!values.push(ch - '0'))
                    {
                        cout << "\nError: Stack overflow.\n";
                        valid = false;
                        break;
                    }
                }
                else
                {
                    if (values.countNoOfElements() < 2)
                    {
                        valid = false;
                        break;
                    }

                    int b = values.pop();
                    int a = values.pop();
                    int result = 0;

                    switch (ch)
                    {
                    case '+':
                        result = a + b;
                        break;
                    case '-':
                        result = a - b;
                        break;
                    case '*':
                        result = a * b;
                        break;
                    case '/':
                        if (b == 0)
                        {
                            cout << "\nError: Division by zero is not allowed.\n";
                            valid = false;
                        }
                        else
                            result = a / b;
                        break;
                    case '^':
                        result = 1;
                        for (int j = 0; j < b; j++)
                            result *= a;
                        break;
                    }

                    if (!valid)
                        break;

                    if (!values.push(result))
                    {
                        cout << "\nError: Stack overflow.\n";
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid || values.countNoOfElements() != 1)
            {
                if (valid)
                    cout << "\nError: Invalid arithmetic expression.\n";
            }
            else
            {
                cout << "\n============================================\n";
                cout << "             CALCULATION RESULT\n";
                cout << "============================================\n";
                cout << "Infix Expression   : " << infix << endl;
                cout << "Postfix Expression : " << postfix << endl;
                cout << "Final Result       : " << values.pop() << endl;
                cout << "============================================\n";
            }
        }
        else if (choice == 2)
        {
            cout << "\nThank you for using the calculator!\n";
            cout << "Exiting program...\n";
        }
        else
        {
            cout << "\nInvalid choice. Please select 1 or 2.\n";
        }

    } while (choice != 2);

    return 0;
}