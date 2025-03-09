#ifndef FILESTORAGE_H
#define FILESTORAGE_H
#include <QObject>
#include <map>
#include <string>
#include <mutex>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

class FileStorage : public QObject {
    Q_OBJECT
public:
    static FileStorage& getInstance();
    void addFile(const string& filePath);
    void removeFile(const string& filePath);
    map<string, uintmax_t> getFiles() const;
    void updateFileSize(const string &filePath);

signals:
    void fileAdded(const string& filePath);
    void fileRemoved(const string& filePath);
    void fileSizeChanged(const string& filePath, uintmax_t newSize);
    void fileNotFound(const string& filePath);

private:
    FileStorage() = default;
    ~FileStorage() = default;
    FileStorage(const FileStorage&) = delete;
    FileStorage& operator=(const FileStorage&) = delete;

    map<string, uintmax_t> _files;
    mutable mutex _mutex;
};


#endif // FILESTORAGE_H
