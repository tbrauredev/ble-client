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

MainWindowForm {
    id: mainWindow
    stackView.initialItem: devicesPage

    function loadDevicesPage() {
        stackView.clear();
        stackView.push(devicesPage);
    }

    function loadDevicePage() {
        stackView.clear();
        stackView.push(devicePage);
    }

    function loadLogPage() {
        stackView.clear();
        stackView.push(logPage);
    }

    function loadSettingsPage() {
        stackView.clear();
        stackView.push(settingsPage);
    }

    function loadAboutPage() {
        stackView.clear();
        stackView.push(aboutPage);
    }
}
