import QtQuick
import QtQuick.Controls
import ROAR

ApplicationWindow {
    visible: true
    width: 600
    height: 400
    title: "ROAR ML Trainer"
    
    Column {
        anchors {
            centerIn: parent
        }
        spacing: 30
        
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
        
        Button {
            text: "Start Training"
            font.pixelSize: 18
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                bridge.startTraining()
            }
        }
    }
}