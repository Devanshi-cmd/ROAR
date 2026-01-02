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

QSurfaceDataArray *generateDummyData();



Bridge::Bridge(QObject *parent){ //Constructor for bridge obj
    m_currentEpoch = 0;
    m_currentLoss = 0.0;

    m_dataProxy = new QSurfaceDataProxy(); //create array for surface data
    m_dataProxy->resetArray(generateDummyData()); //fill the array with dummy data
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


QSurfaceDataArray *generateDummyData() { //for dummy data
    QSurfaceDataArray *data = new QSurfaceDataArray;
    
    // Example: 100 rows (Z/bias), 100 columns (X/weight)
    for (int row = 0; row < 100; row++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow;
        
        for (int col = 0; col < 100; col++) {
            // Center the grid at (50, 50) and scale
            float x = (col - 50) * 0.3;  // X-axis (weight)
            float z = (row - 50) * 0.3;  // Z-axis (bias)
            
            // Simple paraboloid: y = x² + z²
            float y = (x*x + z*z)* 0.1;         // Y-axis (loss)

            
            (*newRow) << QSurfaceDataItem(QVector3D(x, y, z));
        }
        
        *data << newRow;
    }
    
    return data;
}