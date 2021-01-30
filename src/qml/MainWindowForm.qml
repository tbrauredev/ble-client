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

ApplicationWindow {
    property alias errorPopup: errorPopup
    property alias navigationPane: navigationPane
    property alias stackView: stackView
    property alias devicesPage: devicesPage
    property alias devicePage: devicePage
    property alias logPage: logPage
    property alias settingsPage: settingsPage
    property alias aboutPage: aboutPage

    visible: true
    width: 1248
    height: 700

    Overlay.overlay.modeless: Rectangle {
        color: "#8f28282a"
    }

    ErrorPopup {
        id: errorPopup
        parent: Overlay.overlay
        anchors.centerIn: parent
        modal: true
        dim: true
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        NavigationPane {
            id: navigationPane
            Layout.fillHeight: true
        }

        StackView {
            id: stackView
            Layout.fillWidth: true
            Layout.fillHeight: true

            Component {
                id: devicesPage
                DevicesPage { objectName: "devicesPage" }
            }

            Component {
                id: devicePage
                DevicePage { objectName: "devicePage" }
            }

            Component {
                id: logPage
                LogPage { objectName: "logPage" }
            }

            Component {
                id: settingsPage
                SettingsPage {
                    objectName: "settingsPage"
                    StackView.onRemoved: {
                        saveSettings();
                    }
                }
            }

            Component {
                id: aboutPage
                AboutPage { objectName: "aboutPage" }
            }
        }
    }
}
