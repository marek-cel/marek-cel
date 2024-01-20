import Qt 4.7

Flickable {
    width: 640
    height: 360
    contentWidth: 640
    contentHeight: 720

    Rectangle {
        width: 640
        height: 720
        color: "#000"

        Rectangle {
            id: header
            width: 640
            height: 136
            color: "#000"
            anchors.top: parent.top

            Image {
                id: back
                source: "qrc:/gfx/buttonBack.png"

                x: 20
                y: 20

                MouseArea {
                    anchors.fill: parent
                    onClicked: action.triggered()
                }
            }

            Image {
                id: logo
                source: "qrc:/ADI_Touch_296.png"

                x: 272
                y: 20
            }
        }

        Rectangle {
            width: 640
            height: 584
            color: "#000"
            anchors.top: header.bottom

            Text {
                id: info
                color: "#fff"
                anchors.fill: parent
                anchors.margins: 10
                x: 10
                width: 620
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
                text: "<p align=\"center\"><b>ADI Touch version 2.0</b></p> <p>Author: Marek Cel (marekcel@marekcel.pl)</p> <p>For more information visit: http://www.marekcel.pl/</p>"
                font.pointSize: 8
            }
        }

    }

}
