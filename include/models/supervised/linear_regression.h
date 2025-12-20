#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "matrix.h"
#include "optimizer.h"
#include "loss.h"
#include "supervised_model.h"
#include <vector>

class LinearRegression : public SupervisedModel
{
public:
    Matrix weights;
    double bias;
    std::vector<double> loss_history;

    LinearRegression(int num_features);

    // Prediction
    Matrix predict(Matrix X) override;

    // Training
    void train(
        Matrix X,
        Matrix y,
        Optimizer *optimizer,
        Loss *loss,
        int epochs,
        bool verbose = true) override;

    const char *getName() const override;

    // Optional utility (not part of Model interface)
    double evaluate(Matrix X, Matrix y, Loss *loss);
};

#endif
