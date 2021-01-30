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

#include "globals.h"

//==============================================================================
// Constants
//==============================================================================
static QVector<QBluetoothUuid::ServiceClassUuid> g_serviceUuids = {
    QBluetoothUuid::ServiceClassUuid::ServiceDiscoveryServer,
    QBluetoothUuid::ServiceClassUuid::BrowseGroupDescriptor,
    QBluetoothUuid::ServiceClassUuid::PublicBrowseGroup,
    QBluetoothUuid::ServiceClassUuid::SerialPort,
    QBluetoothUuid::ServiceClassUuid::LANAccessUsingPPP,
    QBluetoothUuid::ServiceClassUuid::DialupNetworking,
    QBluetoothUuid::ServiceClassUuid::IrMCSync,
    QBluetoothUuid::ServiceClassUuid::ObexObjectPush,
    QBluetoothUuid::ServiceClassUuid::OBEXFileTransfer,
    QBluetoothUuid::ServiceClassUuid::IrMCSyncCommand,
    QBluetoothUuid::ServiceClassUuid::Headset,
    QBluetoothUuid::ServiceClassUuid::AudioSource,
    QBluetoothUuid::ServiceClassUuid::AudioSink,
    QBluetoothUuid::ServiceClassUuid::AV_RemoteControlTarget,
    QBluetoothUuid::ServiceClassUuid::AdvancedAudioDistribution,
    QBluetoothUuid::ServiceClassUuid::AV_RemoteControl,
    QBluetoothUuid::ServiceClassUuid::AV_RemoteControlController,
    QBluetoothUuid::ServiceClassUuid::HeadsetAG,
    QBluetoothUuid::ServiceClassUuid::PANU,
    QBluetoothUuid::ServiceClassUuid::NAP,
    QBluetoothUuid::ServiceClassUuid::GN,
    QBluetoothUuid::ServiceClassUuid::DirectPrinting,
    QBluetoothUuid::ServiceClassUuid::ReferencePrinting,
    QBluetoothUuid::ServiceClassUuid::BasicImage,
    QBluetoothUuid::ServiceClassUuid::ImagingResponder,
    QBluetoothUuid::ServiceClassUuid::ImagingAutomaticArchive,
    QBluetoothUuid::ServiceClassUuid::ImagingReferenceObjects,
    QBluetoothUuid::ServiceClassUuid::Handsfree,
    QBluetoothUuid::ServiceClassUuid::HandsfreeAudioGateway,
    QBluetoothUuid::ServiceClassUuid::DirectPrintingReferenceObjectsService,
    QBluetoothUuid::ServiceClassUuid::ReflectedUI,
    QBluetoothUuid::ServiceClassUuid::BasicPrinting,
    QBluetoothUuid::ServiceClassUuid::PrintingStatus,
    QBluetoothUuid::ServiceClassUuid::HumanInterfaceDeviceService,
    QBluetoothUuid::ServiceClassUuid::HardcopyCableReplacement,
    QBluetoothUuid::ServiceClassUuid::HCRPrint,
    QBluetoothUuid::ServiceClassUuid::HCRScan,
    QBluetoothUuid::ServiceClassUuid::SIMAccess,
    QBluetoothUuid::ServiceClassUuid::PhonebookAccessPCE,
    QBluetoothUuid::ServiceClassUuid::PhonebookAccessPSE,
    QBluetoothUuid::ServiceClassUuid::PhonebookAccess,
    QBluetoothUuid::ServiceClassUuid::HeadsetHS,
    QBluetoothUuid::ServiceClassUuid::MessageAccessServer,
    QBluetoothUuid::ServiceClassUuid::MessageNotificationServer,
    QBluetoothUuid::ServiceClassUuid::MessageAccessProfile,
    QBluetoothUuid::ServiceClassUuid::GNSS,
    QBluetoothUuid::ServiceClassUuid::GNSSServer,
    QBluetoothUuid::ServiceClassUuid::Display3D,
    QBluetoothUuid::ServiceClassUuid::Glasses3D,
    QBluetoothUuid::ServiceClassUuid::Synchronization3D,
    QBluetoothUuid::ServiceClassUuid::MPSProfile,
    QBluetoothUuid::ServiceClassUuid::MPSService,
    QBluetoothUuid::ServiceClassUuid::PnPInformation,
    QBluetoothUuid::ServiceClassUuid::GenericNetworking,
    QBluetoothUuid::ServiceClassUuid::GenericFileTransfer,
    QBluetoothUuid::ServiceClassUuid::GenericAudio,
    QBluetoothUuid::ServiceClassUuid::GenericTelephony,
    QBluetoothUuid::ServiceClassUuid::VideoSource,
    QBluetoothUuid::ServiceClassUuid::VideoSink,
    QBluetoothUuid::ServiceClassUuid::VideoDistribution,
    QBluetoothUuid::ServiceClassUuid::HDP,
    QBluetoothUuid::ServiceClassUuid::HDPSource,
    QBluetoothUuid::ServiceClassUuid::HDPSink,
    QBluetoothUuid::ServiceClassUuid::GenericAccess,
    QBluetoothUuid::ServiceClassUuid::GenericAttribute,
    QBluetoothUuid::ServiceClassUuid::ImmediateAlert,
    QBluetoothUuid::ServiceClassUuid::LinkLoss,
    QBluetoothUuid::ServiceClassUuid::TxPower,
    QBluetoothUuid::ServiceClassUuid::CurrentTimeService,
    QBluetoothUuid::ServiceClassUuid::ReferenceTimeUpdateService,
    QBluetoothUuid::ServiceClassUuid::NextDSTChangeService,
    QBluetoothUuid::ServiceClassUuid::Glucose,
    QBluetoothUuid::ServiceClassUuid::HealthThermometer,
    QBluetoothUuid::ServiceClassUuid::DeviceInformation,
    QBluetoothUuid::ServiceClassUuid::HeartRate,
    QBluetoothUuid::ServiceClassUuid::PhoneAlertStatusService,
    QBluetoothUuid::ServiceClassUuid::BatteryService,
    QBluetoothUuid::ServiceClassUuid::BloodPressure,
    QBluetoothUuid::ServiceClassUuid::AlertNotificationService,
    QBluetoothUuid::ServiceClassUuid::HumanInterfaceDevice,
    QBluetoothUuid::ServiceClassUuid::ScanParameters,
    QBluetoothUuid::ServiceClassUuid::RunningSpeedAndCadence,
    QBluetoothUuid::ServiceClassUuid::CyclingSpeedAndCadence,
    QBluetoothUuid::ServiceClassUuid::CyclingPower,
    QBluetoothUuid::ServiceClassUuid::LocationAndNavigation,
    QBluetoothUuid::ServiceClassUuid::EnvironmentalSensing,
    QBluetoothUuid::ServiceClassUuid::BodyComposition,
    QBluetoothUuid::ServiceClassUuid::UserData,
    QBluetoothUuid::ServiceClassUuid::WeightScale,
    QBluetoothUuid::ServiceClassUuid::BondManagement,
    QBluetoothUuid::ServiceClassUuid::ContinuousGlucoseMonitoring,
};

