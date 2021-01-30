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
    property alias logMaximumLengthTextField: logMaximumLengthTextField
    property alias logExportFormatComboBox: logExportFormatComboBox

    padding: 0

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            Layout.fillWidth: true
            padding: 24
            bottomPadding: 12

            Label {
                text: qsTr("Settings")
                font.pointSize: 24
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            Pane {
                padding: 24
                topPadding: 12

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 12

                    Label {
                        text: qsTr("Log")
                        font.pointSize: 16
                    }

                    ColumnLayout {
                        spacing: 6

                        Label {
                            text: qsTr("Maximum length")
                        }

                        TextField {
                            id: logMaximumLengthTextField
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200

                            validator: IntValidator {
                                bottom: 0
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 6

                        Label {
                            text: qsTr("Export format")
                        }

                        ComboBox {
                            id: logExportFormatComboBox
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            model: ["CSV", "JSON"]
                        }
                    }
                }
            }
        }
    }
}
