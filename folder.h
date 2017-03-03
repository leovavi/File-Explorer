#ifndef FOLDER_H
#define FOLDER_H
#include "lista.h"

class Folder : public Archivo
{
public:
    Folder(QString, QString);

    int getCantidadArchivos();
    void agregarArchivo(Archivo*);
    int buscarArchivo(Archivo*);
    Archivo * obtenerArchivo(int);
    void eliminarArchivo(Archivo*);
    Lista * getLista();

private:
    Lista * archivos;
};

#endif // FOLDER_H
