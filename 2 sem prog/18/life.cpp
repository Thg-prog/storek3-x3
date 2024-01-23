#include <iostream>
#include "life.h"

Life::Life() {
    f.n = 0;
    f.m = 0;
    previous_ar = nullptr;
    f.ar = nullptr;
} 

Life::Life(const Life& l) {
    f.n = l.f.n;
    f.m = l.f.m;
    previous_ar = l.previous_ar;
}

Life::Life(Life&& l) {
    f.n = l.f.n;
    f.m = l.f.m;
    previous_ar = new char* [f.n];
    f.ar = new char* [f.n];
    for (int i = 0; i < f.n; i++) {
        f.ar[i] = new char[f.m];
        previous_ar[i] = new char[f.m];
    }
    for (int i = 0; i < f.n; i++) {
        for (int j = 0; j < f.m; j++) {
            f.ar[i][j] = l.f.ar[i][j];
            previous_ar[i][j] = l.previous_ar[i][j];
        }
    }
    if (l.f.ar != nullptr && l.previous_ar != nullptr) {
        for (int i = 0; i < f.n; i++) {
            delete[]l.f.ar[i];
            delete[]l.previous_ar[i];
        }
        delete[]l.f.ar;
        delete[]l.previous_ar;
    }
}

Life::Life(Field _f) {
    set(_f);
}

Life::Life(int n, int m, char** ar) {
    set(n, m, ar);
}

void Life::set(Field _f) {
    f.n = _f.n;
    f.m = _f.m;
    previous_ar = new char* [f.n];
    f.ar = new char* [f.n];
    for (int i = 0; i < f.n; i++) {
        f.ar[i] = new char[f.m];
        previous_ar[i] = new char[f.m];
    }
    for (int i = 0; i < f.n; i++) {
        for (int j = 0; j < f.m; j++) {
            f.ar[i][j] = _f.ar[i][j];
            previous_ar[i][j] = _f.ar[i][j];
        }
    }
}

void Life::set(int n, int m, char** ar) {
    f.n = n;
    f.m = m;
    previous_ar = new char* [f.n];
    f.ar = new char* [f.n];
    for (int i = 0; i < f.n; i++) {
        f.ar[i] = new char[f.m];
        previous_ar[i] = new char[f.m];
    }
    for (int i = 0; i < f.n; i++) {
        for (int j = 0; j < f.m; j++) {
            f.ar[i][j] = ar[i][j];
            previous_ar[i][j] = ar[i][j];
        }
    }
}

int Life::getNumberOfLiving(int row, int column) const {
    int count = 0;
    int left = column - 1;
    int right = column + 1;
    int up = row - 1;
    int down = row + 1;
    if (up < 0) up = 0;
    if (left < 0) left = 0;
    if (down > f.n - 1) down = f.n - 1;
    if (right > f.m - 1) right = f.m - 1;
    for (int i = up; i <= down; i++) {
        for (int j = left; j <= right; j++) {
            if (previous_ar[i][j] == '*') {
                count++;
            }
        }
    }
    return count;
}

void Life::birth() {
    for (int i = 0; i < f.n; i++) {
        for (int j = 0; j < f.m; j++) {
            if (previous_ar[i][j] == '.') {
                int count = getNumberOfLiving(i, j);
                if (count == 3) {
                    f.ar[i][j] = '*';
                }
            }
        }
    }
}

void Life::death() {
    for (int i = 0; i < f.n; i++) {
        for (int j = 0; j < f.m; j++) {
            if (previous_ar[i][j] == '*') {
                int count = getNumberOfLiving(i, j) - 1;
                if (count < 2 || count > 3) {
                    f.ar[i][j] = '.';
                }
            }
        }
    }
    for (int i = 0; i < f.n; i++) {
        for (int j = 0; j < f.m; j++) {
            previous_ar[i][j] = f.ar[i][j];
        }
    }
}

Life::~Life() {
    for (int i = 0; i < f.n; i++) {
        delete[]f.ar[i];
        delete[]previous_ar[i];
    }
    delete[]f.ar;
    delete[]previous_ar;
}