#include "filestorage.h"

FileStorage& FileStorage::getInstance() {
    static FileStorage instance;
    return instance;
}

void FileStorage::addFile(const QString& filePath)
{
    QFileInfo fInfo = QFileInfo(filePath);
    if (!fInfo.exists())
    {
        emit fileNotFound(filePath);
        return;
    }
    qint64 fileSize = fInfo.size();
    _files[filePath] = fileSize;
    emit fileAdded(filePath);
}

void FileStorage::updateFileSize(const QString& filePath)
{
    QFileInfo fInfo = QFileInfo(filePath);
    if (!fInfo.exists()) return;
    qint64 fileSize = fInfo.size();
    _files[filePath] = fileSize;
    emit fileSizeChanged(filePath, fileSize);
}

void FileStorage::removeFile(const QString& filePath)
{
    _files.erase(filePath);
    emit fileRemoved(filePath);
}

map<QString, qint64> FileStorage::getFiles() const
{
    return _files;
}
