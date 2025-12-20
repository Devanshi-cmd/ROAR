#include "sgd.h"

void SGD::update(Matrix& weights, Matrix gradients) {
    for (int i = 0; i < weights.rows; i++) {
        for (int j = 0; j < weights.cols; j++) {
            double w = weights.get(i, j);
            double g = gradients.get(i, j);
            weights.set(i, j, w - learning_rate * g);
        }
    }
}

void SGD::updateBias(double& bias, double gradient) {
    bias = bias - learning_rate * gradient;
}
