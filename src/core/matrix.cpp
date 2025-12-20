#include "../../include/core/matrix.h"
#include <iostream>
#include <random>
#include <iomanip>
using namespace std;
Matrix::Matrix() {
    rows = 0;
    cols = 0;
}
Matrix::Matrix(int r, int c) {
    rows = r;
    cols = c;
    data.resize(rows);
    for (int i = 0; i < rows; i++) {
        data[i].resize(cols, 0.0);
    }
}

double Matrix::get(int i, int j) {
    return data[i][j];
}

void Matrix::set(int i, int j, double value) {
    data[i][j] = value;
}

Matrix Matrix::add(Matrix other) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::subtract(Matrix other) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::multiply(Matrix other) {
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols; k++) {
                sum += data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

Matrix Matrix::multiplyScalar(double scalar) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

void Matrix::fillRandom(double min, double max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(min, max);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = dis(gen);
        }
    }
}

void Matrix::fillZeros() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0.0;
        }
    }
}

void Matrix::print() {
    cout << "Matrix (" << rows << "x" << cols << "):" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(10) << fixed << setprecision(4) << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

double Matrix::sum() {
    double total = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            total += data[i][j];
        }
    }
    return total;
}

double Matrix::mean() {
    return sum() / (rows * cols);
}