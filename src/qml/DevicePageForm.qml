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
    property alias titleLabel: titleLabel
    property alias addressLabel: addressLabel
    property alias statusLabel: statusLabel
    property alias disconnectButton: disconnectButton
    property alias servicesListView: servicesListView
    property alias characteristicsListView: characteristicsListView
    property alias descriptorsListView: descriptorsListView

    padding: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            id: headerPane
            Layout.fillWidth: true
            padding: 24
            bottomPadding: 12

            ColumnLayout {
                spacing: 24

                Label {
                    id: titleLabel
                    font.pointSize: 24
                }

                RowLayout {
                    spacing: 72

                    ColumnLayout {
                        spacing: 0

                        RowLayout {
                            spacing: 6

                            Label {
                                text: qsTr("Address:")
                                font.weight: Font.Light
                            }

                            Label {
                                id: addressLabel
                            }
                        }

                        RowLayout {
                            spacing: 6

                            Label {
                                text: qsTr("Status:")
                                font.weight: Font.Light
                            }

                            Label {
                                id: statusLabel
                            }
                        }
                    }

                    Button {
                        id: disconnectButton
                        text: qsTr("Disconnect")
                        hoverEnabled: true
                    }
                }
            }
        }

        Pane {
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 0

            GridLayout {
                anchors.fill: parent
                rowSpacing: 12
                columnSpacing: 0
                rows: 2
                columns: 6

                Label {
                    Layout.leftMargin: 24
                    text: qsTr("Services")
                    font.pointSize: 16
                }

                Item { implicitWidth: 1 }

                Label {
                    Layout.leftMargin: 24
                    text: qsTr("Characteristics")
                    font.pointSize: 16
                }

                Item { implicitWidth: 1 }

                Label {
                    Layout.leftMargin: 24
                    text: qsTr("Descriptors")
                    font.pointSize: 16
                }

                Item {
                    Layout.fillWidth: true
                    Layout.rowSpan: 2
                }

                ListView {
                    id: servicesListView
                    Layout.fillHeight: true
                    implicitWidth: 324
                    currentIndex: -1
                    clip: true

                    ScrollBar.vertical: ScrollBar {}
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

                Rectangle {
                    Layout.fillHeight: true
                    implicitWidth: 1
                    color: "#E4E4E4"
                }

                ListView {
                    id: characteristicsListView
                    Layout.fillHeight: true
                    implicitWidth: 324
                    currentIndex: -1
                    clip: true

                    ScrollBar.vertical: ScrollBar {}
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
                        id: trans
                        PropertyAnimation {
                            property: "opacity"
                            from: 0
                            to: 1
                            duration: 300
                        }
                    }
                }

                Rectangle {
                    Layout.fillHeight: true
                    implicitWidth: 1
                    color: "#E4E4E4"
                }

                ListView {
                    id: descriptorsListView
                    Layout.fillHeight: true
                    implicitWidth: 324
                    currentIndex: -1
                    clip: true

                    ScrollBar.vertical: ScrollBar {}
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
}
