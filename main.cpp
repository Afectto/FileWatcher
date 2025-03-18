#include <QCoreApplication>
#include "filewatchers.h"
#include "filestorage.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    _setmode(_fileno(stdout), _O_U16TEXT);
    setlocale(LC_ALL, "Russian");
    FileWatcher watcher;
    FileStorage& observer = FileStorage::getInstance();

    QTextStream qin(stdin);
    qDebug() << "Введите путь к файлу для наблюдения или 'exit' для выхода: " ;
    while (true)
    {
        QString line = qin.readLine();
        if (line == "exit") break;
        observer.addFile(line);
    }
    QThread::create([&watcher]() { watcher.startWatching(); })->start();
    return a.exec();
}
