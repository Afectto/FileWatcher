#include "filewatchers.h"
#include "filestorage.h"
#include <filesystem>
#include <QCoreApplication>

namespace fs = filesystem;

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

void FileWatcher::onFileAdded(const string &filePath)
{
    qDebug() << "File added:" << filePath;
}

void FileWatcher::onFileRemoved(const string &filePath)
{
    qDebug() << "File removed:" << filePath;
}

void FileWatcher::onFileSizeChanged(const string &filePath, qint64 newSize)
{
    qDebug() << "File size changed:" << filePath << "New size:" << newSize;
}

void FileWatcher::onFileNotFound(const string &filePath)
{
    qDebug() << "File not found:" << filePath;
}

void FileWatcher::checkFileStatus(const string& filePath)
{
    if (!fs::exists(filePath))
    {
        FileStorage::getInstance().removeFile(filePath);
        return;
    }

    uintmax_t fileSize = fs::file_size(filePath);
    auto files = FileStorage::getInstance().getFiles();

    if (files[filePath] != fileSize)
    {
        FileStorage::getInstance().updateFileSize(filePath); // Обновление размера файла
    }
}
