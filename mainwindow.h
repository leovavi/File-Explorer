#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "filesystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnFolder_clicked();

    void on_btnArchivo_clicked();

    void setSelected(Folder * f);

    void pintarFiles();
    void refresh();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    Folder * selected;
};

#endif // MAINWINDOW_H
