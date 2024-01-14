#include <iostream>
#include <string>

using namespace std;

class Comp {
public:
    double a;
    double b;
    void input() {
        cout << "Enter the valid part: ";
        cin >> a;
        cout << "Enter the imaginary part: ";
        cin >> b;
    }
    void print() {
        cout << "Valid part: " << a << "; The imaginary part: " << b << endl;
    }
};

Comp add(Comp c1, Comp c2) {
    Comp answer;
    answer.a = c1.a + c2.a;
    answer.b = c1.b + c2.b;
    return answer;
}

Comp subtraction(Comp c1, Comp c2) {
    Comp answer;
    answer.a = c1.a - c2.a;
    answer.b = c1.b - c2.b;
    return answer;
}

Comp multiply(Comp c1, Comp c2) {
    Comp answer;
    answer.a = c1.a * c2.a - c1.b * c2.b;
    answer.b = c1.a * c2.b + c1.b * c2.a;
    return answer;
}

Comp devide(Comp c1, Comp c2) {
    Comp answer;
    answer.a = (c1.a*c2.a + c1.b*c2.b)/(c2.a*c2.a + c2.b*c2.b);
    answer.b = (c1.b*c2.a - c1.a*c2.b)/(c2.a*c2.a + c2.b*c2.b);
    return answer;
}

int main()
{
    Comp c1;
    cout << "The first number: " << endl;
    c1.input();
    string operation;
    cout << "Enter the action: ";
    cin >> operation;
    Comp c2;
    cout << "The second number: " << endl;
    c2.input();
    Comp answer;
    if (operation == "+") {
        answer = add(c1, c2);
    } else if (operation == "/") {
        answer = devide(c1, c2);
    } else if (operation == "-") {
        answer = subtraction(c1, c2);
    } else if (operation == "*") {
        answer = multiply(c1, c2);
    }
    answer.print();
    return 0;
}
