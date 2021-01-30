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

Popup {
    property alias valueTextField: valueTextField
    property alias displayModeComboBox: displayModeComboBox
    property alias cancelButton: cancelButton
    property alias okButton: okButton

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        Label {
            text: qsTr("Details")
            font.pointSize: 16
        }

        GridLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 400
            rowSpacing: 12
            columnSpacing: 12
            rows: 2
            columns: 2

            Label {
                text: qsTr("Value")
            }

            TextField {
                id: valueTextField
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Display mode")
            }

            ComboBox {
                id: displayModeComboBox
                Layout.fillWidth: true
                model: ["Hexadecimal", "Text", "Binary"]
                hoverEnabled: true
            }
        }

        RowLayout {
            spacing: 12

            Item { Layout.fillWidth: true }

            Button {
                id: cancelButton
                Layout.minimumWidth: 100
                text: qsTr("Cancel")
                hoverEnabled: true
            }

            Button {
                id: okButton
                Layout.minimumWidth: 100
                text: qsTr("Ok")
                hoverEnabled: true
            }
        }
    }
}
