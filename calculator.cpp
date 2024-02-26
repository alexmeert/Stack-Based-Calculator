#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Stack {
private:
    static const int MAX_SIZE = 100;
    char str[MAX_SIZE];
    int top = -1;

public:
    bool isEmpty() const {
        return top < 0;
    }

    bool isFull() const {
        return top >= MAX_SIZE - 1;
    }

    void push(char val) {
        if (!isFull()) {
            str[++top] = val;
        }
        else {
            cout << "Stack Overflow!" << endl;
        }
    }

    char pop() {
        if (!isEmpty()) {
            return str[top--];
        }
        else {
            cout << "Stack Underflow!" << endl;
            return '\0'; // Return null character b/c of empty stack
        }
    }

    char peek() const {
        if (!isEmpty()) {
            return str[top];
        }
        else {
            cout << "Stack is empty!" << endl;
            return '\0'; // Return null character b/c of empty stack
        }
    }

    bool isMatchingPair(char character1, char character2) {
        if (character1 == '(' && character2 == ')') {
            return true;
        }
        else if (character1 == '{' && character2 == '}') {
            return true;
        }
        else if (character1 == '[' && character2 == ']') {
            return true;
        }
        else {
            return false;
        }
    }

    bool areParenthesisBalanced(const string& exp) 
    {
        for (char c : exp)
        {
            if (c == '{' || c == '(' || c == '[')
            {
                push(c);
            }
            else if (c == '}' || c == ')' || c == ']') 
            {
                if (isEmpty() || !isMatchingPair(pop(), c))
                {
                    return false;
                }
            }
        }

        return isEmpty();
    }

    int precedence(char op)
    {
        if (op == '+' || op == '-')
        {
            return 1;
        }
        else if (op == '*' || op == '/' || op == '%')
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
        // Check for balanced parentheses before starting conversion
        if (!areParenthesisBalanced(s)) {
            cout << "Error: Unbalanced parentheses!" << endl;
            return "";
        }

        string postfix;
        bool lastWasOperand = false;
        
        for (char c : s)
        {
            if (isspace(c))
            {
                continue;
            }
            if (isdigit(c))
            {
                if (lastWasOperand)
                {
                    cout << "Error: Invalid number of operators!" << endl;
                    return "";
                }
                postfix += c;
                lastWasOperand = true;
            }
            else if (c == '(' || c == '[' || c == '{')
            {
                push(c);
                lastWasOperand = false;
            }
            else if (c == ')' || c == ']' || c == '}')
            {
                while (!isEmpty() && peek() != '(' && peek() != '[' && peek() != '{')
                {
                    postfix += pop();
                }
                if (isEmpty() || !isMatchingPair(peek(), c))
                {
                    cout << "Error: Invalid parentheses!" << endl;
                    return "";
                }
                pop();
                lastWasOperand = true;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
            {
                if (!lastWasOperand)
                {
                    cout << "Error: Invalid number of operands!" << endl;
                    return "";
                }
                while (!isEmpty() && precedence(peek()) >= precedence(c))
                {
                    postfix += pop();
                }
                push(c);
                lastWasOperand = false;
            }
            else
            {
                cout << "Error: Invalid character '" << c << "' in the expression!" << endl;
                return "";
            }
        }

        while (!isEmpty() && peek() != '(' && peek() != '[' && peek() != '{')
        {
            postfix += pop();
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

    float evaluatePostfix(string s)
    {
        Stack stack;

        for (char c : s)
        {
            if (isdigit(c))
            {
                stack.push(c - '0'); // Convert character to integer
            }
            else
            {
                float operand2 = stack.pop();
                float operand1 = stack.pop();
                float result;
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
                        result = float(operand1) / operand2;
                        break;
                    case '%':
                        result = fmod(operand1, operand2);
                        break;
                    case '^':
                        result = pow(operand1, operand2);
                        break;
                }
                stack.push(result);
            }
        }

        return stack.pop();
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
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "Enter an Infix Expression: ";
            getline(cin, infixExpression);
            if (stack.areParenthesisBalanced(infixExpression)) {
                string postfixExp = stack.to_postfix(infixExpression);
                if (!postfixExp.empty()) {
                    stack.print_postfix(postfixExp);
                    float result = stack.evaluatePostfix(postfixExp);
                    cout << "Result: " << fixed << setprecision(3) << result << endl;
                }
            }
            else
            {
                cout << "Error: Unbalanced parentheses!" << endl;
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
