#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "matrix.h"

// Base class for all optimizers
class Optimizer {
public:
    Optimizer() {}   

    double learning_rate;
    
    Optimizer(double lr) : learning_rate(lr) {}
    virtual ~Optimizer() {}
    
    // Update weights using gradients
    virtual void update(Matrix& weights, Matrix gradients) = 0;
    
    // Update bias using gradient
    virtual void updateBias(double& bias, double gradient) = 0;
    
    // Reset optimizer state (for new training)
    virtual void reset() = 0;
    
    // Get optimizer name
    virtual const char* getName() = 0;
};

#endif