import UdpVideoStream 1.0
import QtMultimedia 5.0
import QtQuick.Controls 2.12
import QtQuick.Window 2.2
import QtQuick 2.12
import StringReceiver 1.0
import StringSender 1.0
import UdpVideoStream 1.0

ApplicationWindow {

    visible: true

    //title of the application
    title: qsTr("Hello World")
    width: 640
    height: 480

    StringReceiver {
        id: test_tcp_rec
        // @disable-check M16
        name: "test"
        // @disable-check M16
        port: "15005"
        // @disable-check M16
        onStringChanged: button.text=rstring
    }

    StringSender {
        id: test_tcp_sender
        // @disable-check M16
        port: "15005"
        // @disable-check M16
        host: "localhost"
        // @disable-check M16
        string: "aa"
    }

    UdpVideoStream {
        id: videoAdapter
        objectName: "VideoAdapter"
    }

    //Content Area

    //a button in the middle of the content area
    Button {
        id: button
        text: qsTr("Hello World")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Button {
        id: button1
        x: -9
        y: -8
        text: qsTr("send A")
        onPressed:  test_tcp_sender.string="A"
        anchors.verticalCenterOffset: -161
        anchors.horizontalCenterOffset: -204
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: button2
        x: -6
        y: 0
        text: qsTr("send B")
        onPressed:  test_tcp_sender.string="B"
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: -161
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: button3
        x: 3
        y: -6
        text: qsTr("send C")
        onPressed:  test_tcp_sender.string="C"

        anchors.horizontalCenterOffset: 204
        anchors.verticalCenterOffset: -161
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: videoUdp
        x: 350
        y: 300
        width: 100
        height: 100

        VideoOutput {
            id: videoPlayer
            anchors.fill: parent
            source: videoAdapter
        }
    }
}


