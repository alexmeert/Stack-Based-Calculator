#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

class Stack {
private:
    static const int MAX_SIZE = 100;
    int str[MAX_SIZE];
    int top = -1;

public:
    bool isEmpty() const
    {
        return top < 0;
    }

    bool isFull() const
    {
        return top >= MAX_SIZE - 1;
    }

    void push(int val)
    {
        if (!isFull())
        {
            str[++top] = val;
        }
        else
        {
            cout << "Stack Overflow!" << endl;
        }
    }

    void pop() {
        if (!isEmpty())
        {
            --top;
        }
        else
        {
            cout << "Stack Underflow!" << endl;
        }
    }

    char peek() const
    {
        if (!isEmpty())
        {
            return str[top];
        }
        else
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }
    }

    int precedence(char op)
    {
        if (op == '+' || op == '-')
        {
            return 1;
        }
        else if (op == '*' || op == '/')
        {
            return 2;
        }
        else if (op == '^')
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }

    string to_postfix(const string& s)
    {
        string postfix;
        Stack stack;
        bool lastWasOperand = false;

        for (char c : s)
        {
            if (isspace(c))
            {
                continue; // skip white spaces
            }
            if (isdigit(c))
            {
                if(lastWasOperand)
                {
                    cout << "Error: invalid number of operands" << endl;
                    return "";
                }
                postfix += c;
                lastWasOperand = true;
            }
            else if (c == '(')
            {
                stack.push(c);
                lastWasOperand = false;
            }
            else if (c == ')')
            {
                while (!stack.isEmpty() && stack.peek() != '(')
                {
                    postfix += stack.peek();
                    stack.pop();
                }
                if(stack.isEmpty())
                {
                    cout << "Error: Invalid parentheses" << endl;
                    return "";
                }
                stack.pop(); // remove '('
                lastWasOperand = false;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
            {
                if(!lastWasOperand && (c == '+' || c == 'i'))
                {
                    cout << "Error: invalid number of operands" << endl;
                    return "";
                }
                while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c))
                {
                    postfix += stack.peek();
                    stack.pop();
                }
                stack.push(c);
                lastWasOperand = false;
            }
            else
            {
                cout << "Error: Invalid character '" << c << "' in the expression" << endl;
                return "";
            }
        }

        while (!stack.isEmpty())
        {
            if(stack.peek() == '(')
            {
                cout << "Error: Invalid Parentheses" << endl;
                return "";
            }
            postfix += stack.peek();
            stack.pop();
        }

        return postfix;
    }

    string print_postfix(string s)
    {
        if (!s.empty())
        {
            cout << "Postfix Expression: " << s << endl;
        }
        return s;
    }

    double evaluatePostfix(string s)
    {
        Stack stack;

        for (char c : s)
        {
            if (isdigit(c))
            {
                stack.push(c - '0');
            }
            else
            {
                double operand2 = stack.peek();
                stack.pop();
                double operand1 = stack.peek();
                stack.pop();
                double result;
                switch (c)
                {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        result = operand1 / operand2;
                        break;
                    case '^':
                        result = pow(operand1, operand2);
                        break;
                }
                stack.push(result);
            }
        }

        return stack.peek();
    }

};

int main()
{
    Stack stack;
    string infixExpression;
    int choice;
    cout << "+---------------------------------------+\n| WELCOME TO THE STACK-BASED CALCULATOR |\n+---------------------------------------+" << endl;
    do {
        cout << "+----------------------------+\n";
        cout << "| Menu:                      |" << endl;
        cout << "| 1. Calculate expression    |" << endl;
        cout << "| 2. Quit                    |" << endl;
        cout << "+----------------------------+\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // consume the newline character left in the input buffer

        switch (choice)
        {
        case 1:
        {
            cout << "Enter an Infix Expression: ";
            getline(cin, infixExpression);
            string postfixExp = stack.to_postfix(infixExpression);
            if (!postfixExp.empty())
            {
                stack.print_postfix(postfixExp);
                double result = stack.evaluatePostfix(postfixExp);
                cout << "Result: " << fixed << setprecision(3) << result << endl;
            }
            break;
        }
        case 2:
        {
            cout << "Goodbye!" << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice!" << endl;
        }
        }
    } while (choice != 2);

    return 0;
}
