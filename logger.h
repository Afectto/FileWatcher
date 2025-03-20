#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QDebug>

class Logger {
public:
    static void logFileAdded(const QString& filePath);

    static void logFileRemoved(const QString& filePath);

    static void logFileSizeChanged(const QString& filePath, qint64 size);

    static void logFileNotFound(const QString& filePath);

    static void logCurrentSize(const QString& filePath, qint64 size);
    static void logFileRestored(const QString& filePath, qint64 size);
    static void logFileAlreadyExists(const QString &filePath);
};
#endif // LOGGER_H
