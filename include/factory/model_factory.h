#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include "../models/model.h"
#include "../models/supervised/linear_regression.h"

class ModelFactory {
public:
    static Model* createSupervisedModel(
        int choice,
        int features
    ) {
        switch (choice) {
        case 1:
            return new LinearRegression(features);
        default:
            return nullptr;
        }
    }
};

#endif
