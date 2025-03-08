#include <QCoreApplication>
#include "filewatchers.h"

void onFileExists(const string& fileName, uintmax_t size) {
    qDebug() << "[Сигнал] Файл существует: "
             << QString::fromStdString(fileName)
             << ", Размер: " << size << " байт";
}

void onFileChanged(const string& fileName, uintmax_t newSize) {
    qDebug() << "[Сигнал] Файл изменен: "
             << QString::fromStdString(fileName)
             << ", Новый размер: " << newSize << " байт";
}

void onFileNotFound(const string& fileName) {
    qDebug() << "[Сигнал] Файл не существует: "
             << QString::fromStdString(fileName);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Russian");
    FileWatcher watcher;

    QObject::connect(&watcher, &FileWatcher::fileExists, &onFileExists);
    QObject::connect(&watcher, &FileWatcher::fileChanged, &onFileChanged);
    QObject::connect(&watcher, &FileWatcher::fileNotFound, &onFileNotFound);

    QTextStream qin(stdin);
    qDebug() << "Введите путь к файлу для наблюдения или 'exit' для выхода: " ;
    while (true)
    {
        QString line = qin.readLine();
        if (line == "exit") break;
        watcher.addFile(line.toStdString());
    }
    QThread::create([&watcher]() { watcher.startWatching(); })->start();
    return a.exec();
}
