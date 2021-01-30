//==============================================================================
// Copyright (C) 2023 Thomas Braure.
//
// This file is part of ble-client.
//
// ble-client is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ble-client is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ble-client. If not, see <https://www.gnu.org/licenses/>.
//==============================================================================

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Layouts

Pane {
    property alias itemDelegate: itemDelegate
    property alias dateLabel: dateLabel
    property alias messageLabel: messageLabel
    property alias detailsPane: detailsPane
    property alias deviceAddressLayout: deviceAddressLayout
    property alias deviceAddressLabel: deviceAddressLabel
    property alias deviceNameLayout: deviceNameLayout
    property alias deviceNameLabel: deviceNameLabel
    property alias serviceUuidLayout: serviceUuidLayout
    property alias serviceUuidLabel: serviceUuidLabel
    property alias serviceNameLayout: serviceNameLayout
    property alias serviceNameLabel: serviceNameLabel
    property alias characteristicUuidLayout: characteristicUuidLayout
    property alias characteristicUuidLabel: characteristicUuidLabel
    property alias characteristicNameLayout: characteristicNameLayout
    property alias characteristicNameLabel: characteristicNameLabel
    property alias descriptorUuidLayout: descriptorUuidLayout
    property alias descriptorUuidLabel: descriptorUuidLabel
    property alias descriptorNameLayout: descriptorNameLayout
    property alias descriptorNameLabel: descriptorNameLabel
    property alias valueLayout: valueLayout
    property alias valueLabel: valueLabel
    property alias errorMessageLayout: errorMessageLayout
    property alias errorMessageLabel: errorMessageLabel
    property alias mouseArea: mouseArea

    padding: 0
    contentWidth: itemDelegate.width

    ItemDelegate {
        id: itemDelegate
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        hoverEnabled: true
        text: " "

        RowLayout {
            anchors.fill: parent.contentItem
            spacing: 12

            Label {
                id: dateLabel
            }

            Label {
                id: messageLabel
            }

            Item {
                Layout.fillWidth: true
            }
        }
    }

    Pane {
        id: detailsPane
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: itemDelegate.bottom
        topPadding: -6

        GridLayout {
            Layout.fillWidth: true
            rowSpacing: 0
            columnSpacing: 12
            rows: 6
            columns: 3

            Item {
                Layout.rowSpan: 6
                implicitWidth: dateLabel.width
            }

            RowLayout {
                id: deviceAddressLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Device Address:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: deviceAddressLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: deviceNameLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Device Name:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: deviceNameLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: serviceUuidLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Service Uuid:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: serviceUuidLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: serviceNameLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Service Name:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: serviceNameLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: characteristicUuidLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Characteristic Uuid:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: characteristicUuidLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: characteristicNameLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Characteristic Name:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: characteristicNameLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: descriptorUuidLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Descriptor Uuid:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: descriptorUuidLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: descriptorNameLayout
                Layout.fillWidth: true
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Descriptor Name:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: descriptorNameLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: valueLayout
                Layout.fillWidth: true
                Layout.columnSpan: 2
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Value:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: valueLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }

            RowLayout {
                id: errorMessageLayout
                Layout.fillWidth: true
                Layout.columnSpan: 2
                spacing: 6

                Label {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                    text: qsTr("Error Message:")
                    font.weight: Font.Light
                    font.pointSize: 10
                }

                Label {
                    id: errorMessageLabel
                    Layout.fillWidth: true
                    font.pointSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: itemDelegate
    }
}
