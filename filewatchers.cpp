#include "filewatchers.h"
#include "filestorage.h"
#include "logger.h"
#include <QCoreApplication>

FileWatcher::FileWatcher(QObject* parent) : QObject(parent)
{
    connectSignals();
}

void FileWatcher::startWatching()
{
    for (const auto& [filePath, _] : FileStorage::getInstance().getFiles())
    {
        StartCheckStatus(filePath);
    }

    while (true)
    {
        for (const auto& [filePath, _] : FileStorage::getInstance().getFiles())
        {
            checkFileStatus(filePath);
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void FileWatcher::connectSignals()
{
    connect(&FileStorage::getInstance(), &FileStorage::fileAdded, this, &FileWatcher::onFileAdded);
    connect(&FileStorage::getInstance(), &FileStorage::fileRemoved, this, &FileWatcher::onFileRemoved);
    connect(&FileStorage::getInstance(), &FileStorage::fileSizeChanged, this, &FileWatcher::onFileSizeChanged);
    connect(&FileStorage::getInstance(), &FileStorage::fileNotFound, this, &FileWatcher::onFileNotFound);
    connect(&FileStorage::getInstance(), &FileStorage::fileExistenceChanged, this, &FileWatcher::onFileExistenceChanged);
    connect(&FileStorage::getInstance(), &FileStorage::fileAlreadyExists, this, &FileWatcher::onFileAlreadyExists);
}

void FileWatcher::onFileAdded(const QString &filePath)
{
    Logger::logFileAdded(filePath);
}

void FileWatcher::onFileRemoved(const QString &filePath)
{
    Logger::logFileRemoved(filePath);
}

void FileWatcher::onFileSizeChanged(const QString &filePath, qint64 newSize)
{
    Logger::logFileSizeChanged(filePath, newSize);
}

void FileWatcher::onFileNotFound(const QString &filePath)
{
    Logger::logFileNotFound(filePath);
}

void FileWatcher::onFileExistenceChanged(const QString& filePath, bool exists, qint64 size)
{
    if (exists) {
        Logger::logFileRestored(filePath, size);
    } else {
        Logger::logFileNotFound(filePath);
    }
}

void FileWatcher::onFileAlreadyExists(const QString& filePath)
{
    Logger::logFileAlreadyExists(filePath);
}

void FileWatcher::checkFileStatus(const QString& filePath)
{
    QFileInfo fInfo(filePath);
    bool existsNow = fInfo.exists();
    qint64 sizeNow = existsNow ? fInfo.size() : 0;

    auto files = FileStorage::getInstance().getFiles();
    //Проверяем поменялось ли что то
    if (existsNow && files[filePath] != sizeNow) {
        FileStorage::getInstance().updateFileSize(filePath);
    }
    //Обновляем существование файла
    FileStorage::getInstance().setFileExistence(filePath, existsNow);
}

void FileWatcher::StartCheckStatus(const QString& filePath)
{
    QFileInfo fInfo = QFileInfo(filePath);
    if (fInfo.exists())
    {
        qint64 newSize = fInfo.size();
        Logger::logCurrentSize(filePath, newSize);
    }
}
