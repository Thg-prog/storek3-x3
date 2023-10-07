#include <iostream>
#include <vector>
#include <cmath>
#include "matrix.hpp"

Matrix::Matrix(const std::vector<std::vector<double>>& _ar) {
    ar = _ar;
    size = ar.size();
    size_y = ar[0].size();
}

Matrix::Matrix(const Matrix& m) {
    ar = m.ar;
    size = m.size;
    size_y = m.size_y;
}

Matrix& Matrix::operator=(const Matrix& m) {
    ar = m.ar;
    size = m.ar.size();
    size_y = m.ar[0].size();
    return *this;
}

MatrixVector& MatrixVector::operator=(const Matrix& m) {
    ar = m.getAr();
    size = ar.size();
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    for (int i = 0; i < m.size; i++) {
        for (int j = 0; j < m.size_y; j++) {
            out << m.ar[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

Matrix operator+(const Matrix& left, const Matrix& right) {
    if (left.size == right.size && left.size_y == right.size_y) {
       Matrix m(left);
       for (int i = 0; i < m.size; i++) {
            for (int j = 0; j < m.size_y; j++) {
                m.ar[i][j] += right.ar[i][j];
            }
       }
       return m;
    }
    return left;
}

Matrix operator-(const Matrix& left, const Matrix& right) {
    if (left.size == right.size && left.size_y == right.size_y) {
       Matrix m(left);
       for (int i = 0; i < m.size; i++) {
            for (int j = 0; j < m.size_y; j++) {
                m.ar[i][j] -= right.ar[i][j];
            }
       }
       return m;
    }
    return left;
}

Matrix operator*(const Matrix& left, const Matrix& right) {
    if (left.size_y == right.size) {
        std::vector<std::vector<double>> buf (left.size, std::vector<double> (right.size_y, 0.0));
        for (int i = 0; i < left.size; i++) {
            for (int j = 0; j < right.size_y; j++) {
                buf[i][j] = 0;
                for (int k = 0; k < left.size; k++) {
                    buf[i][j] += left.ar[i][k] * right.ar[k][j];
                }
            }
        }
        return Matrix(buf);
    }
    return left;
}

std::ostream& operator<<(std::ostream& out, const MatrixVector& m) {
    for (int i = 0; i < m.size; i++) {
        out << "x" << i + 1 << " = " << m.ar[i][0] << "\n";
    }
    return out;
}

double SquareMatrix::getDeterminant() const {
    return getDeterminant(*this);
}

SquareMatrix SquareMatrix::getNewMatrix(const std::vector<std::vector<double>>& _ar, int pos) const {
    std::vector<std::vector<double>> _arr;
    for (int i = 1; i < _ar.size(); i++) {
        std::vector<double> local_ar;
        for (int j = 0; j < pos; j++) {
            local_ar.push_back(_ar[i][j]); 
        }
        for (int j = pos+1; j < _ar.size(); j++) {
            local_ar.push_back(_ar[i][j]); 
        }
        _arr.push_back(local_ar);
    }
    return SquareMatrix (_arr);
}

double SquareMatrix::getDeterminant(const SquareMatrix& m) const {
    if (m.size == 2) {
        return m.ar[0][0] * m.ar[1][1] - m.ar[0][1] * m.ar[1][0];
    }
    double det = 0.0;
    for (int i = 0; i < m.size; i++) {
        double local_det = m.ar[0][i] * getDeterminant(getNewMatrix(m.ar, i));
        if (i % 2 != 0) {
            local_det *= -1;
        }
        det += local_det;
    }
    return det;
}

void SquareMatrix::getGauss(SquareMatrix& x, MatrixVector& vector, const int& step) {
    if (step != x.size) {
        for (int i = x.size-1; i >= step+1; i--) {
            double tmp = x.ar[step][step];
            double tmp2 = x.ar[i][step];
            if (tmp != 0 && tmp2 != 0) {
                for (int j = 0; j < x.size; j++) {
                    x.ar[i][j] *= tmp;
                    x.ar[step][j] *= tmp2;
                    x.ar[i][j] -= x.ar[step][j];
                }
                vector.setElement(vector.get(i) * tmp, i);
                vector.setElement(vector.get(step) * tmp2, step);
                vector.setElement(vector.get(i) - vector.get(step), i);
            }
        }
        getGauss(x, vector, step + 1);
    }
}

MatrixVector SquareMatrix::getGauss(const MatrixVector& matrixVector) const {
    SquareMatrix m(*this);
    MatrixVector v(matrixVector);
    int step = 0;
    m.getGauss(m, v, step);
    std::vector<double> buf;
    v.setElement(v.get(m.size-1)/m.ar[m.size-1][m.size-1], m.size-1);
    buf.push_back(v.get(m.size-1));
    for (int i = m.size - 2; i >= 0; i--) {
        for (int j = m.size - 1; j >= i; j--) {
            v.setElement(v.get(i) - buf[m.size-j-1]*m.ar[i][j], i);
        }
        v.setElement(v.get(i)/m.ar[i][i], i);
        buf.push_back(v.get(i));
    }
    return v;
}

MatrixVector SquareMatrix::getKramer(const MatrixVector& matrixVector) const {
    double det = getDeterminant();
    MatrixVector v(matrixVector);
    if (det != 0) {
        for (int i = 0; i < size; i++) {
            SquareMatrix m(*this);
            for (int j = 0; j < m.size; j++) {
                m.ar[j][i] = matrixVector.get(j);
            }
            v.setElement(m.getDeterminant()/det, i);
        }
    }
    return v;
}

MatrixVector SquareMatrix::getSimpleIterations(const MatrixVector& matrixVector) const {
    double eps = 0.000001;
    SquareMatrix mat(*this);
    MatrixVector v(matrixVector);
    std::vector<std::vector<double>> buf(size, std::vector<double>(1));
    for (int i = 0; i < size; i++) {
        buf[i][0] = 1;
    }

    for (int i = 0; i < size; i++) {
        v.setElement(v.get(i) / mat.ar[i][i], i);
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j)
            mat.ar[i][j] /= mat.ar[i][i];
        }
    }

    for (int i = 0; i < mat.size; i++) {
        mat.ar[i][i] = 0;
        for (int j = 0; j < mat.size; j++) {
            mat.ar[i][j] *= -1;
        }
    }

    MatrixVector v_current(buf);
    MatrixVector v_previous(v_current);
    int i = 0;
    double r = 0.0;
    do {
        v_current = mat * v_previous + v;
        std::vector<double> vec;
        r = 0.0;
        for (int i = 0; i < size; i++) {
            r += (fabs(v_current.get(i)-v_previous.get(i)));
        }
        v_previous = v_current;
        i++;
        if (i == 10) break;
    } while(r > eps);

    return v_current;
}
