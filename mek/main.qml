import QtQuick 2.5
import QtQuick.Window 2.2


Window {
    visible: true
    flags: Qt.FramelessWindowHint
    width: 1024
    height: 768

    Image {
        id: bkTitlebar
        visible: true
        x: 0
        y: 0
        width: 1024
        height: 62
        source: "image/titlebar.png"
    }

    Image {
        id: bkStatusbar
        visible: true
        x: 0
        y: 730
        width: 1024
        height: 38
        source: "image/statusbar.png"
    }

    Rectangle
    {
        x: 180
        y: 5
        width: 225
        height: 50
        Image {
            visible: true
            anchors.fill: parent
            source: "image/setup_btn.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                setupView.visible = true
                monitoringView.visible = false
            }
        }
    }

    Rectangle
    {
        x: 400
        y: 7
        width: 225
        height: 50

        Image {
            visible: true
            anchors.fill: parent
            source: "image/monitoring_btn.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                monitoringView.visible = true
                setupView.visible = false
            }
        }
    }

    Setup {
        id: setupView
        visible: true
        x: 0
        y: 62
        width: 1024
        height: 668
    }

    Monitoring
    {
        id: monitoringView
        visible: false
        x: 0
        y: 62
        width: 1024
        height: 668
    }

    Reports
    {
        id: reportView
        visible: false
        x: 0
        y: 62
        width: 1024
        height: 668
    }


}
