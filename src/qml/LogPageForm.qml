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
    property alias exportButton: exportButton
    property alias clearButton: clearButton
    property alias loggerListView: loggerListView

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
                    text: qsTr("Log")
                    font.pointSize: 24
                }

                RowLayout {
                    spacing: 24

                    RowLayout {
                        spacing: 6

                        Button {
                            id: exportButton
                            icon.source: "qrc:/icons/download.png"
                            hoverEnabled: true
                            display: AbstractButton.IconOnly
                        }

                        Label {
                            text: qsTr("Export log")
                        }
                    }

                    RowLayout {
                        spacing: 6

                        Button {
                            id: clearButton
                            icon.source: "qrc:/icons/delete.png"
                            hoverEnabled: true
                            display: AbstractButton.IconOnly
                        }

                        Label {
                            text: qsTr("Clear log")
                        }
                    }
                }
            }
        }

        Pane {
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 0

            ListView {
                id: loggerListView
                anchors.fill: parent
                currentIndex: -1
                clip: true

                ScrollBar.vertical: ScrollBar {}

                header: Pane {
                    padding: 24
                    topPadding: 12
                    bottomPadding: 12

                    Label {
                        text: qsTr("Log entries")
                        font.pointSize: 16
                    }
                }

                footer: Item {
                    implicitHeight: 12
                }

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
