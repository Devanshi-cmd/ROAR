#include "../../../include/models/supervised/linear_regression.h"
#include <iostream>
#include <iomanip>
using namespace std;

LinearRegression::LinearRegression(int num_features) : weights(num_features, 1) {
    weights.fillRandom();
    bias = 0.0;
}

Matrix LinearRegression::predict(Matrix X) {
    // y_pred = X * weights + bias
    Matrix predictions = X.multiply(weights);
    
    // Add bias to each prediction
    for (int i = 0; i < predictions.rows; i++) {
        predictions.data[i][0] += bias;
    }
    
    return predictions;
}

void LinearRegression::train(Matrix X, Matrix y, Optimizer* optimizer, Loss* loss, int epochs, bool verbose) {
    int n = X.rows;
    
    if (verbose) {
        cout << "\n========== Training Linear Regression ==========" << endl;
        cout << "Dataset: " << n << " samples, " << X.cols << " features" << endl;
        cout << "Optimizer: " << optimizer->getName() << endl;
        cout << "Loss: " << loss->getName() << endl;
        cout << "Epochs: " << epochs << endl;
        cout << "================================================\n" << endl;
    }
    
    // Reset optimizer state
    optimizer->reset();
    loss_history.clear();
    
    for (int epoch = 0; epoch < epochs; epoch++) {
        // Forward pass
        Matrix predictions = predict(X);
        
        // Compute loss
        double loss_val = loss->compute(predictions, y);
        loss_history.push_back(loss_val);
        
        // Backward pass - compute gradients
        Matrix loss_grad = loss->gradient(predictions, y);
        
        // Weight gradient: X^T * loss_grad
        Matrix X_T = X.transpose();
        Matrix weight_grad = X_T.multiply(loss_grad);
        
        // Bias gradient: sum of loss_grad
        double bias_grad = 0.0;
        for (int i = 0; i < loss_grad.rows; i++) {
            bias_grad += loss_grad.get(i, 0);
        }
        
        // Update parameters
        optimizer->update(weights, weight_grad);
        optimizer->updateBias(bias, bias_grad);
        
        // Print progress
        if (verbose && (epoch % 100 == 0 || epoch == epochs - 1)) {
            cout << "Epoch " << setw(4) << epoch 
                 << " | Loss: " << fixed << setprecision(6) << loss_val << endl;
        }
    }
    
    if (verbose) {
        cout << "\n========== Training Complete ==========" << endl;
        cout << "Final Loss: " << loss_history.back() << endl;
        cout << "======================================\n" << endl;
    }
}

double LinearRegression::evaluate(Matrix X, Matrix y, Loss* loss) {
    Matrix predictions = predict(X);
    return loss->compute(predictions, y);
}
const char* LinearRegression::getName() const {
    return "Linear Regression";
}
