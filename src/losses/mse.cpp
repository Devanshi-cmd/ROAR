#include "../../include/losses/mse.h"

double MSE::compute(Matrix predictions, Matrix actual) {
    double sum = 0.0;

    for (int i = 0; i < predictions.rows; i++) {
        for (int j = 0; j < predictions.cols; j++) {
            double diff = predictions.get(i, j) - actual.get(i, j);
            sum += diff * diff;
        }
    }

    return sum / (predictions.rows * predictions.cols);
}

Matrix MSE::gradient(Matrix predictions, Matrix actual) {
    Matrix grad(predictions.rows, predictions.cols);

    for (int i = 0; i < predictions.rows; i++) {
        for (int j = 0; j < predictions.cols; j++) {
            grad.set(i, j,
                2.0 * (predictions.get(i, j) - actual.get(i, j)) /
                (predictions.rows * predictions.cols)
            );
        }
    }

    return grad;
}
