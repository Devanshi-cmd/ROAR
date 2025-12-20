#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"
#include "optimizer.h"
#include "loss.h"

class Model {
public:
    virtual void train(
        Matrix X,
        Matrix y,
        Optimizer* optimizer,
        Loss* loss,
        int epochs,
        bool verbose = true
    ) = 0;

    virtual Matrix predict(Matrix X) = 0;

    virtual const char* getName() const = 0;

    virtual ~Model() {}
};

#endif
