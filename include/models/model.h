#ifndef MODEL_H
#define MODEL_H

#include "matrix.h"
#include "optimizer.h"
#include "loss.h"
#include <functional>

class Model {
public:
    virtual void train(
        Matrix X,
        Matrix y,
        Optimizer* optimizer,
        Loss* loss,
        int epochs,
        bool verbose = true,
        std::function<void(int,double)> callback = NULL //using std::function so this function can acess member variables
        //Call back function is like giving phone number (Function pointer), will call you when something happnes
    ) = 0;

    virtual Matrix predict(Matrix X) = 0;

    virtual const char* getName() const = 0;

    virtual ~Model() {}
};

#endif
