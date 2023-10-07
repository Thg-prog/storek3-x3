#pragma once

#include <iostream>

class Matrix {
    int size_y;
    protected:
    std::vector<std::vector<double>> ar;
    int size;
    public:
    Matrix(const std::vector<std::vector<double>>& _ar);
    Matrix(const Matrix& m);
    Matrix& operator=(const Matrix& m);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);
    friend Matrix operator+(const Matrix& left, const Matrix& right);
    friend Matrix operator-(const Matrix& left, const Matrix& right);
    friend Matrix operator*(const Matrix& left, const Matrix& right);
    std::vector<std::vector<double>> getAr() const { return ar; };
};

class MatrixVector: public Matrix {
    public:
    MatrixVector(const std::vector<std::vector<double>>& _ar): Matrix(_ar) {}
    MatrixVector(const MatrixVector& m): Matrix(m) {}
    inline double get(const int& pos) const { return ar[pos][0]; }
    inline void setElement(const double& element, const int& pos) { ar[pos][0] = element; }
    MatrixVector& operator=(const Matrix& m);
    friend std::ostream& operator<<(std::ostream& out, const MatrixVector& m);
};

class SquareMatrix: public Matrix {
    SquareMatrix getNewMatrix(const std::vector<std::vector<double>>& _ar, int pos) const;
    double getDeterminant(const SquareMatrix& m) const;
    void getGauss(SquareMatrix& x, MatrixVector& vector, const int& step);
    public:
    SquareMatrix(const std::vector<std::vector<double>>& _ar): Matrix(_ar) {}
    SquareMatrix(const SquareMatrix& m): Matrix(m) {}
    double getDeterminant() const;
    MatrixVector getGauss(const MatrixVector& matrixVector) const;
    MatrixVector getKramer(const MatrixVector& matrixVector) const;
    MatrixVector getSimpleIterations(const MatrixVector& matrixVector) const;
    std::vector<double> solveIterative(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>&b, double epsilon, int maxIterations);
};
