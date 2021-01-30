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

#ifndef BLUETOOTH_CONTROLLER_H_
#define BLUETOOTH_CONTROLLER_H_

#include "characteristics_model.h"
#include "descriptors_model.h"
#include "devices_model.h"
#include "services_model.h"
#include "logger.h"
#include "logger_model.h"

#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QLowEnergyController>

class BluetoothController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        State state
        READ state
        NOTIFY stateChanged);

    Q_PROPERTY(
        Error error
        READ error
        NOTIFY errorChanged);

    Q_PROPERTY(
        Logger* logger
        READ logger
        NOTIFY loggerChanged);

    Q_PROPERTY(
        LoggerModel* loggerModel
        READ loggerModel
        NOTIFY loggerModelChanged);

    Q_PROPERTY(
        DevicesModel* devicesModel
        READ devicesModel
        NOTIFY devicesModelChanged);

    Q_PROPERTY(
        ServicesModel* servicesModel
        READ servicesModel
        NOTIFY servicesModelChanged);

    Q_PROPERTY(
        CharacteristicsModel* characteristicsModel
        READ characteristicsModel
        NOTIFY characteristicsModelChanged);

    Q_PROPERTY(
        DescriptorsModel* descriptorsModel
        READ descriptorsModel
        NOTIFY descriptorsModelChanged);

public:
    enum class State {
        Unconnected,
        DiscoveringDevices,
        SelectingDevice,
        DeviceSelected,
        SelectingService,
        ServiceSelected,
        SelectingCharacteristic,
        CharacteristicSelected,
        SelectingDescriptor,
        DescriptorSelected,
    };
    Q_ENUM(State);

    enum class Error {
        None,
        PoweredOff,
        InsufficentPermission,
        DiscoveryFailed,
        ConnectionFailed,
        CharacteristicReadFailed,
        CharacteristicWriteFailed,
        DescriptorReadFailed,
        DescriptorWriteFailed,
        InvalidOperation,
        Unknown,
    };
    Q_ENUM(Error);

    BluetoothController(const BluetoothController&) = delete;
    BluetoothController(BluetoothController&&) = delete;

    BluetoothController& operator = (const BluetoothController&) = delete;
    BluetoothController& operator = (BluetoothController&&) = delete;

    ~BluetoothController() override;

    State state() const;
    Q_SIGNAL void stateChanged();

    Error error() const;
    Q_SIGNAL void errorChanged();

    Logger* logger() const;
    Q_SIGNAL void loggerChanged();

    LoggerModel* loggerModel() const;
    Q_SIGNAL void loggerModelChanged();

    Q_SLOT void startDevicesDiscovery();
    Q_SLOT void stopDevicesDiscovery();

    DevicesModel* devicesModel() const;
    Q_SIGNAL void devicesModelChanged();

    Q_SLOT void selectDevice(int index);
    Q_SLOT void deselectDevice();

    Q_INVOKABLE QString deviceName() const;
    Q_INVOKABLE QString deviceAddress() const;

    ServicesModel* servicesModel() const;
    Q_SIGNAL void servicesModelChanged();

    Q_SLOT void selectService(int index);
    Q_SLOT void deselectService();

    CharacteristicsModel* characteristicsModel() const;
    Q_SIGNAL void characteristicsModelChanged();

    Q_SLOT void selectCharacteristic(int index);
    Q_SLOT void deselectCharacteristic();

    Q_INVOKABLE void writeCharacteristicValue(const QByteArray& value);
    Q_INVOKABLE void touchCharacteristic();

    DescriptorsModel* descriptorsModel() const;
    Q_SIGNAL void descriptorsModelChanged();

    Q_SLOT void selectDescriptor(int index);
    Q_SLOT void deselectDescriptor();

    Q_INVOKABLE void writeDescriptorValue(const QByteArray& value);
    Q_INVOKABLE void touchDescriptor();

    static BluetoothController* instance();

private:
    explicit BluetoothController();

    void setState(State state);
    void setError(Error error);

    Q_SLOT void handleDeviceDiscovered(const QBluetoothDeviceInfo& deviceInfo);
    Q_SLOT void handleDeviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error);
    Q_SLOT void handleDeviceDiscoveryFinished();
    Q_SLOT void handleDeviceConnected();
    Q_SLOT void handleDeviceDisconnected();
    Q_SLOT void handleDeviceError(QLowEnergyController::Error error);
    Q_SLOT void handleServiceDiscovered(const QBluetoothUuid& serviceUuid);
    Q_SLOT void handleServiceDiscoveryFinished();
    Q_SLOT void handleServiceStateChanged(QLowEnergyService::ServiceState state);
    Q_SLOT void handleServiceError(QLowEnergyService::ServiceError error);
    Q_SLOT void handleCharacteristicChanged(const QLowEnergyCharacteristic& characteristic);
    Q_SLOT void handleCharacteristicRead(const QLowEnergyCharacteristic& characteristic);
    Q_SLOT void handleCharacteristicWritten(const QLowEnergyCharacteristic& characteristic);
    Q_SLOT void handleDescriptorRead(const QLowEnergyDescriptor& descriptor);
    Q_SLOT void handleDescriptorWritten(const QLowEnergyDescriptor& descriptor);

    State m_state;
    Error m_error;

    Logger* m_logger;
    LoggerModel* m_loggerModel;

    DevicesModel* m_devicesModel;
    ServicesModel* m_servicesModel;
    CharacteristicsModel* m_characteristicsModel;
    DescriptorsModel* m_descriptorsModel;

    QBluetoothDeviceDiscoveryAgent* m_discoveryAgent;
    QLowEnergyController* m_deviceController;
    QList<QLowEnergyService*> m_serviceObjects;
    QLowEnergyService* m_serviceObject;
    QLowEnergyCharacteristic m_characteristic;
    QLowEnergyDescriptor m_descriptor;
};

#endif  // BLUETOOTH_CONTROLLER_H_
