#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QGraphicsScene>
#include "archivotexto.h"
#include "folder.h"
#include "files.h"

class FileSystem
{
public:
    FileSystem();
    void agregarArchivo(Folder*, QString, int);
    Lista * listarArchivos(Folder*);
    Archivo * cargarArchivo(QString);
    void eliminarArchivo(QString);
    void copiar(Folder*, QString, Folder*);
    int buscar(Folder*, QString, QString);


    Folder * raiz, *selected;

private:
    Archivo * temp;

    int posX, posY;

    QGraphicsScene * scene;
    QGraphicsView * view;
    QLabel * label;

    Archivo * cargarArchivo(QString, Folder*);
    void eliminarArchivo(QString, Folder*);
};

#endif // FILESYSTEM_H
