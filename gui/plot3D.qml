import QtQuick
import QtQuick.Controls
import ROAR
import QtDataVisualization

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: "ROAR 3D Plot"
    
    Surface3D{
        id: surfacePlot
        width: 1280
        height: 720

        aspectRatio: 4.0              // Make it taller (increase Y axis)
        horizontalAspectRatio: 1.0    // Keep X:Z ratio equal

        // theme: Theme3D{
        //     type: Theme3D.ThemeQt
        //     gridEnabled: true
        //     gridLineColor: "black"
        //     windowColor: "white"

        //     labelBackgroundColor: "white"
        //     labelTextColor: "black"
        // }
        

        //Axis Config
        axisX: ValueAxis3D{
            title: "Weight"
            min: -100
            max: 100
        }

        axisZ: ValueAxis3D{
            title: "Bias"
            min: -100
            max: 100
        }

        axisY: ValueAxis3D{
            title: "Loss"
            min: 0
            max: 100
        }

        //DATA series
        Surface3DSeries{
            // id: surfaceSeries
            dataProxy: bridge.surfaceData

            // baseColor: "red"  // Simple single color test

            // Set the color style first
            colorStyle: Theme3D.ColorStyleObjectGradient 

            baseGradient: ColorGradient {
                ColorGradientStop { position: 0.0; color: "blue" }
                ColorGradientStop { position: 1.0; color: "red" }
            }
            //styling
            flatShadingEnabled: false
            drawMode: Surface3Dseries.DrawSurface

        }
    }
}