#ifndef LOSS_H
#define LOSS_H

#include "matrix.h"

class Loss {
public:
    virtual double compute(Matrix predictions, Matrix actual) = 0;
    virtual Matrix gradient(Matrix predictions, Matrix actual) = 0;
    virtual const char* getName()=0;
    virtual ~Loss(){}
};

#endif