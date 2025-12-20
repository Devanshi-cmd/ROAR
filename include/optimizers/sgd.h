#ifndef SGD_H
#define SGD_H

#include "optimizer.h"

class SGD : public Optimizer {
public:
    SGD(double lr) : Optimizer(lr) {}
    
    void update(Matrix& weights, Matrix gradients);
    void updateBias(double& bias, double gradient);
    void reset() {}
    const char* getName() { return "SGD"; }
};

#endif
