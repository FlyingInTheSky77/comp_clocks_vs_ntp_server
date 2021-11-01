import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Window {
    width: 760
    height: 450
    minimumWidth: 760
    visible: true
    title: qsTr("comp_clock_vs_ntp_clock")

    Connections {
        target: Ntp_test_in_QML
        function onSendMsg(msg) {
            ti.append( addMsg(msg));
        }
         function onDifferenceSignal(dif) {
            change_interval_button.enabled = true;
            ti.append( addMsg("now the difference is " + dif + " milliseconds or " + dif/1000 + "sec"));
         }
         function onWrongIntervalChangingSignal(prev_interval) {
            change_interval_button.enabled = true;
            ti.append( addMsg("you enter wrong interval. Interval is " + prev_interval + " sec "));
             interval.text = prev_interval;
         }
    }

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 10
        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            Layout.leftMargin: 15
            Layout.rightMargin: 15
            BetterButton {
                id: get_time_difference_with_ntp_server_button
                text: "get time difference with ntp server"
                color: enabled ? "#86a4e5" : "#CED0D4"
                onClicked: {
                    Ntp_test_in_QML.run();
                    get_time_difference_with_ntp_server_button.enabled = false;
                    change_interval_button.enabled = false;
                    this.enabled = false;
                }
            }

            BetterButton {
                id: change_interval_button
                text: "change interval"
                color: enabled ? "#86a4e5" : "#CED0D4"
                onClicked: {
                    Ntp_test_in_QML.setTimerInterval(interval.text);
                }
            }
            Rectangle {
                Layout.fillWidth: true
                radius: 5
                color: "#F4F2F5"
                border.color: "grey"
                border.width: 5
                width:50
                Layout.leftMargin: 15
                Layout.rightMargin: 15
                TextInput
                {
                     id: interval
                     property string placeholderText: "now " + Ntp_test_in_QML.getTimerInterval() +" sec. enter here new number to change"
                     anchors.verticalCenter: parent.verticalCenter
                     leftPadding: 10
                     rightPadding: 10
                     width: parent.width
                     font.pixelSize: defpixelSize
                     clip: true
                     Text
                        {
                            text: interval.placeholderText
                            color: "#aaa"
                                    visible: !interval.text
                                }
                            }
                        }

        }

        LayoutSection {
            Layout.fillHeight: true
            ScrollView {
                id: scrollView
                anchors.fill: parent

                TextArea {
                    id: ti
                    readOnly: true
                    selectByMouse : true
                    font.pixelSize: 14
                    wrapMode: TextInput.WrapAnywhere
                }
            }
        }
        BetterButton {
            id:exit_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Close program"
            color: this.down ? "#6FA3D2" : "#7DB7E9"
            border.color: "#6FA3D2"
            onClicked: {
                Qt.quit();
            }
        }
    }

    Component.onCompleted: {
        ti.text = addMsg("Dmitriy Rodin's application is launched");
        resive_data_button.enabled = true;

    }

    function addMsg(someText)
    {
        return "[" + currentTime() + "] " + someText;
    }

    function currentTime()
    {
        var now = new Date();
        var nowString = ("0" + now.getHours()).slice(-2) + ":"
                + ("0" + now.getMinutes()).slice(-2) + ":"
                + ("0" + now.getSeconds()).slice(-2);
        return nowString;
    }
}
