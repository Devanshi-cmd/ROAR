// src/main.cpp
#include <iostream>
#include <random>
#include "matrix.h"
#include "mse.h"
#include "mae.h"
#include "adam.h"
#include "linear_regression.h"

using namespace std;

void testLinearRegression() {
    cout << "\n╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║         Linear Regression Demo                       ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝\n" << endl;
    
    int n = 100;
    Matrix X(n, 1);
    Matrix y(n, 1);

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> noise(0.0, 0.5);

    for (int i = 0; i < n; i++) {
        double x_val = i / 10.0;
        X.set(i, 0, x_val);
        y.set(i, 0, 2.0 * x_val + 3.0 + noise(gen));
    }

    cout << "Dataset created: y = 2*x + 3 (with noise)" << endl;
    cout << "Expected: weight ≈ 2.0, bias ≈ 3.0\n" << endl;

    LinearRegression model(1);

    cout << "\n--- Testing Adam Optimizer ---" << endl;
    Adam adam(0.01);
    MSE mse;
    model.train(X, y, &adam, &mse, 1000);

    cout << "\nLearned Parameters:" << endl;
    cout << "Weight: " << model.weights.get(0, 0) << endl;
    cout << "Bias: " << model.bias << endl;

    Matrix test_X(1, 1);
    test_X.set(0, 0, 5.0);
    Matrix pred = model.predict(test_X);

    cout << "\nTest Prediction:" << endl;
    cout << "Input: x = 5.0" << endl;
    cout << "Predicted: y = " << pred.get(0, 0) << endl;
    cout << "Expected: y = 13.0" << endl;
}

void compareOptimizers() {
    cout << "\n╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║         Comparing Optimizers                         ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝\n" << endl;

    int n = 100;
    Matrix X(n, 1);
    Matrix y(n, 1);

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> noise(0.0, 0.5);

    for (int i = 0; i < n; i++) {
        double x_val = i / 10.0;
        X.set(i, 0, x_val);
        y.set(i, 0, 2.0 * x_val + 3.0 + noise(gen));
    }

    MSE loss;

    cout << "\n=== Adam ===" << endl;
    LinearRegression model2(1);
    Adam adam(0.01);
    model2.train(X, y, &adam, &loss, 500, false);
    cout << "Final Loss: " << model2.loss_history.back() << endl;
}

void compareLosses() {
    cout << "\n╔══════════════════════════════════════════════════════╗" << endl;
    cout << "║         Comparing Loss Functions                     ║" << endl;
    cout << "╚══════════════════════════════════════════════════════╝\n" << endl;

    int n = 100;
    Matrix X(n, 1);
    Matrix y(n, 1);

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> noise(0.0, 0.5);

    for (int i = 0; i < n; i++) {
        double x_val = i / 10.0;
        X.set(i, 0, x_val);
        y.set(i, 0, 2.0 * x_val + 3.0 + noise(gen));
    }

    Adam optimizer(0.01);

    cout << "\n=== MSE Loss ===" << endl;
    LinearRegression model1(1);
    MSE mse;
    model1.train(X, y, &optimizer, &mse, 500, false);
    cout << "Final Loss: " << model1.loss_history.back() << endl;

    cout << "\n=== MAE Loss ===" << endl;
    LinearRegression model2(1);
    MAE mae;
    optimizer.reset();
    model2.train(X, y, &optimizer, &mae, 500, false);
    cout << "Final Loss: " << model2.loss_history.back() << endl;
}

int main() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║        ROAR ML Library - Modular Implementation            ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;

    testLinearRegression();
    compareOptimizers();
    compareLosses();

    cout << "\n\n✨ All tests completed successfully! ✨\n" << endl;
    return 0;
}
