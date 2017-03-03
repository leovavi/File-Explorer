#ifndef ARCHIVOTEXTO_H
#define ARCHIVOTEXTO_H
#include "archivo.h"

class ArchivoTexto : public Archivo
{
public:
    ArchivoTexto(QString, QString);

    QString getContenido();

    void setContenido(QString);

private:
    QString contenido;
};

#endif // ARCHIVOTEXTO_H
