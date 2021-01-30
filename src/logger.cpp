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

#include "logger.h"
#include "settings.h"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QMetaEnum>

Logger::Logger(QObject* parent) :
    QObject(parent),
    m_maxLength(INT_MAX)
{
    QObject::connect(
        Settings::instance(),
        &Settings::settingsChanged,
        this,
        &Logger::handleSettingsChanged);

    this->handleSettingsChanged();
}

Logger::~Logger() {}

QList<LogEntry> Logger::entries() const
{
    return m_entries;
}

void Logger::addEntry(const LogEntry& entry)
{
    bool removeFirst = m_entries.count() == m_maxLength;

    Q_EMIT entryAboutToBeAdded();
    if (removeFirst)
        Q_EMIT entryAboutToBeRemoved();

    m_entries.append(entry);
    if (removeFirst)
        m_entries.removeFirst();

    Q_EMIT entryAdded();
    if (removeFirst)
        Q_EMIT entryRemoved();
}

void Logger::clearEntries()
{
    if (!m_entries.isEmpty()) {
        Q_EMIT entriesAboutToChange();
        m_entries.clear();
        Q_EMIT entriesChanged();
    }
}

bool Logger::exportEntries(const QUrl& url)
{
    if (!url.isLocalFile())
        return false;

    switch (Settings::instance()->logExportFormat()) {
        case Globals::LogFormat::Csv:
            return this->exportEntriesToCsv(url);

        case Globals::LogFormat::Json:
            return this->exportEntriesToJson(url);

        default:
            return false;
    }
}

void Logger::handleSettingsChanged()
{
    int maxLength = Settings::instance()->logMaximumLength();
    if (m_maxLength != maxLength) {
        bool removeFirsts = m_entries.count() > maxLength;

        if (removeFirsts)
            Q_EMIT entriesAboutToChange();

        while (m_entries.count() > maxLength)
            m_entries.removeFirst();

        m_maxLength = maxLength;

        if (removeFirsts)
            Q_EMIT entriesChanged();
    }
}

bool Logger::exportEntriesToCsv(const QUrl& url)
{
    QString none("None");
    QList<QStringList> lines;

    QStringList line;
    line << "dateTime";
    line << "dateTime";
    line << "event";
    line << "deviceAddress";
    line << "deviceName";
    line << "serviceUuid";
    line << "serviceName";
    line << "characteristicUuid";
    line << "characteristicName";
    line << "descriptorUuid";
    line << "descriptorName";
    line << "value";
    line << "errorMessage";
    lines.append(line);

    for (const LogEntry& entry : m_entries) {
        QStringList line;

        QMetaEnum metaEnum = QMetaEnum::fromType<LogEntry::Event>();
        line << entry.dateTime().toString();
        line << metaEnum.valueToKey(static_cast<int>(entry.event()));

        if (!entry.deviceAddress().isNull()) {
            line << entry.deviceAddress().toString();
            line << entry.deviceName();
        }
        else {
            line << none;
            line << none;
        }

        if (!entry.serviceUuid().isNull()) {
            line << entry.serviceUuid().toString(QUuid::WithoutBraces);
            line << Globals::instance()->serviceName(entry.serviceUuid());
        }
        else {
            line << none;
            line << none;
        }

        if (!entry.characteristicUuid().isNull()) {
            line << entry.characteristicUuid().toString(QUuid::WithoutBraces);
            line << Globals::instance()->characteristicName(entry.characteristicUuid());
        }
        else {
            line << none;
            line << none;
        }

        if (!entry.descriptorUuid().isNull()) {
            line << entry.descriptorUuid().toString(QUuid::WithoutBraces);
            line << Globals::instance()->descriptorName(entry.descriptorUuid());
        }
        else {
            line << none;
            line << none;
        }

        if (!entry.value().isEmpty()) {
            Globals::DisplayMode displayMode;
            if (!entry.descriptorUuid().isNull()) {
                displayMode = Settings::instance()->descriptorDisplayMode(
                    entry.descriptorUuid());
            }
            else {
                displayMode = Settings::instance()->characteristicDisplayMode(
                    entry.characteristicUuid());
            }

            line << Globals::instance()->valueToString(entry.value(), displayMode);
        }
        else {
            line << none;
        }

        if (!entry.errorMessage().isEmpty())
            line << entry.errorMessage();
        else
            line << none;

        lines.append(line);
    }

    QFile file(url.toLocalFile());
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    for (const QStringList& line : lines) {
        QByteArray buf = (line.join(", ") + "\n").toUtf8();
        if (file.write(buf) != buf.size())
            return false;
    }

    file.close();
    return true;
}

