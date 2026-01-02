cmake_minimum_required(VERSION 3.16)
project(ROAR)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Concurrent DataVisualization) #all packages we are using in Qt

set(CMAKE_AUTOMOC ON) #cmake will need to generate some code itself

set(SOURCES
    main.cpp
    bridge.cpp
    ../src/models/supervised/linear_regression.cpp
    ../src/core/matrix.cpp
    ../src/losses/mae.cpp
    ../src/losses/mse.cpp
    ../src/optimizers/adam.cpp
    ../src/optimizers/sgd.cpp
)

include_directories( #header files
    ../include/core
    ../include/factory
    ../include/losses
    ../include/models
    ../include/models/supervised
    ../include/models/unsupervised
    ../include/optimizers
    ../include/utils
)

set(QML_FILES
    main.qml
    plot3D.qml
)

qt_add_executable(ROAR_GUI #create a executable with all source files
    ${SOURCES}
)

qt_add_qml_module(ROAR_GUI #add qml files to executables
    URI ROAR #Uniform Resource identifier, used to identify our module, when we import
    VERSION 0.1
    QML_FILES ${QML_FILES}
)

target_link_libraries(ROAR_GUI PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Concurrent
    Qt6::DataVisualization
)
