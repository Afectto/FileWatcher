#include "filewatchers.h"

FileWatcher::FileWatcher(QObject* parent) : QObject(parent) {}

void FileWatcher::addFile(const string& filePath)
{
    if (!fs::exists(filePath))
    {
        emit fileNotFound(filePath);
        return;
    }
    _files[filePath] = fs::file_size(filePath);
    emit fileExists(filePath, _files[filePath]);
}

void FileWatcher::startWatching()
{
    while (true)
    {
        for (const auto& [filePath, _] : _files)
        {
            checkFileStatus(filePath);
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void FileWatcher::checkFileStatus(const string& filePath)
{
    if (!fs::exists(filePath))
    {
        emit fileNotFound(filePath);
        return;
    }

    uintmax_t fileSize = fs::file_size(filePath);
    if (fileSize != _files[filePath])
    {
        emit fileChanged(filePath, fileSize);
    }

    _files[filePath] = fileSize;
}
