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
    property alias detailsPane: detailsPane
    property alias uuidLabel: uuidLabel
    property alias mouseArea: mouseArea

    padding: 0
    contentWidth: itemDelegate.width

    ItemDelegate {
        id: itemDelegate
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        hoverEnabled: true
    }

    Pane {
        id: detailsPane
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: itemDelegate.bottom
        topPadding: -12

        ColumnLayout {
            anchors.fill: parent
            spacing: 12

            Label {
                id: uuidLabel
                padding: 0
                font.weight: Font.Light
                font.pointSize: 10
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: itemDelegate
    }
}
