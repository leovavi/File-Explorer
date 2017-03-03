#include "mainwindow.h"
#include <QApplication>
#include "folder.h"
#include "filesystem.h"

Folder * selected;
FileSystem * fs;

int main(int argc, char *argv[])
{
    fs = new FileSystem();
    selected = fs->raiz;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
