#include "filestorage.h"
#include <iostream>

FileStorage& FileStorage::getInstance() {
    static FileStorage instance;
    return instance;
}

void FileStorage::addFile(const string& filePath)
{
    lock_guard<mutex> lock(_mutex);
    if (!fs::exists(filePath))
    {
        emit fileNotFound(filePath);
        return;
    }
    uintmax_t fileSize = fs::file_size(filePath);
    _files[filePath] = fileSize;
    emit fileAdded(filePath);
}

void FileStorage::updateFileSize(const string& filePath)
{
    lock_guard<mutex> lock(_mutex);
    if (!fs::exists(filePath)) return;
    uintmax_t fileSize = fs::file_size(filePath);
    _files[filePath] = fileSize;
    emit fileSizeChanged(filePath, fileSize);
}

void FileStorage::removeFile(const string& filePath)
{
    lock_guard<mutex> lock(_mutex);
    _files.erase(filePath);
    emit fileRemoved(filePath);
}

map<string, uintmax_t> FileStorage::getFiles() const
{
    lock_guard<mutex> lock(_mutex);
    return _files;
}
