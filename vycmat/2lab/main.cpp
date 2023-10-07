#include <iostream>
#include <fstream>
#include "matrix.cpp"
#include "matrix.hpp"

int main() {
    std::vector<std::vector<double>> ar_vector;
    std::ifstream in("input.txt");
    int size;
    in >> size;
    double value;
    int c = 0;
    while (in >> value) {
        if (ar_vector.empty() || ar_vector.back().size() == size + 1) {
            ar_vector.emplace_back();
        }
        ar_vector.back().push_back(value);
        c += 1;
    }
    in.close();

    std::vector<std::vector<double>> ar (size, std::vector<double> (size));
    std::vector<std::vector<double>> buf (size, std::vector<double> (1));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ar[i][j] = ar_vector[i][j];
        }
    }
    for (int i = 0; i < size; i++) buf[i][0] = ar_vector[i][size];
    MatrixVector matrixVector(buf);
    SquareMatrix m(ar);
    std::cout << "Метод Гаусса:\n" << m.getGauss(matrixVector);
    std::cout << "Метод Крамера:\n" << m.getKramer(matrixVector);
    std::cout << "Метод простых итераций:\n" << m.getSimpleIterations(matrixVector);
    return 0;
}