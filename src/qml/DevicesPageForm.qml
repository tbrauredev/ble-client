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
    property alias refreshButton: refreshButton
    property alias devicesListView: devicesListView
    property alias refreshIndicator: refreshIndicator

    padding: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            Layout.fillWidth: true
            padding: 24
            bottomPadding: 12

            ColumnLayout {
                spacing: 24

                Label {
                    text: qsTr("Bluetooth devices")
                    font.pointSize: 24
                }

                RowLayout {
                    spacing: 12

                    Button {
                        id: refreshButton
                        icon.source: "qrc:/icons/autorenew.png"
                        hoverEnabled: true
                        display: AbstractButton.IconOnly
                    }

                    Label {
                        text: qsTr("Refresh available devices")
                    }

                    BusyIndicator {
                        id: refreshIndicator
                    }
                }
            }
        }

        Pane {
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 0

            ListView {
                id: devicesListView
                anchors.fill: parent
                currentIndex: -1
                clip: true

                ScrollBar.vertical: ScrollBar {}

                header: Pane {
                    padding: 24
                    topPadding: 12
                    bottomPadding: 12

                    Label {
                        text: qsTr("Available devices")
                        font.pointSize: 16
                    }
                }

                footer: Item { implicitHeight: 12 }

                add: Transition {
                    PropertyAnimation {
                        property: "opacity"
                        from: 0
                        to: 1
                        duration: 300
                    }
                }

                populate: Transition {
                    PropertyAnimation {
                        property: "opacity"
                        from: 0
                        to: 1
                        duration: 300
                    }
                }
            }
        }
    }
}
