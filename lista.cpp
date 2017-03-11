#include "lista.h"

Lista::Lista()
{
    inicio = NULL;
    fin = NULL;
    longitudLista = 0;
}

int Lista::tamano(){
    return longitudLista;
}

void Lista::agregar(Archivo * arch){
    if(inicio == NULL){
        inicio = arch;
        fin = arch;
        longitudLista++;
        return;
    }

    Archivo * temp = inicio;

    while(temp->getSig() != NULL)
        temp = temp->getSig();

    temp->setSig(arch);
    arch->setAnt(temp);
    fin = arch;
    longitudLista++;
}

int Lista::buscar(Archivo * arch){
    Archivo * temp = inicio;

    for(int i = 0; i<longitudLista; i++){
        if(temp == arch)
            return i;
        temp = temp->getSig();
    }

    return -1;
}

Archivo * Lista::obtener(int pos){
    if(pos>=0 && pos<longitudLista){
        Archivo * temp = inicio;

        for(int i = 0; i<pos; i++)
            temp = temp->getSig();

        return temp;
    }

    return NULL;
}

void Lista::eliminar(Archivo * arch){
    if(longitudLista != 0){
        if(inicio == arch){
            inicio = inicio->getSig();
            longitudLista--;
            if(longitudLista == 0)
                fin = NULL;
            return;
        }
        else if(fin == arch){
            fin = fin->getAnt();
            if(fin != NULL)
                fin->setSig(NULL);
            longitudLista--;
            return;
        }

        Archivo * temp = inicio;

        while(temp != arch)
            temp = temp->getSig();

        temp->getAnt()->setSig(temp->getSig());
        temp->getSig()->setAnt(temp->getAnt());
        longitudLista--;
        delete temp;
    }
}
