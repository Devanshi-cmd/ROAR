#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QtConcurrent>
#include <QtDataVisualization/QSurfaceDataProxy> 

class Bridge : public QObject{
    Q_OBJECT //QT's magic macro, must be first line after class decclaration

    Q_PROPERTY(QSurfaceDataProxy* surfaceData READ getSurfaceData CONSTANT); //expose surface data to qml


    Q_PROPERTY(int currentEpoch READ getCurrentEpoch NOTIFY trainingProgressChanged); //how qml talks to cpp
    Q_PROPERTY(double currentLoss READ getCurrentLoss NOTIFY trainingProgressChanged);

public:
    explicit Bridge(QObject *parent = NULL);
    
    //getter functions
    int getCurrentEpoch();

    double getCurrentLoss();

    QSurfaceDataProxy* getSurfaceData() { return m_dataProxy; } //getter to get surface data

    Q_INVOKABLE void startTraining(int modelChoice,int optimizerChoice,int lossChoice,double learningRate,int epochs); //Q_INVOKABLE tells Qt that "QML can directly call this function"

signals:
    //signal declarations
    void trainingProgressChanged(); //this signal will tell Qt to update GUI

private:
    int m_currentEpoch; //naming convention: use m_ for member variables
    double m_currentLoss;

    QSurfaceDataProxy *m_dataProxy; //actual surface data

};

#endif