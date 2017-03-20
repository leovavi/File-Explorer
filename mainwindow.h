#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QVector>
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
    void on_actionCrear_Nuevo_Folder_triggered();
    void on_actionCrear_Nuevo_Archivo_de_Texto_triggered();
    void on_btnCopy_clicked();
    void on_btnPaste_clicked();
    void on_btnBack_clicked();
    void on_actionEliminar_Archivo_triggered();
    void renombrarArchivos(Folder * f);
    void on_actionRenombrar_Archivo_triggered();
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * key);
    void keyReleaseEvent(QKeyEvent * key);
    void on_actionSalir_triggered();
    void on_actionCopiar_triggered();
    void on_actionPegar_triggered();
    void on_treeWidget_clicked(const QModelIndex &index);

    void on_btnFront_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QTreeWidgetItem * treeItem, * copyTreeItem;
    QIcon * icon;
    Files * selectedItem;
    FileSystem * fs;
    Archivo * selected, *clipboard;
    Folder * actualFolder;
    QVector<QString> paths;
    bool keyPressed;
    int current;

    void pintarFiles();
    void refresh();
    void deleteFromTree();
    void refreshTree(QString ruta);
    void addPath();
    QTreeWidgetItem * getHijo(QString nombre);
    QString getPath(QTreeWidgetItem * item);
};

#endif // MAINWINDOW_H
