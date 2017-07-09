import QtQuick 2.0

Item {
    Image {
        id: bkStimulation
        visible: true
        anchors.fill: parent
        source: "image/stimulation.png"
    }

    Rectangle
    {

        x: 940
        y: 562
        width: 82
        height: 66
        visible: true
        color: "transparent"

        Image {
            visible: true
            anchors.fill: parent
            source: "image/ok_btn.png"
        }


        MouseArea {
            anchors.fill: parent
            onClicked:
            {
                monitoringRoot.handleOKClicked();
            }
        }
    }
}
