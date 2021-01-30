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

ErrorPopupForm {
    id: popup

    function _errorMessage() {
        switch (controller.error) {
            case BluetoothController.Error.PoweredOff:
                return qsTr("The bluetooth interface is powered off.");

            case BluetoothController.Error.InsufficentPermission:
                return qsTr("Insufficient permission to perform the requested operation.");

            case BluetoothController.Error.DiscoveryFailed:
                return qsTr("The device discovery has failed.");

            case BluetoothController.Error.ConnectionFailed:
                return qsTr("The connection to the remote device has failed.");

            case BluetoothController.Error.CharacteristicReadFailed:
                return qsTr("The characteristic value could not be read.");

            case BluetoothController.Error.CharacteristicWriteFailed:
                return qsTr("The characteristic value could not be written.");

            case BluetoothController.Error.DescriptorReadFailed:
                return qsTr("The descriptor value could not be read.");

            case BluetoothController.Error.DescriptorWriteFailed:
                return qsTr("The descriptor value could not be written.");

            case BluetoothController.Error.InvalidOperation:
                return qsTr("The operation could not be performed.");

            case BluetoothController.Error.Unknown:
                return qsTr("An unknown error occured.");

            default:
                return "";
        }
    }

    messageLabel.text: _errorMessage()

    Connections {
        target: controller

        function onErrorChanged() {
            if (controller.error != BluetoothController.Error.None)
                popup.open();
        }
    }

    Connections {
        target: okButton

        function onClicked() {
            popup.close();
        }
    }
}
