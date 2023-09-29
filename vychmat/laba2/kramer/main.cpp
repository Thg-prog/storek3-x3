#include <iostream>
#include <cmath>
#include <fstream>



int calculateMinorDeterminant(int minor[2][2]){
    int result = minor[0][0]*minor[1][1] - minor[0][1]*minor[1][0];
    return result;
}

int calculateDeterminant(int matrix[3][3]) {
    int determinant = 0;

    for (int i = 0; i < 3; i++) {
        int minor[2][2];
        int sign = (i % 2 == 0) ? 1 : -1;

        for (int j = 1; j < 3; j++) {
            int col = 0;
            for (int k = 0; k < 3; k++) {
                if (k != i) {
                    minor[j - 1][col] = matrix[j][k];
                    col++;
                }
            }
        }

        int minorDeterminant = calculateMinorDeterminant(minor);
        determinant += sign * matrix[0][i] * minorDeterminant;
    }

    return determinant;
}

double* kramer(int matrix[3][3], int unknown[3]){
    int temp[3][3];
    double* iks = new double[3];
    int A = calculateDeterminant(matrix);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++)temp[j][k] = matrix[j][k];
        }
        for(int o = 0; o < 3; o++)temp[o][i] = unknown[o];
        iks[i] = ((double)calculateDeterminant(temp))/((double)A);
    } 
    return iks;
}

int main() {
    /*int matrix[3][3] = {
        {3, 1, 2},
        {-1, 2, -3},
        {-2, 1, 1}
    };*/

    /*int unknown[3][1] = {
        {4},
        {1},
        {-2}
    };*/

    std::ifstream filein;
    filein.open("./text.txt");
    int matrix[3][3];
    int vector[3];
    for(int i = 0; i < 3; i++){
        for(int j = 0; j <= 3; j++){
            if(j == 3){
                filein >> vector[i] ;
            }else filein >> matrix[i][j];
        }
    }


    double* x = kramer(matrix, vector);
    for(int i = 0; i < 3; i++)std::cout << "X" << i << " = " << x[i] << std::endl; 

    return 0;
}