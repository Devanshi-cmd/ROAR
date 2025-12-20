#ifndef MSE_H
#define MSE_H

#include "loss.h"

class MSE : public Loss {
public:
    double compute(Matrix predictions, Matrix actual);
    Matrix gradient(Matrix predictions, Matrix actual);
    const char* getName() { return "MSE"; }
};

#endif