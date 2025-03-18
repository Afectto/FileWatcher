#ifndef FILESTORAGE_H
#define FILESTORAGE_H
#include <QObject>
#include <map>
#include <string>
#include <mutex>
#include <QFileInfo>

using namespace std;

class FileStorage : public QObject {
    Q_OBJECT
public:
    static FileStorage& getInstance();
    void addFile(const QString& filePath);
    void removeFile(const QString& filePath);
    map<QString, qint64> getFiles() const;
    void updateFileSize(const QString &filePath);

signals:
    void fileAdded(const QString& filePath);
    void fileRemoved(const QString& filePath);
    void fileSizeChanged(const QString& filePath, qint64 newSize);
    void fileNotFound(const QString& filePath);

private:
    FileStorage() = default;
    ~FileStorage() = default;
    FileStorage(const FileStorage&) = delete;
    FileStorage& operator=(const FileStorage&) = delete;

    map<QString, qint64> _files;
};


#endif // FILESTORAGE_H
