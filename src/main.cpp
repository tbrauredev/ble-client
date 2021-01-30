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

#include "bluetooth_controller.h"
#include "qml_types.h"
#include "settings.h"
#include "version.h"

#include <QtQuickControls2/QQuickStyle>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QGuiApplication>

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{file}(%{line}): %{message}");
    registerQmlTypes();

    QGuiApplication app(argc, argv);
    app.setOrganizationDomain("ble-client");
    app.setOrganizationName("ble-client");
    app.setApplicationDisplayName("ble-client");
    app.setApplicationName("ble-client");
    app.setApplicationVersion(VERSION);

    QQuickStyle::setStyle("Universal");
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("controller", BluetoothController::instance());
    engine.rootContext()->setContextProperty("settings", Settings::instance());
    engine.rootContext()->setContextProperty("globals", Globals::instance());
    engine.rootContext()->setContextProperty("version", QString(VERSION));

    engine.load(QUrl("qrc:/qml/MainWindow.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
