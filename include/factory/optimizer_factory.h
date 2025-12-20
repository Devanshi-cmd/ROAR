#ifndef OPTIMIZER_FACTORY_H
#define OPTIMIZER_FACTORY_H

#include "../optimizers/sgd.h"
#include "../optimizers/adam.h"

class OptimizerFactory {
public:
    static Optimizer* create(int choice, double lr) {
        switch (choice) {
        case 1:
            return new SGD(lr);
        case 2:
            return new Adam(lr);
        default:
            return nullptr;
        }
    }
};

#endif