static QVector<QBluetoothUuid::CharacteristicType> g_characteristicUuids = {
    QBluetoothUuid::CharacteristicType::DeviceName,
    QBluetoothUuid::CharacteristicType::Appearance,
    QBluetoothUuid::CharacteristicType::PeripheralPrivacyFlag,
    QBluetoothUuid::CharacteristicType::ReconnectionAddress,
    QBluetoothUuid::CharacteristicType::PeripheralPreferredConnectionParameters,
    QBluetoothUuid::CharacteristicType::ServiceChanged,
    QBluetoothUuid::CharacteristicType::AlertLevel,
    QBluetoothUuid::CharacteristicType::TxPowerLevel,
    QBluetoothUuid::CharacteristicType::DateTime,
    QBluetoothUuid::CharacteristicType::DayOfWeek,
    QBluetoothUuid::CharacteristicType::DayDateTime,
    QBluetoothUuid::CharacteristicType::ExactTime256,
    QBluetoothUuid::CharacteristicType::DSTOffset,
    QBluetoothUuid::CharacteristicType::TimeZone,
    QBluetoothUuid::CharacteristicType::LocalTimeInformation,
    QBluetoothUuid::CharacteristicType::TimeWithDST,
    QBluetoothUuid::CharacteristicType::TimeAccuracy,
    QBluetoothUuid::CharacteristicType::TimeSource,
    QBluetoothUuid::CharacteristicType::ReferenceTimeInformation,
    QBluetoothUuid::CharacteristicType::TimeUpdateControlPoint,
    QBluetoothUuid::CharacteristicType::TimeUpdateState,
    QBluetoothUuid::CharacteristicType::GlucoseMeasurement,
    QBluetoothUuid::CharacteristicType::BatteryLevel,
    QBluetoothUuid::CharacteristicType::TemperatureMeasurement,
    QBluetoothUuid::CharacteristicType::TemperatureType,
    QBluetoothUuid::CharacteristicType::IntermediateTemperature,
    QBluetoothUuid::CharacteristicType::MeasurementInterval,
    QBluetoothUuid::CharacteristicType::BootKeyboardInputReport,
    QBluetoothUuid::CharacteristicType::SystemID,
    QBluetoothUuid::CharacteristicType::ModelNumberString,
    QBluetoothUuid::CharacteristicType::SerialNumberString,
    QBluetoothUuid::CharacteristicType::FirmwareRevisionString,
    QBluetoothUuid::CharacteristicType::HardwareRevisionString,
    QBluetoothUuid::CharacteristicType::SoftwareRevisionString,
    QBluetoothUuid::CharacteristicType::ManufacturerNameString,
    QBluetoothUuid::CharacteristicType::IEEE1107320601RegulatoryCertificationDataList,
    QBluetoothUuid::CharacteristicType::CurrentTime,
    QBluetoothUuid::CharacteristicType::MagneticDeclination,
    QBluetoothUuid::CharacteristicType::ScanRefresh,
    QBluetoothUuid::CharacteristicType::BootKeyboardOutputReport,
    QBluetoothUuid::CharacteristicType::BootMouseInputReport,
    QBluetoothUuid::CharacteristicType::GlucoseMeasurementContext,
    QBluetoothUuid::CharacteristicType::BloodPressureMeasurement,
    QBluetoothUuid::CharacteristicType::IntermediateCuffPressure,
    QBluetoothUuid::CharacteristicType::HeartRateMeasurement,
    QBluetoothUuid::CharacteristicType::BodySensorLocation,
    QBluetoothUuid::CharacteristicType::HeartRateControlPoint,
    QBluetoothUuid::CharacteristicType::AlertStatus,
    QBluetoothUuid::CharacteristicType::RingerControlPoint,
    QBluetoothUuid::CharacteristicType::RingerSetting,
    QBluetoothUuid::CharacteristicType::AlertCategoryIDBitMask,
    QBluetoothUuid::CharacteristicType::AlertCategoryID,
    QBluetoothUuid::CharacteristicType::AlertNotificationControlPoint,
    QBluetoothUuid::CharacteristicType::UnreadAlertStatus,
    QBluetoothUuid::CharacteristicType::NewAlert,
    QBluetoothUuid::CharacteristicType::SupportedNewAlertCategory,
    QBluetoothUuid::CharacteristicType::SupportedUnreadAlertCategory,
    QBluetoothUuid::CharacteristicType::BloodPressureFeature,
    QBluetoothUuid::CharacteristicType::HIDInformation,
    QBluetoothUuid::CharacteristicType::ReportMap,
    QBluetoothUuid::CharacteristicType::HIDControlPoint,
    QBluetoothUuid::CharacteristicType::Report,
    QBluetoothUuid::CharacteristicType::ProtocolMode,
    QBluetoothUuid::CharacteristicType::ScanIntervalWindow,
    QBluetoothUuid::CharacteristicType::PnPID,
    QBluetoothUuid::CharacteristicType::GlucoseFeature,
    QBluetoothUuid::CharacteristicType::RecordAccessControlPoint,
    QBluetoothUuid::CharacteristicType::RSCMeasurement,
    QBluetoothUuid::CharacteristicType::RSCFeature,
    QBluetoothUuid::CharacteristicType::SCControlPoint,
    QBluetoothUuid::CharacteristicType::CSCMeasurement,
    QBluetoothUuid::CharacteristicType::CSCFeature,
    QBluetoothUuid::CharacteristicType::SensorLocation,
    QBluetoothUuid::CharacteristicType::CyclingPowerMeasurement,
    QBluetoothUuid::CharacteristicType::CyclingPowerVector,
    QBluetoothUuid::CharacteristicType::CyclingPowerFeature,
    QBluetoothUuid::CharacteristicType::CyclingPowerControlPoint,
    QBluetoothUuid::CharacteristicType::LocationAndSpeed,
    QBluetoothUuid::CharacteristicType::Navigation,
    QBluetoothUuid::CharacteristicType::PositionQuality,
    QBluetoothUuid::CharacteristicType::LNFeature,
    QBluetoothUuid::CharacteristicType::LNControlPoint,
    QBluetoothUuid::CharacteristicType::Elevation,
    QBluetoothUuid::CharacteristicType::Pressure,
    QBluetoothUuid::CharacteristicType::Temperature,
    QBluetoothUuid::CharacteristicType::Humidity,
    QBluetoothUuid::CharacteristicType::TrueWindSpeed,
    QBluetoothUuid::CharacteristicType::TrueWindDirection,
    QBluetoothUuid::CharacteristicType::ApparentWindSpeed,
    QBluetoothUuid::CharacteristicType::ApparentWindDirection,
    QBluetoothUuid::CharacteristicType::GustFactor,
    QBluetoothUuid::CharacteristicType::PollenConcentration,
    QBluetoothUuid::CharacteristicType::UVIndex,
    QBluetoothUuid::CharacteristicType::Irradiance,
    QBluetoothUuid::CharacteristicType::Rainfall,
    QBluetoothUuid::CharacteristicType::WindChill,
    QBluetoothUuid::CharacteristicType::HeatIndex,
    QBluetoothUuid::CharacteristicType::DewPoint,
    QBluetoothUuid::CharacteristicType::DescriptorValueChanged,
    QBluetoothUuid::CharacteristicType::AerobicHeartRateLowerLimit,
    QBluetoothUuid::CharacteristicType::AerobicThreshold,
    QBluetoothUuid::CharacteristicType::Age,
    QBluetoothUuid::CharacteristicType::AnaerobicHeartRateLowerLimit,
    QBluetoothUuid::CharacteristicType::AnaerobicHeartRateUpperLimit,
    QBluetoothUuid::CharacteristicType::AnaerobicThreshold,
    QBluetoothUuid::CharacteristicType::AerobicHeartRateUpperLimit,
    QBluetoothUuid::CharacteristicType::DateOfBirth,
    QBluetoothUuid::CharacteristicType::DateOfThresholdAssessment,
    QBluetoothUuid::CharacteristicType::EmailAddress,
    QBluetoothUuid::CharacteristicType::FatBurnHeartRateLowerLimit,
    QBluetoothUuid::CharacteristicType::FatBurnHeartRateUpperLimit,
    QBluetoothUuid::CharacteristicType::FirstName,
    QBluetoothUuid::CharacteristicType::FiveZoneHeartRateLimits,
    QBluetoothUuid::CharacteristicType::Gender,
    QBluetoothUuid::CharacteristicType::HeartRateMax,
    QBluetoothUuid::CharacteristicType::Height,
    QBluetoothUuid::CharacteristicType::HipCircumference,
    QBluetoothUuid::CharacteristicType::LastName,
    QBluetoothUuid::CharacteristicType::MaximumRecommendedHeartRate,
    QBluetoothUuid::CharacteristicType::RestingHeartRate,
    QBluetoothUuid::CharacteristicType::SportTypeForAerobicAnaerobicThresholds,
    QBluetoothUuid::CharacteristicType::ThreeZoneHeartRateLimits,
    QBluetoothUuid::CharacteristicType::TwoZoneHeartRateLimits,
    QBluetoothUuid::CharacteristicType::VO2Max,
    QBluetoothUuid::CharacteristicType::WaistCircumference,
    QBluetoothUuid::CharacteristicType::Weight,
    QBluetoothUuid::CharacteristicType::DatabaseChangeIncrement,
    QBluetoothUuid::CharacteristicType::UserIndex,
    QBluetoothUuid::CharacteristicType::BodyCompositionFeature,
    QBluetoothUuid::CharacteristicType::BodyCompositionMeasurement,
    QBluetoothUuid::CharacteristicType::WeightMeasurement,
    QBluetoothUuid::CharacteristicType::WeightScaleFeature,
    QBluetoothUuid::CharacteristicType::UserControlPoint,
    QBluetoothUuid::CharacteristicType::MagneticFluxDensity2D,
    QBluetoothUuid::CharacteristicType::MagneticFluxDensity3D,
    QBluetoothUuid::CharacteristicType::Language,
    QBluetoothUuid::CharacteristicType::BarometricPressureTrend,
};

