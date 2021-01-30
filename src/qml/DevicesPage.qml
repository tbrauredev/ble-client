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

DevicesPageForm {
    id: page

    property var _selectedDeviceIndex: -1

    refreshIndicator.visible: controller.state === BluetoothController.State.DiscoveringDevices
    devicesListView.model: controller.devicesModel
    devicesListView.delegate: DeviceDelegate {
        anchors.left: parent != null ? parent.left : undefined
        anchors.leftMargin: 12
        implicitWidth: 300
        expanded: page._selectedDeviceIndex == index

        onReleased: {
            page._selectedDeviceIndex = index;
        }

        Connections {
            target: connectButton

            function onReleased() {
                controller.selectDevice(index);
                mainWindow.loadDevicePage();
            }
        }
    }

    Connections {
        target: refreshButton

        function onReleased() {
            page._selectedDeviceIndex = -1;
            controller.startDevicesDiscovery();
        }
    }
}
