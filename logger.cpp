#include "logger.h"

void Logger::logFileAdded(const QString &filePath) {
    qDebug() << "[LOG] File added:" << filePath;
}

void Logger::logFileRemoved(const QString &filePath) {
    qDebug() << "[LOG] File removed:" << filePath;
}

void Logger::logFileSizeChanged(const QString &filePath, qint64 size) {
    qDebug() << "[LOG] File size changed:" << filePath << "New size:" << size;
}

void Logger::logFileNotFound(const QString &filePath) {
    qDebug() << "[LOG] File not found:" << filePath;
}

void Logger::logCurrentSize(const QString &filePath, qint64 size) {
    qDebug() << "[LOG] File:" << filePath << " Size: " << size;
}
