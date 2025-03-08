#ifndef FILEWATCHERS_H
#define FILEWATCHERS_H

#include <QObject>
#include <QThread>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <io.h>
#include <fcntl.h>
#include <chrono>
#include <thread>

using namespace std;

namespace fs = filesystem;

class FileWatcher : public QObject {
    Q_OBJECT
public:
    explicit FileWatcher(QObject* parent = nullptr);
    void addFile(const string& filePath);
    void startWatching();

signals:
    void fileExists(const string& fileName, uintmax_t size);
    void fileChanged(const string& fileName, uintmax_t newSize);
    void fileNotFound(const string& fileName);

private:
    void checkFileStatus(const string& filePath);

    map<string, uintmax_t> _files;
};

#endif // FILEWATCHERS_H
