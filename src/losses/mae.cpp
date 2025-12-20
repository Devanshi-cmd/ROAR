#include "../../include/losses/mae.h"
#include <cmath>

double MAE::compute(Matrix predictions, Matrix targets) {
    int n = predictions.rows;
    double sum = 0.0;
    
    for (int i = 0; i < n; i++) {
        double error = predictions.get(i, 0) - targets.get(i, 0);
        sum += abs(error);
    }
    
    return sum / n;
}

Matrix MAE::gradient(Matrix predictions, Matrix targets) {
    int n = predictions.rows;
    Matrix grad(n, 1);
    
    for (int i = 0; i < n; i++) {
        double error = predictions.get(i, 0) - targets.get(i, 0);
        
        if (error > 0) {
            grad.set(i, 0, 1.0 / n);
        } else if (error < 0) {
            grad.set(i, 0, -1.0 / n);
        } else {
            grad.set(i, 0, 0.0);
        }
    }
    
    return grad;
    
}