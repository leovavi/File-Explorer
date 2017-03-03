#ifndef LISTA_H
#define LISTA_H
#include "archivo.h"

class Lista
{
public:
    Lista();
    int tamano();
    void agregar(Archivo*);
    int buscar(Archivo*);
    Archivo * obtener(int pos);
    void eliminar(Archivo*);

private:
    Archivo *inicio, *fin;
    int longitudLista;
};

#endif // LISTA_H
