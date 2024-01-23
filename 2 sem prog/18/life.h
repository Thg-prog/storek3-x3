#pragma once

struct Field {
    int n;
    int m;
    char** ar;
};

class Life {
    Field f;
    char** previous_ar;
public:
    Life();
    Life(const Life& l);
    Life(Life&& l);
    Life(Field _f);
    Life(int n, int m, char** ar);
    void set(Field _f);
    void set(int n, int m, char** ar);
    Field get() const;
    int getNumberOfLiving(int row, int column) const;
    void birth();
    void death();
    ~Life();
};

inline Field Life::get() const {
    return f;
}