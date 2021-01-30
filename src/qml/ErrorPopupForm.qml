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
    property alias messageLabel: messageLabel
    property alias okButton: okButton

    closePolicy: Popup.NoAutoClose

    ColumnLayout {
        anchors.fill: parent
        spacing: 12

        Label {
            text: qsTr("Error")
            font.pointSize: 16
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 12

            Label {
                id: messageLabel
                Layout.fillWidth: true
                Layout.columnSpan: 2
                wrapMode: Text.WrapAnywhere
            }
        }

        RowLayout {
            spacing: 12

            Item { Layout.fillWidth: true }

            Button {
                id: okButton
                Layout.minimumWidth: 100
                text: qsTr("Ok")
                hoverEnabled: true
            }
        }
    }
}
