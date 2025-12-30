#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "bridge.h"

int main(int argc, char *argv[]){
    QGuiApplication app(argc,argv); //create Qt application

    QQmlApplicationEngine engine; //create QML engine

    Bridge bridge; //create bridge obj

    engine.rootContext()->setContextProperty("bridge", &bridge); //Expose bridge to QML, so .qml files can acess the object's properties
    engine.load(QUrl(QStringLiteral("qrc:/ROAR/main.qml"))); //load main.qml
    /*
    qrc: means Qt Resource - embedded files
    /qt/qml/ROAR from CMake "URI ROAR"
    */

    if(engine.rootObjects().isEmpty()){ //Error checking, to make sure we actually got the object exposed to QML
        return -1;
    }

    return app.exec(); //start event loop
}