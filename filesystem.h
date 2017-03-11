#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QGraphicsScene>
#include "archivotexto.h"
#include "folder.h"
#include <QDebug>

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
    Folder * getParent(Archivo * arch);
    Folder * getParent(Archivo * arch, Folder * subRaiz, int cont);

    Folder * raiz, *actualFolder;

private:
    Archivo * temp;

    Archivo * cargarArchivo(QString, Folder*, int cont);
};

#endif // FILESYSTEM_H
