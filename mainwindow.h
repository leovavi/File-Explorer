#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "filesystem.h"
#include "files.h"
#include "input.h"

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

    void pintarFiles();
    void refresh();

    void on_actionCrear_Nuevo_Folder_triggered();

    void on_actionCrear_Nuevo_Archivo_de_Texto_triggered();

    void on_btnCopy_clicked();

    void on_btnBack_clicked();

    void mouseDoubleClickEvent(QMouseEvent * event);

    void mousePressEvent(QMouseEvent * event);

    void on_actionEliminar_Archivo_triggered();

    void on_actionRenombrar_Archivo_triggered();

    void on_btnPaste_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    Files * selectedItem;
    FileSystem * fs;
    Archivo * selected, *clipboard;
    Folder * actualFolder;
};

#endif // MAINWINDOW_H
