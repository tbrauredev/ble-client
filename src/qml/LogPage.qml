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
import QtQuick.Dialogs
import QtCore

import BluetoothController
import Globals
import Settings

LogPageForm {
    id: page

    property var _selectedDeviceIndex: -1

    loggerListView.model: controller.loggerModel
    loggerListView.delegate: LogEntryDelegate {
        anchors.left: parent != null ? parent.left : undefined
        anchors.right: parent != null ? parent.right : undefined
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        expanded: page._selectedDeviceIndex == index

        onReleased: {
            page._selectedDeviceIndex = index;
        }
    }

    FileDialog {
        id: fileDialog

        function _nameFilters() {
            switch (settings.logExportFormat()) {
                case Globals.LogFormat.Csv:
                    return ["Csv files (*.csv)"];

                case Globals.LogFormat.Json:
                    return ["Json files (*.json)"];

                default:
                    return [];
            }
        }

        function _defaultSuffix() {
            switch (settings.logExportFormat()) {
                case Globals.LogFormat.Csv:
                    return ".csv";

                case Globals.LogFormat.Json:
                    return ".json";

                default:
                    return "";
            }
        }

        fileMode: FileDialog.SaveFile
        nameFilters: _nameFilters()
        defaultSuffix: _defaultSuffix()
        currentFolder: StandardPaths.writableLocation(StandardPaths.HomeLocation)
    }

    Connections {
        target: exportButton

        function onReleased() {
            fileDialog.open();
        }
    }

    Connections {
        target: fileDialog

        function onAccepted() {
            controller.logger.exportEntries(fileDialog.selectedFile);
        }
    }

    Connections {
        target: clearButton

        function onReleased() {
            controller.logger.clearEntries();
        }
    }
}
