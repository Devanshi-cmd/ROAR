#ifndef MAE_H
#define MAE_H

#include "loss.h"

class MAE : public Loss {
public:
    double compute(Matrix predictions, Matrix actual) override;
    Matrix gradient(Matrix predictions, Matrix actual) override;

    const char* getName() override {
        return "Mean Absolute Error";
    }
};

#endif
