#ifndef MATRIX_H
#define MATRIX_H
#include<vector>
using namespace std;

class Matrix{
public:
    vector<vector<double>> data;
    //data 2d array
    int rows;
    int cols;
    Matrix();               

    Matrix(int r,int c);

    double get(int i,int j);
    void set(int i,int j,double value);

    Matrix add(Matrix other);
    Matrix subtract(Matrix other);
    Matrix multiply(Matrix other);
    Matrix multiplyScalar(double scalar);
    Matrix transpose();

    void print();
    double sum();
    double mean();
    void fillRandom(double min = -0.1, double max = 0.1);
    void fillZeros();
    
};

#endif