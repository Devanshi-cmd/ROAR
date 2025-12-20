#include <iostream>
#include <limits>

#include "matrix.h"

#include "model_factory.h"
#include "optimizer_factory.h"
#include "loss_factory.h"

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

/* ---------- Menus ---------- */
int supervisedModelMenu() {
    cout << "\nSupervised Models:\n";
    cout << "1. Linear Regression\n";
    cout << "Enter choice: ";
    int c;
    cin >> c;
    return c;
}

int optimizerMenu() {
    cout << "\nOptimizers:\n";
    cout << "1. SGD\n";
    cout << "2. Adam\n";
    cout << "Enter choice: ";
    int c;
    cin >> c;
    return c;
}

int lossMenu() {
    cout << "\nLoss Functions:\n";
    cout << "1. MSE\n";
    cout << "2. MAE\n";
    cout << "Enter choice: ";
    int c;
    cin >> c;
    return c;
}

/* ---------- Main Program ---------- */
int main() {

    cout << "========================================\n";
    cout << "        ROAR ML – Menu Driven CLI        \n";
    cout << "========================================\n";

    while (true) {

        cout << "\nSelect Model Type:\n";
        cout << "1. Supervised Learning\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";

        int type;
        cin >> type;

        if (!cin) {
            clearInput();
            continue;
        }

        if (type == 2) {
            cout << "\nExiting ROAR ML. Goodbye 👋\n";
            break;
        }

        if (type != 1) {
            cout << "Invalid choice.\n";
            continue;
        }

        /* ---------- Model Selection ---------- */
        int modelChoice = supervisedModelMenu();
        Model* model = ModelFactory::createSupervisedModel(modelChoice, 1);

        if (!model) {
            cout << "Invalid model selection.\n";
            continue;
        }

        /* ---------- Optimizer Selection ---------- */
        int optChoice = optimizerMenu();
        double lr;
        cout << "Enter learning rate: ";
        cin >> lr;

        Optimizer* optimizer = OptimizerFactory::create(optChoice, lr);
        if (!optimizer) {
            cout << "Invalid optimizer.\n";
            delete model;
            continue;
        }

        /* ---------- Loss Selection ---------- */
        int lossChoice = lossMenu();
        Loss* loss = LossFactory::create(lossChoice);
        if (!loss) {
            cout << "Invalid loss.\n";
            delete model;
            delete optimizer;
            continue;
        }

        /* ---------- Dataset ---------- */
        int samples = 100;
        Matrix X(samples, 1);
        Matrix y(samples, 1);
        createLinearDataset(X, y);

        int epochs;
        cout << "\nEnter number of epochs: ";
        cin >> epochs;

        /* ---------- Training ---------- */
        cout << "\n========================================\n";
        cout << "Training Started\n";
        cout << "Model     : " << model->getName() << "\n";
        cout << "Optimizer : " << optimizer->getName() << "\n";
        cout << "Loss      : " << loss->getName() << "\n";
        cout << "========================================\n";

        model->train(X, y, optimizer, loss, epochs, true);

        /* ---------- Prediction ---------- */
        Matrix testX(1, 1);
        testX.set(0, 0, 5.0);

        Matrix pred = model->predict(testX);

        cout << "\nTest Prediction:\n";
        cout << "x = 5.0 → y = " << pred.get(0, 0) << "\n";

        /* ---------- Cleanup ---------- */
        delete model;
        delete optimizer;
        delete loss;

        cout << "\nExperiment completed.\n";
    }

    return 0;
}
