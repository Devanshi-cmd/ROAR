#include "bridge.h"
#include <functional>
#include <cmath> 

#include <iostream>
#include <limits>
#include "matrix.h"
#include "model_factory.h"
#include "optimizer_factory.h"
#include "loss_factory.h"

//the Qt includes (for 3D plot)
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtDataVisualization/QCustom3DItem>

QSurfaceDataArray *generateDummyMLData();


Bridge::Bridge(QObject *parent){ //Constructor for bridge obj
    m_currentEpoch = 0;
    m_currentLoss = 0.0;

    m_dataProxy = new QSurfaceDataProxy(); //create array for surface data
    m_dataProxy->resetArray(generateDummyMLData()); //fill the array with dummy data
}

int Bridge::getCurrentEpoch(){
    return m_currentEpoch;
}

double Bridge::getCurrentLoss(){
    return m_currentLoss;
}

///THE MENUE

using namespace std;

/* ---------- Utility ---------- */
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/* ---------- Dataset ---------- */
void createLinearDataset(Matrix& X, Matrix& y) {
    for (int i = 0; i < X.rows; i++) {
        double x = i * 0.1;
        X.set(i, 0, x);
        y.set(i, 0, 2.0 * x + 3.0);
    }
}

/* ---------- Main Program ---------- */
void Bridge::startTraining(int modelChoice,int optimizerChoice,int lossChoice,double learningRate,int epochs){
    //have to pass the parameters again to the thread
    QtConcurrent::run([this,modelChoice,optimizerChoice,lossChoice,learningRate,epochs](){ //Run this code in different thread

        Model* model = ModelFactory::createSupervisedModel(modelChoice, 1);

        Optimizer* optimizer = OptimizerFactory::create(optimizerChoice, learningRate);
        
        Loss* loss = LossFactory::create(lossChoice);

        /* ---------- Dataset ---------- */
        int samples = 100;
        Matrix X(samples, 1);
        Matrix y(samples, 1);
        createLinearDataset(X, y); //hmmmmm

        /* ---------- Training ---------- */
        cout << "\n========================================\n";
        cout << "Training Started\n";
        cout << "Model     : " << model->getName() << "\n";
        cout << "Optimizer : " << optimizer->getName() << "\n";
        cout << "Loss      : " << loss->getName() << "\n";
        cout << "========================================\n";

        //create lembda that captures 'this'
        auto callback = [this](int epoch, double loss){
            m_currentEpoch = epoch;
            m_currentLoss = loss;
            emit trainingProgressChanged(); //emit signal
        };

        model->train(X, y, optimizer, loss, epochs, true,callback); //to start training model

        /* ---------- Cleanup ---------- */
        delete model;
        delete optimizer;
        delete loss;

        cout << "\nExperiment completed.\n";

        return;
    });
}

// --- SURFACE GENERATION FOR VISUALIZATION ---


 Matrix predict(Matrix X,float weight,float bias) { //TO PREDICT
    // y_pred = X * weights + bias
    Matrix predictions = X.multiplyScalar(weight);
    
    // Add bias to each prediction
    for (int i = 0; i < predictions.rows; i++) {
        predictions.data[i][0] += bias;
    }
    
    return predictions;
}

double compute(Matrix predictions, Matrix targets) { //to calculate loss
    int n = predictions.rows;
    double sum = 0.0;
    
    for (int i = 0; i < n; i++) {
        double error = predictions.get(i, 0) - targets.get(i, 0);
        sum += abs(error);
    }
    
    return sum / n;
}

QSurfaceDataArray *generateDummyMLData() { //for dummy data
    QSurfaceDataArray *data = new QSurfaceDataArray;

     /* ---------- Dataset ---------- */
        int samples = 100;
        Matrix X(samples, 1);
        Matrix y(samples, 1);
        createLinearDataset(X, y); //hmmmmm
    
    // Example: 100 rows (Z/bias), 100 columns (X/weight)
    for (int row = 0; row < 100; row++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow;
        
        for (int col = 0; col < 100; col++) {
            
            float weight = (col-50) * 0.1;  // X-axis (weight) (-5 to 5)
            float bias = (row-50) * 0.1;  // Z-axis (bias)

            Matrix predictions = predict(X,weight,bias);
            
            double loss = compute(predictions, y);  // Y-axis (loss)

            (*newRow) << QSurfaceDataItem(QVector3D(weight, loss, bias));
        }
        
        *data << newRow;
    }
    
    return data;
}

// QVector<QCustom3DItem*> Bridge::getTrajectoryPoints() {//for plotting points
//     QVector<QCustom3DItem*> items;
    
//     // Example: 5 scatter points
//     for (int i = 0; i < 1000; i++) {
//         float x = (rand() % 100 - 50) * 0.2f;
//         float z = (rand() % 100 - 50) * 0.2f;
//         float y = (x*x + z*z) * 0.1f + 5.0f;
        
//         // Create a custom sphere item
//         QCustom3DItem *sphere = new QCustom3DItem();
//         sphere->setMeshFile(":/mesh/meshes/ball.obj");  // Qt's built-in sphere mesh
//         sphere->setPosition(QVector3D(x, y, z));
//         sphere->setScaling(QVector3D(0.03f, 0.03f, 0.03f));  // Size
        
//         items.append(sphere);
//     }
    
//     return items;
// }


Matrix predict2(Matrix X, Matrix weights, double bias) {
    // y_pred = X * weights + bias
    Matrix predictions = X.multiply(weights);
    
    // Add bias to each prediction
    for (int i = 0; i < predictions.rows; i++) {
        predictions.data[i][0] += bias;
    }
    
    return predictions;
}

QVector<QCustom3DItem*> Bridge::getTrajectoryPoints() {//for plotting points
    QVector<QCustom3DItem*> items;

    /* ---------- Dataset ---------- */
    int samples = 100;
    Matrix X(samples, 1);
    Matrix y(samples, 1);
    createLinearDataset(X, y); //hmmmmm

    Matrix weights(1,1);
    double bias;

    weights.fillRandom();
    bias = 0.0;

    double learning_rate = 0.1;

    Optimizer* optimizer = OptimizerFactory::create(2, learning_rate); //adam
    Loss* loss = LossFactory::create(2); //MAE
    
    for (int epoch = 0; epoch < 1000; epoch++) { //for 1000 epoch
        // Forward pass
        Matrix predictions = predict2(X,weights,bias);
        
        // Compute loss
        double loss_val = loss->compute(predictions, y);
        
        // Backward pass - compute gradients
        Matrix loss_grad = loss->gradient(predictions, y);
        
        // Weight gradient: X^T * loss_grad
        Matrix X_T = X.transpose();
        Matrix weight_grad = X_T.multiply(loss_grad);
        
        // Bias gradient: sum of loss_grad
        double bias_grad = 0.0;
        for (int i = 0; i < loss_grad.rows; i++) {
            bias_grad += loss_grad.get(i, 0);
        }
        
        // Update parameters
        optimizer->update(weights, weight_grad);
        optimizer->updateBias(bias, bias_grad);
        
        // Create a custom sphere item
        QCustom3DItem *sphere = new QCustom3DItem();
        sphere->setMeshFile(":/mesh/meshes/ball.obj");  // Qt's built-in sphere mesh
        sphere->setPosition(QVector3D(weights.get(0,0), loss_val, bias));
        sphere->setScaling(QVector3D(0.03f, 0.03f, 0.03f));  // Size
        
        items.append(sphere);
    }
    
    return items;
}