#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <iostream>
#include <QString>

using namespace std;

class Archivo
{
public:
    Archivo();
    Archivo(QString, QString, QString);

    QString getNombre();
    QString getRuta();
    QString getTipo();
    Archivo * getSig();
    Archivo * getAnt();

    void setNombre(QString);
    void setRuta(QString);
    void setTipo(QString);
    void setSig(Archivo*);
    void setAnt(Archivo*);

private:
    QString nombre, ruta, tipo;
    Archivo *sig, *ant;
};

#endif // ARCHIVO_H
