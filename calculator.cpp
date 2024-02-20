#include <iostream>
#include <iomanip> // for setting precision (3 places past the decimal)
#include <string> // for strings

using namespace std;

class Stack
{
    private:

    static const int MAX_SIZE = 100;
    int data[MAX_SIZE];
    int top;

    public:

    int top = -1;

    void push(int val) // adds a new value to the top of the stack
    {
        if(top >= MAX_SIZE -1)
        {
            cout << "Stack Overflow!" << endl;
            return;
        }
        data[++top] = val;
    }

    void pop() // removes the value at the top of the stack
    {
        if(top < 0)
        {
            cout << "Stack Underflow!" << endl;
            return;
        }
        top--;
    }

    int peek() // returns the value at the top of the stack w/o removing it
    {
        if(top < 0)
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return data[top];
    }


    string to_postfix(string s) // transfroms an infix expression to a postfix expression
    {
        
    }

    string print_postfix(string s) // prints the postfix expression
    {

    }

    double evaluatePostfix(string s) // evaluates the postfix expression and returns a floating point answer
    {

    }

};

int main()
{
    string infixExpression;
    cout << "Enter an infix expression: "; // Prompt the user to enter an input in infix format
    getline(cin, infixExpression);
    string postfixExp = to_postfix(infixExpression); // Transform the infix expression to postfix
    print_postfix(postfixExp); // Print the postfix expression
    double result = evaluatePostfix(postfixExp); // Evaluate the postfix expression
    return 0;
}
