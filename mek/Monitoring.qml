import QtQuick 2.0
//import QtCharts 2.0

Item {
    id: monitoringRoot
    signal handleOKClicked();


    Connections {
        target: monitoringRoot
        onHandleOKClicked: {
            stimulationViewAnimationToRight.start()
        }
  }

    Image {
        id: bkMonitoringLeftBar
        x: 0
        y: 0
        width: 171
        height: 672
        visible: true
        source: "image/monitoring_leftbar.png"
    }

    Image {
        id: bkMonitoringRightBar
        x: 817
        y: 0
        width: 207
        height: 672
        visible: true
        source: "image/monitoring_rightbar.png"

        MouseArea {
            x: 0
            y: 380
            width: 45
            height: 240
            onClicked:
            {
                stimulationViewAnimationToLeft.start()
            }
        }
    }

    Stimulation
    {
        id: stimulationView
        visible: true
        x: 1024
        y: 0
        width: 1024
        height: 672

        NumberAnimation {
            id: stimulationViewAnimationToLeft
            target: stimulationView
            properties: "x"
            easing.type: Easing.InOutQuad
            duration: 2000
            to: 0
        }

        NumberAnimation {
            id: stimulationViewAnimationToRight
            target: stimulationView
            properties: "x"
            easing.type: Easing.InOutQuad
            duration: 2000
            to: 1024
        }
    }

    /*
    ChartView {
        id: chart1
        x: 171
        y: 0
        width: 853
        height: 334
        title: "Left"
        antialiasing: true

        LineSeries {
            name: "LineSeries"
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 4.9 }
            XYPoint { x: 3.4; y: 3.0 }
            XYPoint { x: 4.1; y: 3.3 }
        }
    }

    ChartView {
        id: chart2
        x: 171
        y: 335
        width: 853
        height: 334
        title: "right"
        antialiasing: true

        LineSeries {
            name: "LineSeries"
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1.1; y: 2.1 }
            XYPoint { x: 1.9; y: 3.3 }
            XYPoint { x: 2.1; y: 2.1 }
            XYPoint { x: 2.9; y: 4.9 }
            XYPoint { x: 3.4; y: 3.0 }
            XYPoint { x: 4.1; y: 3.3 }
        }
    }
    */
}
