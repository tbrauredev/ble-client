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
    property alias licenseLabel: licenseLabel
    property alias versionLabel: versionLabel

    padding: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            Layout.fillWidth: true
            padding: 24
            bottomPadding: 12

            Label {
                text: qsTr("About")
                font.pointSize: 24
            }
        }

        Pane {
            Layout.fillWidth: true
            Layout.fillHeight: true
            padding: 0

            ScrollView {
                anchors.fill: parent
                clip: true

                Pane {
                    padding: 24
                    topPadding: 12

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 0

                        Label {
                            text: qsTr("Bluetooth LE client")
                            font.pointSize: 16
                        }

                        Label {
                            id: versionLabel
                            font.weight: Font.Light
                        }

                        Label {
                            Layout.topMargin: 12
                            text: qsTr("A simple Qt based bluetooth low energy client.");
                        }

                        Label {
                            Layout.topMargin: 24
                            text: qsTr("License")
                            font.pointSize: 16
                        }

                        Label {
                            Layout.topMargin: 12
                            text: qsTr("Copyright © 2023 Thomas Braure.");
                        }

                        Label {
                            Layout.topMargin: 12
                            text: qsTr("This application comes with absolutely no warranty.");
                        }

                        Label {
                            id: licenseLabel
                            text: qsTr(
                                "See the <a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">" +
                                "GNU General Public License version 3 or later</a> for details.");

                            MouseArea {
                                anchors.fill: parent
                                acceptedButtons: Qt.NoButton
                                cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                            }
                        }

                        Label {
                            Layout.topMargin: 24
                            text: qsTr("Credits")
                            font.pointSize: 16
                        }

                        Label {
                            Layout.topMargin: 12
                            text: qsTr("This application uses the following libraries and assets:");
                        }

                        ColumnLayout {
                            Layout.topMargin: 12
                            spacing: 0

                            Label {
                                text: "Qt 6 - Copyright © 2022 The Qt Company Ltd and other contributors - LGPL v3";
                            }

                            Label {
                                text: "Material Design Icons 7 - Copyright © 2022 The pictogrammers - Apache License 2.0";
                            }
                        }
                    }
                }
            }
        }
    }
}
