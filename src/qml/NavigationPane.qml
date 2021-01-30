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

import BluetoothController

NavigationPaneForm {
    id: pane
    state: "expanded"

    property string _currentPage: mainWindow.stackView.currentItem != null ?
         mainWindow.stackView.currentItem.objectName : ""

    states: [
        State {
            name: "expanded"
            PropertyChanges {
                target: pane
                implicitWidth: 200
            }
        },

        State {
            name: "collapsed"
            PropertyChanges {
                target: pane
                implicitWidth: navigationButton.width
            }
        }
    ]

    transitions: [
        Transition {
            PropertyAnimation {
                target: pane
                property: "implicitWidth"
                easing.type: Easing.InOutQuad
            }
        }
    ]

    Connections {
        target: navigationButton

        function onReleased() {
            if (pane.state == "collapsed")
                pane.state = "expanded"
            else
                pane.state = "collapsed"
        }
    }

    Connections {
        target: deviceButton

        function onReleased() {
            if (_currentPage == "devicesPage" || _currentPage == "devicePage")
                return;

            if (controller.state >= BluetoothController.State.SelectingDevice)
                mainWindow.loadDevicePage();
            else
                mainWindow.loadDevicesPage();
        }
    }

    Connections {
        target: logButton

        function onReleased() {
            if (_currentPage == "logPage")
                return;

            mainWindow.loadLogPage();
        }
    }

    Connections {
        target: settingsButton

        function onReleased() {
            if (_currentPage == "settingsPage")
                return;

            mainWindow.loadSettingsPage();
        }
    }

    Connections {
        target: aboutButton

        function onReleased() {
            if (_currentPage == "aboutPage")
                return;

            mainWindow.loadAboutPage();
        }
    }
}
