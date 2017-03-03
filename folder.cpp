#include "folder.h"

Folder::Folder(QString nombre, QString ruta) : Archivo(nombre, ruta, "Folder"){
    archivos = new Lista();
}

int Folder::getCantidadArchivos(){
    return archivos->tamano();
}

void Folder::agregarArchivo(Archivo * arch){
    archivos->agregar(arch);
}

int Folder::buscarArchivo(Archivo * arch){
    return archivos->buscar(arch);
}

Archivo * Folder::obtenerArchivo(int pos){
    return archivos->obtener(pos);
}

void Folder::eliminarArchivo(Archivo * arch){
    archivos->eliminar(arch);
}

Lista * Folder::getLista(){
    return archivos;
}
