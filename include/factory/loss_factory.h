#ifndef LOSS_FACTORY_H
#define LOSS_FACTORY_H

#include "mse.h"
#include "mae.h"

class LossFactory {
public:
    static Loss* create(int choice) {
        switch (choice) {
        case 1:
            return new MSE();
        case 2:
            return new MAE();
        default:
            return nullptr;
        }
    }
};

#endif
