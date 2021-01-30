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

DevicePageForm {
    id: page

    property int _selectedServiceIndex: -1
    property int _selectedCharacteristicIndex: -1
    property int _selectedDescriptorIndex: -1

    titleLabel.text: controller.deviceName().length > 0 ? controller.deviceName() : "Unknown Device"
    addressLabel.text: controller.deviceAddress().length > 0 ? controller.deviceAddress() : "00:00:00:00:00:00"
    statusLabel.text:
        controller.state <= BluetoothController.State.DiscoveringDevices ? qsTr("Disconnected") :
            controller.state <= BluetoothController.State.SelectingDevice ? qsTr("Connecting") : qsTr("Connected")

    servicesListView.model: controller.servicesModel
    servicesListView.delegate: ServiceDelegate {
        anchors.left: parent != null ? parent.left : undefined
        anchors.right: parent != null ? parent.right : undefined
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        expanded: page._selectedServiceIndex == index

        onReleased: {
            if (page._selectedServiceIndex != index) {
                page._selectedDescriptorIndex = -1;
                page._selectedCharacteristicIndex = -1;
                page._selectedServiceIndex = index;
                controller.selectService(index);
            }
        }
    }

    characteristicsListView.model: controller.characteristicsModel
    characteristicsListView.delegate: CharacteristicDelegate {
        anchors.left: parent != null ? parent.left : undefined
        anchors.right: parent != null ? parent.right : undefined
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        expanded: page._selectedCharacteristicIndex == index

        onReleased: {
            if (page._selectedCharacteristicIndex != index) {
                page._selectedDescriptorIndex = -1;
                page._selectedCharacteristicIndex = index;
                controller.selectCharacteristic(index);
            }
        }
    }

    descriptorsListView.model: controller.descriptorsModel
    descriptorsListView.delegate: DescriptorDelegate {
        anchors.left: parent != null ? parent.left : undefined
        anchors.right: parent != null ? parent.right : undefined
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        expanded: page._selectedDescriptorIndex == index

        onReleased: {
            if (page._selectedDescriptorIndex != index) {
                page._selectedDescriptorIndex = index;
                controller.selectDescriptor(index);
            }
        }
    }

    Connections {
        target: disconnectButton

        function onReleased() {
            controller.deselectDevice();
            mainWindow.loadDevicesPage();
        }
    }
}
