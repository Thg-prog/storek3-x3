#include <iostream>
#include <fstream>
#include <string>
#include "life.h"


int main()
{
    std::ifstream file1("in.txt");
    int n, m, p;
    file1 >> n >> m >> p;
    char** ar = new char* [n];
    for (int i = 0; i < n; i++) {
        ar[i] = new char[m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file1 >> ar[i][j];
        }
    }
    file1.close();
    
    Field f;
    f.ar = ar;
    f.n = n;
    f.m = m;
    Life life(f);
    for (int i = 0; i < p; i++) {
        life.birth();
        life.death();
    }
    Field _f = life.get();


    std::ofstream file2("out.txt");
    for (int i = 0; i < _f.n; i++) {
        for (int j = 0; j < _f.m; j++) {
            file2 << _f.ar[i][j];
        }
        file2 << "\n";
    }
    for (int i = 0; i < n; i++)
        delete[]ar[i];
    delete[]ar;
}