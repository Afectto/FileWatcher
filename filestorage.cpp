#include "filestorage.h"

FileStorage& FileStorage::getInstance() {
    static FileStorage instance;
    return instance;
}

void FileStorage::addFile(const QString& filePath)
{
    // Проверка: уже добавлен?
    if (_files.find(filePath) != _files.end()) {
        emit fileAlreadyExists(filePath);
        return;  // Не добавляем дубликат
    }
    QFileInfo fInfo = QFileInfo(filePath);
    if (!fInfo.exists())
    {
        emit fileNotFound(filePath);
        return;
    }
    qint64 fileSize = fInfo.size();
    _files[filePath] = fileSize;
    _existence[filePath] = true;
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

bool FileStorage::wasFileExisting(const QString &filePath) const {
    auto it = _existence.find(filePath);
    return (it != _existence.end()) ? it->second : false;
}

void FileStorage::setFileExistence(const QString &filePath, bool exists) {
    bool prevExists = _existence[filePath];
    _existence[filePath] = exists;

    if (prevExists != exists) {
        qint64 size = 0;
        QFileInfo fInfo(filePath);
        if (fInfo.exists()) {
            size = fInfo.size();
        }
        emit fileExistenceChanged(filePath, exists, size);
    }
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
