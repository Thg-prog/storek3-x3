#include <iostream>

class Matrix {
    double** ar;
    int size;
    Matrix getNewMatrix(double** _ar, int _size, int pos) const;
    double getDeterminant(const Matrix& m) const;
    public:
    Matrix(double** _ar, int _size);
    double getDeterminant() const;
    ~Matrix();
};


Matrix::Matrix(double** _ar, int _size) {
    size = _size;
    ar = new double*[size];
    for (int i = 0; i < size; i++) {
        ar[i] = new double[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ar[i][j] = _ar[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < size; i++) {
        delete[] ar[i];
    }
    delete[] ar;
}

double Matrix::getDeterminant() const {
    return getDeterminant(*this);
}

Matrix Matrix::getNewMatrix(double** _ar, int _size, int pos) const {
    int newSize = _size-1;
    double** _arr = new double*[newSize];
    for (int i = 0; i < newSize; i++) _arr[i] = new double[newSize];
    for (int i = 1; i < _size; i++) {
        for (int j = 0; j < pos; j++) {
            _arr[i-1][j] = _ar[i][j]; 
        }
    }
    for (int i = 1; i < _size; i++) {
        for (int j = pos+1; j < _size; j++) {
            _arr[i-1][j-1] = _ar[i][j]; 
        }
    }
    Matrix m(_arr, newSize);
    for (int i = 0; i < newSize; i++) delete[] _arr[i];
    delete[] _arr;
    return m;
}

double Matrix::getDeterminant(const Matrix& m) const {
    if (m.size == 2) {
        return m.ar[0][0] * m.ar[1][1] - m.ar[0][1] * m.ar[1][0];
    }
    double det = 0.0;
    for (int i = 0; i < m.size; i++) {
        double local_det = m.ar[0][i] * getDeterminant(getNewMatrix(m.ar, m.size, i));
        if (i % 2 != 0) {
            local_det *= -1;
        }
        det += local_det;
    }
    return det;
}

int main() {
    int n = 4;
    double** ar = new double*[n];
    for (int i = 0; i < n; i++) {
        ar[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ar[i][j] = i + j;
        }
    }
    Matrix m(ar, n);
    std::cout << m.getDeterminant();
    for (int i = 0; i < n; i++) {
        delete[] ar[i];
    } 
    delete[] ar;
    return 0;
}