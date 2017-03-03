#include "archivo.h"

Archivo::Archivo(){
    sig = NULL;
    ant = NULL;
    nombre = "";
    ruta = "";
    tipo = "";
}

Archivo::Archivo(QString nombre, QString ruta, QString tipo){
    sig = NULL;
    ant = NULL;
    this->nombre = nombre;
    this->ruta = ruta;
    this->tipo = tipo;
}

QString Archivo::getNombre(){
    return nombre;
}

QString Archivo::getRuta(){
    return ruta;
}

QString Archivo::getTipo(){
    return tipo;
}

Archivo * Archivo::getSig(){
    return sig;
}

Archivo * Archivo::getAnt(){
    return ant;
}

void Archivo::setNombre(QString nombre){
    this->nombre = nombre;
}

void Archivo::setRuta(QString ruta){
    this->ruta = ruta;
}

void Archivo::setTipo(QString tipo){
    this->tipo = tipo;
}

void Archivo::setSig(Archivo * sig){
    this->sig = sig;
}

void Archivo::setAnt(Archivo * ant){
    this->ant = ant;
}
