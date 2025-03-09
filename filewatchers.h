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

class FileWatcher : public QObject {
    Q_OBJECT
public:
    explicit FileWatcher(QObject* parent = nullptr);
    void startWatching();

private:
    void connectSignals();

private slots:
    void onFileAdded(const string& filePath);

    void onFileRemoved(const string& filePath);

    void onFileSizeChanged(const string& filePath, qint64 newSize);

    void onFileNotFound(const string& filePath);
private:
    void checkFileStatus(const string& filePath);
    std::map<std::string, bool> _fileExistNotified;
};

#endif // FILEWATCHERS_H
