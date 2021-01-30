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
import Globals

DescriptorDetailsPopupForm {
    id: popup

    property var value: null
    property bool valueChanged: false
    property int displayMode: Globals.DisplayMode.Hexadecimal

    signal accepted()
    signal rejected()

    function _valueValidator() {
        switch (displayMode) {
            case Globals.DisplayMode.Hexadecimal:
                return hexadecimalValidator;

            case Globals.DisplayMode.Text:
                return textValidator;

            case Globals.DisplayMode.Binary:
                return binaryValidator;

            default:
                return null;
        }
    }

    valueTextField.text: globals.valueToString(value, displayMode)
    valueTextField.validator: _valueValidator()
    displayModeComboBox.currentIndex: displayMode

    RegularExpressionValidator {
        id: hexadecimalValidator
        regularExpression: /[a-fA-F0-9 ]*/
    }

    RegularExpressionValidator {
        id: textValidator;
        regularExpression: /.*/
    }

    RegularExpressionValidator {
        id: binaryValidator
        regularExpression: /[0-1 ]*/
    }

    Connections {
        target: valueTextField

        function onEditingFinished() {
            value = globals.valueFromString(valueTextField.text, displayMode);
            valueChanged = true;
        }
    }

    Connections {
        target: displayModeComboBox

        function onCurrentIndexChanged() {
            displayMode = displayModeComboBox.currentIndex;
        }
    }

    Connections {
        target: cancelButton

        function onClicked() {
            popup.close();
            popup.rejected();
        }
    }

    Connections {
        target: okButton

        function onClicked() {
            popup.close();
            popup.accepted();
        }
    }
}
