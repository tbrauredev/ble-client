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

#ifndef LOGGER_H_
#define LOGGER_H_

#include "log_entry.h"

#include <QtCore/QObject>
#include <QtCore/QUrl>

class Logger : public QObject
{
    Q_OBJECT

public:
    explicit Logger(QObject* parent = nullptr);

    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;

    Logger& operator = (const Logger&) = delete;
    Logger& operator = (Logger&&) = delete;

    ~Logger() override;

    QList<LogEntry> entries() const;
    Q_SIGNAL void entriesAboutToChange();
    Q_SIGNAL void entriesChanged();

    Q_SIGNAL void entryAboutToBeAdded();
    Q_SIGNAL void entryAdded();

    Q_SIGNAL void entryAboutToBeRemoved();
    Q_SIGNAL void entryRemoved();

    Q_INVOKABLE void addEntry(const LogEntry& entry);
    Q_INVOKABLE void clearEntries();

    Q_INVOKABLE bool exportEntries(const QUrl& url);

private:
    Q_SLOT void handleSettingsChanged();

    bool exportEntriesToCsv(const QUrl& url);
    bool exportEntriesToJson(const QUrl& url);

    QList<LogEntry> m_entries;
    int m_maxLength;
};

#endif  // LOGGER_H_
