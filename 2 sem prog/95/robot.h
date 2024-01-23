#pragma once

#include <iostream>

class Robot {
    char** field;
    int count, returnCount;
    int x, y;
    int next_x, next_y;
public:
    Robot();
    Robot(const Robot& r);
    Robot(Robot&& r);
    void straight();
    void turnLeft();
    void turnRight();
    int getCount();
    ~Robot();
};

inline int Robot::getCount() {
    if (returnCount == 0) return -1;
    return returnCount;
}