#include <iostream>
#include "robot.h"

Robot::Robot(const Robot& r) {
    count = r.count;
    returnCount = r.returnCount;
    x = r.x;
    y = r.y;
    next_x = r.next_x;
    next_y = r.next_y;
    field = new char* [101];
    for (int i = 0; i < 101; i++) {
        field[i] = new char[101];
    }
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            field[i][j] = r.field[i][j];
        }
    }
}

Robot::Robot(Robot&& r) {
    count = r.count;
    returnCount = r.returnCount;
    x = r.x;
    y = r.y;
    next_x = r.next_x;
    next_y = r.next_y;
    field = new char* [101];
    for (int i = 0; i < 101; i++) {
        field[i] = new char[101];
    }
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            field[i][j] = r.field[i][j];
        }
    }
    for (int i = 0; i < 101; i++) delete[] r.field[i];
    delete[] field;
}

Robot::Robot() {
    field = new char* [101];
    for (int i = 0; i < 101; i++) {
        field[i] = new char[101];
    }
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            field[i][j] = '-';
        }
    }
    count = 0;
    x = 50;
    y = 50;
    next_x = 0;
    next_y = 1;
    returnCount = 0;
}

void Robot::straight() {
    field[y][x] = '#';
    x += next_x;
    y += next_y;
    if (field[y][x] == '-' && returnCount == 0)
        count++;
    else if (field[y][x] == '#' && returnCount == 0) {
        returnCount = count;
        count = 0;
    }
}

void Robot::turnLeft() {
    if (next_x == 1 && next_y == 0) {
        next_x = 0;
        next_y = 1;
    }
    else if (next_x == 0 && next_y == 1) {
        next_x = -1;
        next_y = 0;
    }
    else if (next_x == -1 && next_y == 0) {
        next_x = 0;
        next_y = -1;
    }
    else if (next_x == 0 && next_y == -1) {
        next_x = 1;
        next_y = 0;
    }
}

void Robot::turnRight() {
    if (next_x == 1 && next_y == 0) {
        next_x = 0;
        next_y = -1;
    }
    else if (next_x == 0 && next_y == -1) {
        next_x = -1;
        next_y = 0;
    }
    else if (next_x == -1 && next_y == 0) {
        next_x = 0;
        next_y = 1;
    }
    else if (next_x == 0 && next_y == 1) {
        next_x = 1;
        next_y = 0;
    }
}

Robot::~Robot() {
    for (int i = 0; i < 101; i++)
        delete[] field[i];
    delete[] field;
}