static QVector<QBluetoothUuid::DescriptorType> g_descriptorUuids = {
    QBluetoothUuid::DescriptorType::CharacteristicExtendedProperties,
    QBluetoothUuid::DescriptorType::CharacteristicUserDescription,
    QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration,
    QBluetoothUuid::DescriptorType::ServerCharacteristicConfiguration,
    QBluetoothUuid::DescriptorType::CharacteristicPresentationFormat,
    QBluetoothUuid::DescriptorType::CharacteristicAggregateFormat,
    QBluetoothUuid::DescriptorType::ValidRange,
    QBluetoothUuid::DescriptorType::ExternalReportReference,
    QBluetoothUuid::DescriptorType::ReportReference,
    QBluetoothUuid::DescriptorType::EnvironmentalSensingConfiguration,
    QBluetoothUuid::DescriptorType::EnvironmentalSensingMeasurement,
    QBluetoothUuid::DescriptorType::EnvironmentalSensingTriggerSetting,
};

//==============================================================================
// Utils
//==============================================================================
static inline QString toHex(const QByteArray& a)
{
    return a.toHex(' ');
}

static inline QByteArray fromHex(const QString& s)
{
    return QByteArray::fromHex(s.toUtf8());
}

static inline QString toText(const QByteArray& a)
{
    return QString::fromUtf8(a);
}

