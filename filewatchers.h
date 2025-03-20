#ifndef FILEWATCHERS_H
#define FILEWATCHERS_H

#include <QObject>
#include <QThread>
#include <io.h>
#include <fcntl.h>
#include <QTextStream>
#include <QDebug>

using namespace std;

class FileWatcher : public QObject {
    Q_OBJECT
public:
    explicit FileWatcher(QObject* parent = nullptr);
    void startWatching();

private:
    void connectSignals();

private slots:
    void onFileAdded(const QString& filePath);
    void onFileRemoved(const QString& filePath);
    void onFileSizeChanged(const QString& filePath, qint64 newSize);
    void onFileNotFound(const QString& filePath);
    void onFileExistenceChanged(const QString &filePath, bool exists, qint64 size);
    void onFileAlreadyExists(const QString &filePath);
private:
    void checkFileStatus(const QString& filePath);
    void StartCheckStatus(const QString &filePath);

};

#endif // FILEWATCHERS_H
