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

import Settings

SettingsPageForm {
    id: page

    function saveSettings() {
        settings.setLogMaximumLength(logMaximumLengthTextField.text);
        settings.setLogExportFormat(logExportFormatComboBox.currentIndex);
    }

    logMaximumLengthTextField.text: settings.logMaximumLength()
    logExportFormatComboBox.currentIndex: settings.logExportFormat()

    Component.onDestruction: {
        saveSettings();
    }
}
