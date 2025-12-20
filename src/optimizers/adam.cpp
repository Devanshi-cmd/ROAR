#include "adam.h"
#include <cmath>

Adam::Adam(double lr) : learning_rate(lr) {
    m = Matrix(0, 0);
    v = Matrix(0, 0);
    m_bias = 0.0;
    v_bias = 0.0;
    t = 0;
}
void Adam::update(Matrix& weights, Matrix gradients) {
    // Initialize on first call
    if (m.rows == 0) {
        m = Matrix(weights.rows, weights.cols);
        v = Matrix(weights.rows, weights.cols);
        m.fillZeros();
        v.fillZeros();
    }
    
    t++;
    
    double beta1 = 0.9;
    double beta2 = 0.999;
    double epsilon = 1e-8;
    
    for (int i = 0; i < weights.rows; i++) {
        for (int j = 0; j < weights.cols; j++) {
            double g = gradients.get(i, j);
            
            // Update first moment
            double m_val = beta1 * m.get(i, j) + (1 - beta1) * g;
            m.set(i, j, m_val);
            
            // Update second moment
            double v_val = beta2 * v.get(i, j) + (1 - beta2) * g * g;
            v.set(i, j, v_val);
            
            // Bias correction
            double m_hat = m_val / (1 - pow(beta1, t));
            double v_hat = v_val / (1 - pow(beta2, t));
            
            // Update weight
            double w = weights.get(i, j);
            weights.set(i, j, w - learning_rate * m_hat / (sqrt(v_hat) + epsilon));
        }
    }
}

void Adam::updateBias(double& bias, double gradient) {
    t++;
    
    double beta1 = 0.9;
    double beta2 = 0.999;
    double epsilon = 1e-8;
    
    // Update moments
    m_bias = beta1 * m_bias + (1 - beta1) * gradient;
    v_bias = beta2 * v_bias + (1 - beta2) * gradient * gradient;
    
    // Bias correction
    double m_hat = m_bias / (1 - pow(beta1, t));
    double v_hat = v_bias / (1 - pow(beta2, t));
    
    // Update bias
    bias = bias - learning_rate * m_hat / (sqrt(v_hat) + epsilon);
}

void Adam::reset() {
    m =Matrix(0, 0);
    v = Matrix(0, 0);
    m_bias = 0;
    v_bias = 0;
    t = 0;
}
const char* Adam::getName() {
    return "Adam";
}
