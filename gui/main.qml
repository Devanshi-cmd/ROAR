import QtQuick
import QtQuick.Controls
import ROAR

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: "ROAR ML Trainer"
    
    Column { //whole menue in vertical
        anchors {
            centerIn: parent
        }
        spacing: 30

        //Model selection dropdown
        Row{ //Name of dropdown and the dropdown in a horizontal manner
            spacing: 10

            Label{
                text: "Model:"
                font.pixelSize: 16
            }

            ComboBox{
                id: modelSelector
                model: ["Linear Regression",] //VERY STATIC (Reference: factory) for index
                currentIndex: 0 //Default selection
                width: 200

                onCurrentIndexChanged:{ //log what we have selected
                    console.log("Selected Model:",modelSelector.currentText)
                }
            }
        }

        //Optimizer selection dropdown
        Row{ 
            spacing: 10

            Label{
                text: "Optimizer:"
                font.pixelSize: 16
            }

            ComboBox{
                id: optimizerSelector
                model: ["SGD","ADAM"] //VERY STATIC (Reference: factory) for index
                currentIndex: 0 //Default selection
                width: 200

                onCurrentIndexChanged:{ 
                    console.log("Selected Optimizer:",optimizerSelector.currentText)
                }
            }
        }

        //loss selection dropdown
        Row{ 
            spacing: 10
            Label{
                text: "Loss:"
                font.pixelSize: 16
            }

            ComboBox{
                id: lossSelector
                model: ["MSE","MAE"] //VERY STATIC (Reference: factory) for index
                currentIndex: 0 //Default selection
                width: 200

                onCurrentIndexChanged:{ 
                    console.log("Selected Loss function:",lossSelector.currentText)
                }
            }
        }

        //Learning rate set
        Row{
            spacing: 10
            Label{
                text: "Learning Rate:"
                font.pixelSize: 16
            }

            TextField{
                id: learningRateInput
                placeholderText: "Learning Rate" //label in the box
                text: "0.01" //default value
                width: 200
                validator: DoubleValidator{bottom: 0.0; top:1.0} //the range of learning rate
            }
        }

        //No of epoach
        Row{
            spacing: 10
            Label{
                text: "Epoachs:"
                font.pixelSize: 16
            }

            SpinBox{
                id: epochsInput
                from: 1
                to: 1000000 //range
                value: 1000 //default value
                stepSize: 100 //no to inc or dec on +/-
            }
        }

        Button {
            text: "Start Training"
            font.pixelSize: 18
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                bridge.startTraining(
                    modelSelector.currentIndex +1, //+1 cuz loss/optimizer selector starts from index 1
                    optimizerSelector.currentIndex +1,
                    lossSelector.currentIndex+1,
                    parseFloat(learningRateInput.text),
                    epochsInput.value
                )
            }
        }
        
        Text {
            text: "Epoch: " + bridge.currentEpoch
            font.pixelSize: 24
            color: "cyan"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        Text {
            text: "Loss: " + bridge.currentLoss.toFixed(6)
            font.pixelSize: 24
            color: "lightgreen"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}