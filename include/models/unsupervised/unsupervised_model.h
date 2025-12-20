#ifndef UNSUPERVISED_MODEL_H
#define UNSUPERVISED_MODEL_H

#include "model.h"

class UnsupervisedModel : public Model {
public:
    virtual void fit(Matrix X) = 0;
    virtual ~UnsupervisedModel() {}
};

#endif
