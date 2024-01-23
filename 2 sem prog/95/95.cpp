#include <iostream>
#include <fstream>
#include "robot.h"

int main()
{
    std::ifstream file1;
    file1.open("in.txt");
    char* str = new char[200];
    file1 >> str;
    file1.close();
    Robot r;
    for (int i = 0; i < 200; i++) {
        if (str[i] == 'S') r.straight();
        else if (str[i] == 'L') r.turnLeft();
        else if (str[i] == 'R') r.turnRight();
    }
    std::ofstream file2;
    file2.open("out.txt");
    file2 << r.getCount();
    file2.close();
    delete[] str;
}
