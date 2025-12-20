#ifndef ADAM_H
#define ADAM_H

#include "../core/matrix.h"
#include "optimizer.h" 
class Adam : public Optimizer {
public:
    Adam(double learning_rate);   
    void update(Matrix& weights, Matrix gradients) override;
    void updateBias(double& bias, double gradient) override;
    void reset() override;
    const char* getName() override;  
private:
    double learning_rate;
    Matrix m, v;
    double m_bias = 0.0;
    double v_bias = 0.0;
    int t = 0;
};

#endif
