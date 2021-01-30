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
    property alias navigationButton: navigationButton
    property alias deviceButton: deviceButton
    property alias logButton: logButton
    property alias settingsButton: settingsButton
    property alias aboutButton: aboutButton

    padding: 0
    Universal.background: "#E4E4E4"

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        ItemDelegate {
            id: navigationButton
            icon.source: "qrc:/icons/menu.png"
            display: AbstractButton.IconOnly
            hoverEnabled: true
        }

        ItemDelegate {
            id: deviceButton
            Layout.fillWidth: true
            text: qsTr("Device")
            icon.source: "qrc:/icons/devices_other.png"
            hoverEnabled: true
        }

        ItemDelegate {
            id: logButton
            Layout.fillWidth: true
            text: qsTr("Log")
            icon.source: "qrc:/icons/format_list_checkbox.png"
            hoverEnabled: true
        }

        ItemDelegate {
            id: settingsButton
            Layout.fillWidth: true
            text: qsTr("Settings")
            icon.source: "qrc:/icons/settings.png"
            hoverEnabled: true
        }

        ItemDelegate {
            id: aboutButton
            Layout.fillWidth: true
            text: qsTr("About")
            icon.source: "qrc:/icons/info.png"
            hoverEnabled: true
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
