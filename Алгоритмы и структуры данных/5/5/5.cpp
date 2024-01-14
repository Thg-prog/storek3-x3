#include <iostream>
#include <string>
#include "Stack.h" 

class OPZ {
    std::string str;
    std::string result;
public:
    OPZ();
    OPZ(std::string _str);
    void set(std::string _str);
    void convert();
    std::string getResult();
    int calculate(Stack& st);
};

OPZ::OPZ() {
    str = "";
}

OPZ::OPZ(std::string _str) {
    str = _str;
}

void OPZ::set(std::string _str) {
    str = _str;
}

void OPZ::convert() {
    result = "";
    Stack signs;
    for (int i = 0; i < (int)str.size(); i++) {
        if (isalpha(str[i])) {
            result += str[i];
        }
        else if (str[i] == '-' || str[i] == '+' || str[i] == '*' || str[i] == '/') {
            signs.add((int)str[i]);
        }
        else if (str[i] == ')') {
            char value = (char)signs.deleteStart();
            result += value;
        }
    }
}

std::string OPZ::getResult() {
    return result;
}

int OPZ::calculate(Stack& st) {
    Stack s;
    int size = st.size();
    for (int i = 0; i < size; i++) {
        s.add(st.deleteStart());
    }
    Stack tmp;
    for (int i = 0; i < (int)result.size(); i++) {
        if (isalpha(result[i])) {
            tmp.add(s.deleteStart());
        }
        else if (result[i] == '-' || result[i] == '+' || result[i] == '*' || result[i] == '/') {
            int b = tmp.deleteStart();
            int a = tmp.deleteStart();
            int val = 0;
            if (result[i] == '-')
                val = a - b;
            else if (result[i] == '+')
                val = a + b;
            else if (result[i] == '*')
                val = a * b;
            else if (result[i] == '/')
                val = a / b;
            tmp.add(val);
        }
    }
    return tmp.deleteStart();
}


int main()
{
    OPZ opz;
    std::cout << "0-to exit; 1-to set value; 2-to convert value; 3-to print result" << std::endl;
    int value;
    while (true) {
        std::cout << "Enter value: ";
        std::cin >> value;
        if (value == 1) {
            std::cout << "Enter the string: ";
            std::string str;
            std::cin >> str;
            opz.set(str);
        }
        else if (value == 2) opz.convert();
        else if (value == 3) {
            std::cout << "Would you like to set values?(YES/NO): ";
            std::string s;
            std::cin >> s;
            for (int i = 0; i < (int)s.size(); i++) s[i] = tolower(s[i]);
            std::string result = opz.getResult();
            if (s == "yes") {
                Stack st;
                int num = 0;
                for (int i = 0; i < (int)result.size(); i++) {
                    if (isalpha(result[i])) {
                        std::cout << result[i] << "=";
                        std::cin >> num;
                        st.add(num);
                    }
                }
                int answer = opz.calculate(st);
                std::cout << answer << std::endl;
            }
            else
                std::cout << "Answer: " << result << std::endl;
        }
        else if (value == 0) break;
    }
}
