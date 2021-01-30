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

#include <QtCore/QMetaEnum>

BluetoothController::~BluetoothController()
{
    for (QLowEnergyService* serviceObject : m_serviceObjects) {
        QObject::disconnect(serviceObject, nullptr, this, nullptr);
        delete serviceObject;
    }
    m_serviceObjects.clear();
    m_serviceObject = nullptr;

    if (m_deviceController != nullptr) {
        QObject::disconnect(m_deviceController, nullptr, this, nullptr);
        delete m_deviceController;
    }

    if (m_discoveryAgent != nullptr) {
        QObject::disconnect(m_discoveryAgent, nullptr, this, nullptr);
        delete m_discoveryAgent;
    }
}

BluetoothController::State BluetoothController::state() const
{
    return m_state;
}

BluetoothController::Error BluetoothController::error() const
{
    return m_error;
}

Logger* BluetoothController::logger() const
{
    return m_logger;
}

LoggerModel* BluetoothController::loggerModel() const
{
    return m_loggerModel;
}

void BluetoothController::startDevicesDiscovery()
{
    this->stopDevicesDiscovery();
    this->deselectDevice();

    m_devicesModel->clearDeviceInfos();

    this->setError(Error::None);
    this->setState(State::DiscoveringDevices);

    LogEntry entry(LogEntry::Event::DeviceDiscoveryStarted);
    m_logger->addEntry(entry);

    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_discoveryAgent->setLowEnergyDiscoveryTimeout(10000);

    QObject::connect(
        m_discoveryAgent,
        &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
        this,
        &BluetoothController::handleDeviceDiscovered);

    QObject::connect(
        m_discoveryAgent,
        static_cast<void(QBluetoothDeviceDiscoveryAgent::*)(
            QBluetoothDeviceDiscoveryAgent::Error)>(
                &QBluetoothDeviceDiscoveryAgent::errorOccurred),
        this,
        &BluetoothController::handleDeviceDiscoveryError);

    QObject::connect(
        m_discoveryAgent,
        &QBluetoothDeviceDiscoveryAgent::finished,
        this,
        &BluetoothController::handleDeviceDiscoveryFinished);

    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BluetoothController::stopDevicesDiscovery()
{
    if (m_state == State::DiscoveringDevices) {
        LogEntry entry(LogEntry::Event::DeviceDiscoveryStopped);
        m_logger->addEntry(entry);

        QObject::disconnect(m_discoveryAgent, nullptr, this, nullptr);
        m_discoveryAgent->deleteLater();
        m_discoveryAgent = nullptr;

        this->setState(State::Unconnected);
    }
}

DevicesModel* BluetoothController::devicesModel() const
{
    return m_devicesModel;
}

void BluetoothController::selectDevice(int index)
{
    QBluetoothDeviceInfo deviceInfo = m_devicesModel->deviceInfo(index);
    if (!deviceInfo.isValid())
        return;

    this->stopDevicesDiscovery();
    this->deselectDevice();
    this->setError(Error::None);
    this->setState(State::SelectingDevice);

    m_deviceController = QLowEnergyController::createCentral(deviceInfo, this);
    QObject::connect(
        m_deviceController,
        &QLowEnergyController::connected,
        this,
        &BluetoothController::handleDeviceConnected);

    QObject::connect(
        m_deviceController,
        &QLowEnergyController::disconnected,
        this,
        &BluetoothController::handleDeviceDisconnected);

    QObject::connect(
        m_deviceController,
        static_cast<void(QLowEnergyController::*)(QLowEnergyController::Error)>(
            &QLowEnergyController::errorOccurred),
        this,
        &BluetoothController::handleDeviceError);

    QObject::connect(
        m_deviceController,
        &QLowEnergyController::serviceDiscovered,
        this,
        &BluetoothController::handleServiceDiscovered);

    QObject::connect(
        m_deviceController,
        &QLowEnergyController::discoveryFinished,
        this,
        &BluetoothController::handleServiceDiscoveryFinished);

    m_deviceController->connectToDevice();
}

void BluetoothController::deselectDevice()
{
    this->deselectService();

    if (m_state >= State::SelectingDevice) {
        for (QLowEnergyService* serviceObject : m_serviceObjects) {
            QObject::disconnect(serviceObject, nullptr, this, nullptr);
            serviceObject->deleteLater();
        }
        m_serviceObjects.clear();

        QObject::disconnect(m_deviceController, nullptr, this, nullptr);
        m_deviceController->deleteLater();
        m_deviceController = nullptr;

        m_servicesModel->clearServiceUuids();
        this->setState(State::Unconnected);
    }
}

QString BluetoothController::deviceName() const
{
    if (m_state >= State::SelectingDevice) {
        return m_deviceController->remoteName();
    }
    else {
        return QString();
    }
}

QString BluetoothController::deviceAddress() const
{
    if (m_state >= State::SelectingDevice) {
        return m_deviceController->remoteAddress().toString();
    }
    else {
        return QString();
    }
}

ServicesModel* BluetoothController::servicesModel() const
{
    return m_servicesModel;
}

void BluetoothController::selectService(int index)
{
    if (index < 0 || index >= m_serviceObjects.count())
        return;

    if (m_state < State::DeviceSelected)
        return;

    this->deselectService();
    this->setError(Error::None);
    this->setState(State::SelectingService);

    m_serviceObject = m_serviceObjects[index];
    m_characteristicsModel->setCharacteristics(m_serviceObject->characteristics());

    this->setState(State::ServiceSelected);
}

void BluetoothController::deselectService()
{
    this->deselectCharacteristic();

    if (m_state >= State::SelectingService) {
        m_serviceObject = nullptr;

        m_characteristicsModel->clearCharacteristics();
        this->setState(State::DeviceSelected);
    }
}

CharacteristicsModel* BluetoothController::characteristicsModel() const
{
    return m_characteristicsModel;
}

void BluetoothController::selectCharacteristic(int index)
{
    QLowEnergyCharacteristic characteristic = m_characteristicsModel->characteristic(index);
    if (!characteristic.isValid())
        return;

    if (m_state < State::ServiceSelected)
        return;

    this->deselectCharacteristic();
    this->setError(Error::None);
    this->setState(State::SelectingCharacteristic);

    m_characteristic = characteristic;
    m_descriptorsModel->setDescriptors(m_characteristic.descriptors());

    this->setState(State::CharacteristicSelected);
}

void BluetoothController::deselectCharacteristic()
{
    this->deselectDescriptor();

    if (m_state >= State::SelectingCharacteristic) {
        m_characteristic = QLowEnergyCharacteristic();
        m_descriptorsModel->clearDescriptors();

        this->setState(State::ServiceSelected);
    }
}

void BluetoothController::writeCharacteristicValue(const QByteArray& value)
{
    if (m_state >= State::CharacteristicSelected) {
        LogEntry entry(LogEntry::Event::WrittingCharacteristic);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(m_serviceObject->serviceUuid());
        entry.setCharacteristicUuid(m_characteristic.uuid());
        entry.setValue(value);
        m_logger->addEntry(entry);

        this->setError(Error::None);
        m_serviceObject->writeCharacteristic(m_characteristic, value);
        this->touchCharacteristic();
    }
}

void BluetoothController::touchCharacteristic()
{
    if (m_state >= State::CharacteristicSelected)
        m_characteristicsModel->updateCharacteristic(m_characteristic);
}

DescriptorsModel* BluetoothController::descriptorsModel() const
{
    return m_descriptorsModel;
}

void BluetoothController::selectDescriptor(int index)
{
    QLowEnergyDescriptor descriptor = m_descriptorsModel->descriptor(index);
    if (!descriptor.isValid())
        return;

    if (m_state < State::CharacteristicSelected)
        return;

    this->deselectDescriptor();
    this->setError(Error::None);
    this->setState(State::SelectingDescriptor);

    m_descriptor = descriptor;
    this->setState(State::DescriptorSelected);
}

void BluetoothController::deselectDescriptor()
{
    if (m_state >= State::SelectingDescriptor) {
        m_descriptor = QLowEnergyDescriptor();
        this->setState(State::CharacteristicSelected);
    }
}

void BluetoothController::writeDescriptorValue(const QByteArray& value)
{
    if (m_state >= State::DescriptorSelected) {
        LogEntry entry(LogEntry::Event::WrittingDescriptor);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(m_serviceObject->serviceUuid());
        entry.setCharacteristicUuid(m_characteristic.uuid());
        entry.setDescriptorUuid(m_descriptor.uuid());
        entry.setValue(value);

        m_logger->addEntry(entry);
        this->setError(Error::None);
        m_serviceObject->writeDescriptor(m_descriptor, value);
        this->touchDescriptor();
    }
}

void BluetoothController::touchDescriptor()
{
    if (m_state >= State::DescriptorSelected)
        m_descriptorsModel->updateDescriptor(m_descriptor);
}

BluetoothController* BluetoothController::instance()
{
    static BluetoothController instance;
    return &instance;
}

BluetoothController::BluetoothController() :
    m_state(State::Unconnected),
    m_error(Error::None),
    m_logger(new Logger(this)),
    m_devicesModel(new DevicesModel(this)),
    m_servicesModel(new ServicesModel(this)),
    m_characteristicsModel(new CharacteristicsModel(this)),
    m_descriptorsModel(new DescriptorsModel(this)),
    m_loggerModel(new LoggerModel(m_logger, this)),
    m_discoveryAgent(nullptr),
    m_deviceController(nullptr),
    m_serviceObject(nullptr) {}

void BluetoothController::setState(State state)
{
    if (m_state != state) {
        m_state = state;
        Q_EMIT stateChanged();
    }
}

void BluetoothController::setError(Error error)
{
    if (m_error != error) {
        m_error = error;
        Q_EMIT errorChanged();
    }
}

void BluetoothController::handleDeviceDiscovered(
    const QBluetoothDeviceInfo& deviceInfo)
{
    if (m_state != State::DiscoveringDevices)
        return;

    bool isLowEnergy =
        deviceInfo.coreConfigurations() &
            QBluetoothDeviceInfo::LowEnergyCoreConfiguration;

    if (isLowEnergy) {
        LogEntry entry(LogEntry::Event::DeviceDiscovered);
        entry.setDeviceAddress(deviceInfo.address());
        entry.setDeviceName(deviceInfo.name());
        m_logger->addEntry(entry);

        m_devicesModel->addDeviceInfo(deviceInfo);
    }
}

void BluetoothController::handleDeviceDiscoveryError(
    QBluetoothDeviceDiscoveryAgent::Error error)
{
    if (error != QBluetoothDeviceDiscoveryAgent::NoError) {
        LogEntry entry(LogEntry::Event::ErrorOccurred);
        entry.setErrorMessage(m_discoveryAgent->errorString());
        m_logger->addEntry(entry);
    }

    if (m_state != State::DiscoveringDevices)
        return;

    switch (error) {
        case QBluetoothDeviceDiscoveryAgent::NoError:
            break;

        case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
            this->setError(Error::PoweredOff);
            this->stopDevicesDiscovery();
            break;

        case QBluetoothDeviceDiscoveryAgent::MissingPermissionsError:
            this->setError(Error::InsufficentPermission);
            this->stopDevicesDiscovery();
            break;

        case QBluetoothDeviceDiscoveryAgent::LocationServiceTurnedOffError:
        case QBluetoothDeviceDiscoveryAgent::UnsupportedPlatformError:
        case QBluetoothDeviceDiscoveryAgent::UnsupportedDiscoveryMethod:
            this->setError(Error::DiscoveryFailed);
            this->stopDevicesDiscovery();
            break;

        default:
            this->setError(Error::Unknown);
            this->stopDevicesDiscovery();
            break;
    }
}

void BluetoothController::handleDeviceDiscoveryFinished()
{
    this->stopDevicesDiscovery();
}

void BluetoothController::handleDeviceConnected()
{
    if (m_state != State::SelectingDevice)
        return;

    LogEntry entry1(LogEntry::Event::DeviceConnected);
    entry1.setDeviceAddress(m_deviceController->remoteAddress());
    entry1.setDeviceName(m_deviceController->remoteName());
    m_logger->addEntry(entry1);

    LogEntry entry2(LogEntry::Event::ServiceDiscoveryStarted);
    entry2.setDeviceAddress(m_deviceController->remoteAddress());
    entry2.setDeviceName(m_deviceController->remoteName());
    m_logger->addEntry(entry2);

    m_deviceController->discoverServices();
}

void BluetoothController::handleDeviceDisconnected()
{
    LogEntry entry(LogEntry::Event::DeviceDisconnected);
    entry.setDeviceAddress(m_deviceController->remoteAddress());
    entry.setDeviceName(m_deviceController->remoteName());
    m_logger->addEntry(entry);

    this->deselectDevice();
}

void BluetoothController::handleDeviceError(
    QLowEnergyController::Error error)
{
    if (error != QLowEnergyController::NoError) {
        LogEntry entry(LogEntry::Event::ErrorOccurred);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setErrorMessage(m_deviceController->errorString());
        m_logger->addEntry(entry);
    }

    switch (error) {
        case QLowEnergyController::NoError:
            break;

        case QLowEnergyController::MissingPermissionsError:
            this->setError(Error::InsufficentPermission);
            this->deselectDevice();
            break;

        case QLowEnergyController::ConnectionError:
            this->setError(Error::ConnectionFailed);
            this->deselectDevice();
            break;

        default:
            this->setError(Error::Unknown);
            this->deselectDevice();
            break;
    }
}

void BluetoothController::handleServiceDiscovered(
    const QBluetoothUuid& serviceUuid)
{
    if (m_state != State::SelectingDevice)
        return;

    LogEntry entry(LogEntry::Event::ServiceDiscovered);
    entry.setDeviceAddress(m_deviceController->remoteAddress());
    entry.setDeviceName(m_deviceController->remoteName());
    entry.setServiceUuid(serviceUuid);
    m_logger->addEntry(entry);

    m_servicesModel->addServiceUuid(serviceUuid);
}

void BluetoothController::handleServiceDiscoveryFinished()
{
    if (m_state != State::SelectingDevice)
        return;

    LogEntry entry(LogEntry::Event::ServiceDiscoveryFinished);
    entry.setDeviceAddress(m_deviceController->remoteAddress());
    entry.setDeviceName(m_deviceController->remoteName());
    m_logger->addEntry(entry);

    for (const QBluetoothUuid& serviceUuid : m_servicesModel->serviceUuids()) {
        QLowEnergyService* serviceObject = m_deviceController->createServiceObject(serviceUuid, this);
        m_serviceObjects.append(serviceObject);

        LogEntry entry(LogEntry::Event::ServiceDetailsDiscoveryStarted);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(serviceUuid);
        m_logger->addEntry(entry);

        QObject::connect(
            serviceObject,
            &QLowEnergyService::stateChanged,
            this,
            &BluetoothController::handleServiceStateChanged);

        QObject::connect(
            serviceObject,
            static_cast<void(QLowEnergyService::*)(QLowEnergyService::ServiceError)>(
                &QLowEnergyService::errorOccurred),
            this,
            &BluetoothController::handleServiceError);

        QObject::connect(
            serviceObject,
            &QLowEnergyService::characteristicChanged,
            this,
            &BluetoothController::handleCharacteristicChanged);

        QObject::connect(
            serviceObject,
            &QLowEnergyService::characteristicRead,
            this,
            &BluetoothController::handleCharacteristicRead);

        QObject::connect(
            serviceObject,
            &QLowEnergyService::characteristicWritten,
            this,
            &BluetoothController::handleCharacteristicWritten);

        QObject::connect(
            serviceObject,
            &QLowEnergyService::descriptorRead,
            this,
            &BluetoothController::handleDescriptorRead);

        QObject::connect(
            serviceObject,
            &QLowEnergyService::descriptorWritten,
            this,
            &BluetoothController::handleDescriptorWritten);

        this->handleServiceStateChanged(serviceObject->state());
        serviceObject->discoverDetails();
    }
}

void BluetoothController::handleServiceStateChanged(
    QLowEnergyService::ServiceState state)
{
    if (state == QLowEnergyService::RemoteServiceDiscovered) {
        QLowEnergyService* serviceObject = qobject_cast<QLowEnergyService*>(this->sender());

        LogEntry entry(LogEntry::Event::ServiceDetailsDiscoveryFinished);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(serviceObject->serviceUuid());
        m_logger->addEntry(entry);
    }

    if (m_state != State::SelectingDevice)
        return;

    for (QLowEnergyService* serviceObject : m_serviceObjects) {
        if (serviceObject->state() != QLowEnergyService::RemoteServiceDiscovered)
            return;
    }

    this->setState(State::DeviceSelected);
}

void BluetoothController::handleServiceError(
    QLowEnergyService::ServiceError error)
{
    if (error != QLowEnergyService::NoError) {
        QMetaEnum metaEnum = QMetaEnum::fromType<QLowEnergyService::ServiceError>();

        LogEntry entry(LogEntry::Event::ErrorOccurred);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(m_serviceObject->serviceUuid());
        entry.setErrorMessage(metaEnum.valueToKey(error));
        m_logger->addEntry(entry);
    }

    switch (error) {
        case QLowEnergyService::NoError:
            break;

        case QLowEnergyService::CharacteristicReadError:
            this->setError(Error::CharacteristicReadFailed);
            break;

        case QLowEnergyService::CharacteristicWriteError:
            this->setError(Error::CharacteristicWriteFailed);
            break;

        case QLowEnergyService::DescriptorReadError:
            this->setError(Error::DescriptorReadFailed);
            break;

        case QLowEnergyService::DescriptorWriteError:
            this->setError(Error::DescriptorWriteFailed);
            break;

        case QLowEnergyService::OperationError:
            this->setError(Error::InvalidOperation);
            this->deselectDevice();
            break;

        default:
            this->setError(Error::Unknown);
            this->deselectDevice();
            break;
    }
}

void BluetoothController::handleCharacteristicChanged(
    const QLowEnergyCharacteristic& characteristic)
{
    if (m_state >= State::DeviceSelected) {
        QLowEnergyService* serviceObject = qobject_cast<QLowEnergyService*>(this->sender());

        LogEntry entry(LogEntry::Event::CharacteristicChanged);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(serviceObject->serviceUuid());
        entry.setCharacteristicUuid(characteristic.uuid());
        entry.setValue(characteristic.value());
        m_logger->addEntry(entry);

        if (serviceObject == m_serviceObject)
            m_characteristicsModel->updateCharacteristic(characteristic);
    }
}

void BluetoothController::handleCharacteristicRead(
    const QLowEnergyCharacteristic& characteristic)
{
    if (m_state >= State::DeviceSelected) {
        QLowEnergyService* serviceObject = qobject_cast<QLowEnergyService*>(this->sender());

        LogEntry entry(LogEntry::Event::CharacteristicRead);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(serviceObject->serviceUuid());
        entry.setCharacteristicUuid(characteristic.uuid());
        entry.setValue(characteristic.value());
        m_logger->addEntry(entry);

        if (serviceObject == m_serviceObject)
            m_characteristicsModel->updateCharacteristic(characteristic);
    }
}

void BluetoothController::handleCharacteristicWritten(
    const QLowEnergyCharacteristic& characteristic)
{
    if (m_state >= State::DeviceSelected) {
        QLowEnergyService* serviceObject = qobject_cast<QLowEnergyService*>(this->sender());

        LogEntry entry(LogEntry::Event::CharacteristicWritten);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(serviceObject->serviceUuid());
        entry.setCharacteristicUuid(characteristic.uuid());
        entry.setValue(characteristic.value());
        m_logger->addEntry(entry);

        if (serviceObject == m_serviceObject)
            m_characteristicsModel->updateCharacteristic(characteristic);
    }
}

void BluetoothController::handleDescriptorRead(
    const QLowEnergyDescriptor& descriptor)
{
    if (m_state >= State::DeviceSelected) {
        QLowEnergyService* serviceObject = qobject_cast<QLowEnergyService*>(this->sender());

        QLowEnergyCharacteristic characteristic;
        for (const QLowEnergyCharacteristic& c : serviceObject->characteristics()) {
            if (c.descriptors().contains(descriptor)) {
                characteristic = c;
                break;
            }
        }

        LogEntry entry(LogEntry::Event::DescriptorRead);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(serviceObject->serviceUuid());
        entry.setCharacteristicUuid(characteristic.uuid());
        entry.setDescriptorUuid(descriptor.uuid());
        entry.setValue(descriptor.value());
        m_logger->addEntry(entry);

        if (serviceObject == m_serviceObject)
            m_descriptorsModel->updateDescriptor(descriptor);
    }
}

void BluetoothController::handleDescriptorWritten(
    const QLowEnergyDescriptor& descriptor)
{
    if (m_state >= State::DeviceSelected) {
        QLowEnergyService* serviceObject = qobject_cast<QLowEnergyService*>(this->sender());

        QLowEnergyCharacteristic characteristic;
        for (const QLowEnergyCharacteristic& c : serviceObject->characteristics()) {
            if (c.descriptors().contains(descriptor)) {
                characteristic = c;
                break;
            }
        }

        LogEntry entry(LogEntry::Event::DescriptorWritten);
        entry.setDeviceAddress(m_deviceController->remoteAddress());
        entry.setDeviceName(m_deviceController->remoteName());
        entry.setServiceUuid(serviceObject->serviceUuid());
        entry.setCharacteristicUuid(characteristic.uuid());
        entry.setDescriptorUuid(descriptor.uuid());
        entry.setValue(descriptor.value());
        m_logger->addEntry(entry);

        if (serviceObject == m_serviceObject)
            m_descriptorsModel->updateDescriptor(descriptor);
    }
}
