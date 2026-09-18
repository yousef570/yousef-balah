#include <iostream>
using namespace std;

int main() {
    char op; 
    double n1, n2;
    double result = 0; 

    

    cout << "Enter two numbers: ";
    cin >> n1  >> op >> n2;

    if (op == '+') {
        result = n1 + n2;
    } else if (op == '-') {
        result = n1 - n2;
    } else if (op == '*') {
        result = n1 * n2;   
    } else if (op == '/') {
        if (n2 != 0) {
            result = n1 / n2;
        } else {
            cout << "Error: Division by zero!" << endl;
            return 1;
        }
    } else {
        cout << "Error: Invalid operator!" << endl;
        return 1;
    }

    cout << "Result: " << result << endl;
    return 0;
}