static inline QByteArray fromText(const QString& s)
{
    return s.toUtf8();
}

static inline QString toBinary(const QByteArray& a)
{
    if (a.isEmpty())
        return QString();

    QString r;
    r.reserve(8 + 9 * (a.size() - 1));

    r.append(QString("%1").arg(static_cast<uint8_t>(a[0]), 8, 2, QChar('0')));
    for (qsizetype i = 1u; i < a.size(); ++i)
        r.append(QString(" %1").arg(static_cast<uint8_t>(a[i]), 8, 2, QChar('0')));

    return r;
}

static inline QByteArray fromBinary(const QString& s)
{
    QByteArray binary = s.toUtf8();
    QByteArray res((binary.size() + 7) / 8, Qt::Uninitialized);

    uint8_t rank = 0;
    uint8_t* result = reinterpret_cast<uint8_t*>(res.data()) + res.size();

    for (intptr_t i = binary.size() - 1; i >= 0; --i) {
            uint8_t ch = uint8_t(binary.at(i));
            if (ch != '0' && ch != '1')
                continue;

            if (rank == 0) {
                --result;
                *result = ch == '1';
            }
            else {
                *result |= (ch == '1') << rank;
            }

            if (++rank == 8)
                rank = 0;
    }

    res.remove(0, result - reinterpret_cast<const uint8_t*>(res.constData()));
    return res;
}

