#include <iostream>
#include <cmath>
#include <fstream>

void solveSeidel(double** matrix, double* vector, double* startVector, double tolerance, int size) {
    double x[size];
    double error = tolerance + 1;

    while (error > tolerance) {
        for (int i = 0; i < size; i++) {
            double sum = 0.0;
            for (int j = 0; j < size; j++) {
                if (j != i) {
                    sum += matrix[i][j] * x[j];
                }
            }
            x[i] = (vector[i] - sum) / matrix[i][i];
        }

        error = 0.0;
        for (int i = 0; i < size; i++) {
            error += std::abs(x[i] - startVector[i]);
            startVector[i] = x[i];
        }

    }

    std::cout << "Answer: ";
    for (int i = 0; i < 3; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

}

int main() {/* = {
        {4, -1, 2},
        {1, 6, -1},
        {2, 1, 5}
    };*/

    std::ifstream filein;
    filein.open("./text.txt");
    int size;
    filein >> size;
    double** matrix = new double*[size];
    for(int i = 0; i < size; i ++){
        matrix[i] = new double[size];
    }
    double vector[size];
    for(int i = 0; i < size; i++){
        for(int j = 0; j <= size; j++){
            if(j == size){
                filein >> vector[i] ;
            }else filein >> matrix[i][j];
        }
    }


    double startVector[size];
    for(int i = 0; i < size; i++){
        startVector[i] = 0;
    }
    double tolerance = 0.0001;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
        std::cout << matrix[i][j] << " ";
        std::cout << "\n";
    }

    solveSeidel(matrix, vector, startVector, tolerance, size);

    return 0;
}