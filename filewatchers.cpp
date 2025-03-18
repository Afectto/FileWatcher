#include "filewatchers.h"
#include "filestorage.h"
#include <QCoreApplication>

FileWatcher::FileWatcher(QObject* parent) : QObject(parent)
{
    connectSignals();
}

void FileWatcher::startWatching()
{
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
}

void FileWatcher::onFileAdded(const QString &filePath)
{
    qDebug() << "File added:" << filePath;
}

void FileWatcher::onFileRemoved(const QString &filePath)
{
    qDebug() << "File removed:" << filePath;
}

void FileWatcher::onFileSizeChanged(const QString &filePath, qint64 newSize)
{
    qDebug() << "File size changed:" << filePath << "New size:" << newSize;
}

void FileWatcher::onFileNotFound(const QString &filePath)
{
    qDebug() << "File not found:" << filePath;
}

void FileWatcher::checkFileStatus(const QString& filePath)
{
    QFileInfo fInfo = QFileInfo(filePath);
    if (!fInfo.exists())
    {
        FileStorage::getInstance().removeFile(filePath);
        return;
    }

    qint64 fileSize = fInfo.size();
    auto files = FileStorage::getInstance().getFiles();

    if (files[filePath] != fileSize)
    {
        FileStorage::getInstance().updateFileSize(filePath); // Обновление размера файла
    }
}
