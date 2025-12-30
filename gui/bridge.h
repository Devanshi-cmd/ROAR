#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QtConcurrent>

class Bridge : public QObject{
    Q_OBJECT //QT's magic macro, must be first line after class decclaration

    Q_PROPERTY(int currentEpoch READ getCurrentEpoch NOTIFY trainingProgressChanged); //how qml talks to cpp
    Q_PROPERTY(double currentLoss READ getCurrentLoss NOTIFY trainingProgressChanged);

public:
    explicit Bridge(QObject *parent = NULL);
    //getter functions

    int getCurrentEpoch();

    double getCurrentLoss();

    Q_INVOKABLE void startTraining(); //Q_INVOKABLE tells Qt that "QML can directly call this function"

signals:
    //signal declarations
    void trainingProgressChanged(); //this signal will tell Qt to update GUI

private:
    int m_currentEpoch; //naming convention: use m_ for member variables
    double m_currentLoss;

};

#endif