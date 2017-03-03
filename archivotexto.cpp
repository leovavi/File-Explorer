#include "archivotexto.h"

ArchivoTexto::ArchivoTexto(QString nombre, QString ruta) : Archivo(nombre, ruta, "ArchivoTexto"){
    contenido = "";
}

QString ArchivoTexto::getContenido(){
    return contenido;
}

void ArchivoTexto::setContenido(QString contenido){
    this->contenido = contenido;
}