//==============================================================================
// Globals
//==============================================================================
Globals::~Globals() {}

QString Globals::valueToString(const QByteArray& value, DisplayMode mode) const
{
    switch (mode) {
        case Globals::DisplayMode::Hexadecimal:
            return toHex(value);

        case Globals::DisplayMode::Text:
            return toText(value);

        case Globals::DisplayMode::Binary:
            return toBinary(value);

        default:
            return QString();
    }
}

QByteArray Globals::valueFromString(const QString& value, DisplayMode mode) const
{
    switch (mode) {
        case Globals::DisplayMode::Hexadecimal:
            return fromHex(value);

        case Globals::DisplayMode::Text:
            return fromText(value);

        case Globals::DisplayMode::Binary:
            return fromBinary(value);

        default:
            return QByteArray();
    }
}

QString Globals::serviceName(const QBluetoothUuid& uuid) const
{
    for (int i = 0; i < g_serviceUuids.count(); ++i) {
        QBluetoothUuid::ServiceClassUuid value = g_serviceUuids[i];

        if (uuid == QBluetoothUuid(value))
            return QBluetoothUuid::serviceClassToString(value);
    }

    return tr("Unknown service");
}

QString Globals::characteristicName(const QBluetoothUuid& uuid) const
{
    for (int i = 0; i < g_characteristicUuids.count(); ++i) {
        QBluetoothUuid::CharacteristicType value = g_characteristicUuids[i];

        if (uuid == QBluetoothUuid(value))
            return QBluetoothUuid::characteristicToString(value);
    }

    return tr("Unknown characteristic");
}

QString Globals::descriptorName(const QBluetoothUuid& uuid) const
{
    for (int i = 0; i < g_descriptorUuids.count(); ++i) {
        QBluetoothUuid::DescriptorType value = g_descriptorUuids[i];

        if (uuid == QBluetoothUuid(value))
            return QBluetoothUuid::descriptorToString(value);
    }

    return tr("Unknown descriptor");
}

Globals* Globals::instance()
{
    static Globals instance;
    return &instance;
}

Globals::Globals() {}
