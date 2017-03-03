#include "filesystem.h"

FileSystem::FileSystem()
{
    temp = NULL;
    raiz = new Folder("raiz", "raiz");
    selected = raiz;
    posX = 0;
    posY = 0;
}

void FileSystem::agregarArchivo(Folder * destino, QString nombre, int tipo){
    int cant = buscar(destino, nombre, (tipo == 1 ? "ArchivoTexto" : "Folder"));

    if(cant != 0){
        nombre = nombre +"("+QString::number(cant)+")";
    }

    QString ruta = destino->getRuta()+"/"+nombre;

    if(tipo == 1){
        ArchivoTexto * archivo = new ArchivoTexto(nombre, ruta);
        destino->agregarArchivo(archivo);
    }
    else if(tipo == 2){
        Folder * folder = new Folder(nombre, ruta);
        destino->agregarArchivo(folder);
    }
}

Lista * FileSystem::listarArchivos(Folder * origen){
    return origen->getLista();
}

Archivo * FileSystem::cargarArchivo(QString ruta){
    return cargarArchivo(ruta, raiz);
}

Archivo * FileSystem::cargarArchivo(QString ruta, Folder * subRaiz){
    for(int i = 0; i<subRaiz->getCantidadArchivos(); i++){
        temp = subRaiz->obtenerArchivo(i);

        if(temp->getRuta() == ruta)
            return temp;

        else if(temp->getTipo() == "Folder")
            return cargarArchivo(ruta, (Folder*)temp);
    }

    if(subRaiz == raiz)
        return NULL;
}

void FileSystem::eliminarArchivo(QString ruta){
    eliminarArchivo(ruta, raiz);
}

void FileSystem::eliminarArchivo(QString ruta, Folder * subRaiz){
    for(int i = 0; i<subRaiz->getCantidadArchivos(); i++){
        temp = subRaiz->obtenerArchivo(i);

        if(temp->getRuta() == ruta){
            subRaiz->eliminarArchivo(temp);
            return;
        }

        else if(temp->getTipo() == "Folder")
            return eliminarArchivo(ruta, (Folder*)temp);
    }
}

void FileSystem::copiar(Folder * origen, QString nombre, Folder * destino){
    for(int i = 0; i<origen->getCantidadArchivos(); i++){
        temp = origen->obtenerArchivo(i);

        if(temp->getNombre() == nombre)
            break;
    }

    if(temp != NULL){
        QString ruta = destino->getRuta()+"/"+nombre;

        if(temp->getTipo() == "Folder"){
            Folder * folder = new Folder(nombre, ruta);
            Folder * conv = (Folder*)temp;

            for(int i = 0; i<conv->getCantidadArchivos(); i++)
                folder->agregarArchivo(conv->obtenerArchivo(i));

            destino->agregarArchivo(folder);
        }
        else{
            ArchivoTexto * text = new ArchivoTexto(nombre, ruta);
            text->setContenido(((ArchivoTexto*)temp)->getContenido());
            destino->agregarArchivo(text);
        }
    }
}

int FileSystem::buscar(Folder * origen, QString nombre, QString tipo){
    Lista * l = origen->getLista();
    int cant = 0;

    for(int i = 0; i<origen->getCantidadArchivos(); i++){
        Archivo * temp = l->obtener(i);

        if((temp->getNombre() == nombre || temp->getNombre().contains(nombre+"(")) && temp->getTipo() == tipo)
            cant++;
    }
    return cant;
}