bool Logger::exportEntriesToJson(const QUrl& url)
{
    QString none("None");
    QJsonArray jsonEntries;

    for (const LogEntry& entry : m_entries) {
        QJsonObject jsonEntry;

        jsonEntry.insert(
            "dateTime",
            entry.dateTime().toString());

        QMetaEnum metaEnum = QMetaEnum::fromType<LogEntry::Event>();
        jsonEntry.insert(
            "event",
            metaEnum.valueToKey(static_cast<int>(entry.event())));

        if (!entry.deviceAddress().isNull()) {
            jsonEntry.insert(
                "deviceAddress",
                entry.deviceAddress().toString());

            jsonEntry.insert(
                "deviceName",
                entry.deviceName());
        }
        else {
            jsonEntry.insert("deviceAddress", none);
            jsonEntry.insert("deviceName", none);
        }

        if (!entry.serviceUuid().isNull()) {
            jsonEntry.insert(
                "serviceUuid",
                entry.serviceUuid().toString(QUuid::WithoutBraces));

            jsonEntry.insert(
                "serviceName",
                Globals::instance()->serviceName(entry.serviceUuid()));
        }
        else {
            jsonEntry.insert("serviceUuid", none);
            jsonEntry.insert("serviceName", none);
        }

        if (!entry.characteristicUuid().isNull()) {
            jsonEntry.insert(
                "characteristicUuid",
                entry.characteristicUuid().toString(QUuid::WithoutBraces));

            jsonEntry.insert(
                "characteristicName",
                Globals::instance()->characteristicName(entry.characteristicUuid()));
        }
        else {
            jsonEntry.insert("characteristicUuid", none);
            jsonEntry.insert("characteristicName", none);
        }

        if (!entry.descriptorUuid().isNull()) {
            jsonEntry.insert(
                "descriptorUuid",
                entry.descriptorUuid().toString(QUuid::WithoutBraces));

            jsonEntry.insert(
                "descriptorUuid",
                Globals::instance()->descriptorName(entry.descriptorUuid()));
        }
        else {
            jsonEntry.insert("descriptorUuid", none);
            jsonEntry.insert("descriptorUuid", none);
        }

        if (!entry.value().isEmpty()) {
            Globals::DisplayMode displayMode;
            if (!entry.descriptorUuid().isNull()) {
                displayMode = Settings::instance()->descriptorDisplayMode(
                    entry.descriptorUuid());
            }
            else {
                displayMode = Settings::instance()->characteristicDisplayMode(
                    entry.characteristicUuid());
            }

            jsonEntry.insert(
                "value",
                Globals::instance()->valueToString(entry.value(), displayMode));
        }
        else {
            jsonEntry.insert("value", none);
        }

        if (!entry.errorMessage().isEmpty()) {
            jsonEntry.insert(
                "errorMessage",
                entry.errorMessage());
        }
        else {
            jsonEntry.insert("errorMessage", none);
        }

        jsonEntries.append(jsonEntry);
    }

    QFile file(url.toLocalFile());
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    QJsonDocument document;
    document.setArray(jsonEntries);

    QByteArray buf = document.toJson();
    if (file.write(buf) != buf.size())
        return false;

    file.close();
    return true;
}
