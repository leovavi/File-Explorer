#include "filesystem.h"

FileSystem::FileSystem()
{
    temp = NULL;
    raiz = new Folder("raiz", "raiz");
    actualFolder = raiz;
}

Archivo * FileSystem::agregarArchivo(Folder * destino, QString nombre, int tipo){
    int cant = buscar(destino, nombre, (tipo == 1 ? "ArchivoTexto" : "Folder"));

    if(cant != 0)
        nombre = nombre +"("+QString::number(cant)+")";

    QString ruta = destino->getRuta()+"/"+nombre;

    if(tipo == 1){
        ArchivoTexto * archivo = new ArchivoTexto(nombre, ruta);
        destino->agregarArchivo(archivo);
        return archivo;
    }
    else if(tipo == 2){
        Folder * folder = new Folder(nombre, ruta);
        destino->agregarArchivo(folder);
        return folder;
    }
}

Lista * FileSystem::listarArchivos(Folder * origen){
    return origen->getLista();
}

Archivo * FileSystem::cargarArchivo(QString ruta){
    if(ruta == "raiz")
        return raiz;

    return cargarArchivo(ruta, raiz, 1);
}

Archivo * FileSystem::cargarArchivo(QString ruta, Folder * subRaiz, int cont){
    for(int i = 0; i<subRaiz->getCantidadArchivos(); i++){
        temp = subRaiz->obtenerArchivo(i);

        if(temp->getRuta() == ruta)
            return temp;

        else if(temp->getTipo() == "Folder"){
            QStringList split = ruta.split('/');
            if(split.at(cont) == temp->getNombre())
                return cargarArchivo(ruta, (Folder*)temp, cont+1);
        }
    }

    if(subRaiz == raiz)
        return NULL;
}

void FileSystem::eliminarArchivo(QString ruta){
    Archivo * temp = cargarArchivo(ruta);
    Folder * actual = getParent(temp);

    if(temp != NULL)
        actual->eliminarArchivo(temp);
}

QString FileSystem::copiar(Folder * origen, QString nombre, Folder * destino){
    for(int i = 0; i<origen->getCantidadArchivos(); i++){
        temp = origen->obtenerArchivo(i);

        if(temp->getNombre() == nombre)
            break;
    }

    if(temp != NULL){
        int cant = buscar(destino, nombre, (temp->getTipo() == "Folder" ? "Folder" : "ArchivoTexto"));
        if(cant != 0)
            nombre = nombre+"("+QString::number(cant)+")";
        QString ruta = destino->getRuta()+"/"+nombre;

        if(temp->getTipo() == "Folder"){
            Folder * folder = copiarFolder((Folder*)temp, nombre, ruta);
            destino->agregarArchivo(folder);
        }
        else{
            ArchivoTexto * text = copiarArchivo((ArchivoTexto*)temp, nombre, ruta);
            destino->agregarArchivo(text);
        }
        return nombre;
    }
}

Folder * FileSystem::copiarFolder(Folder *origen, QString nombre, QString ruta){
    Folder * nuevo = new Folder(nombre, ruta);

    for(int i = 0; i<origen->getCantidadArchivos(); i++){
        Archivo * obt = origen->obtenerArchivo(i);
        nombre = obt->getNombre();

        if(obt->getTipo() == "Folder"){
            Folder * fcopiado = copiarFolder((Folder*)obt, nombre, ruta+"/"+nombre);
            nuevo->agregarArchivo(fcopiado);
        }else{
            ArchivoTexto * text = copiarArchivo((ArchivoTexto*)obt, obt->getNombre(), ruta+"/"+obt->getNombre());
            nuevo->agregarArchivo(text);
        }
    }

    return nuevo;
}

ArchivoTexto * FileSystem::copiarArchivo(ArchivoTexto * origen, QString nombre, QString ruta){
    ArchivoTexto * text = new ArchivoTexto(nombre, ruta);
    text->setContenido(origen->getContenido());
    return text;
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

Folder *FileSystem::getParent(Archivo *arch){
    return getParent(arch, raiz, 1);
}

Folder *FileSystem::getParent(Archivo *arch, Folder *subRaiz, int cont)
{
    for(int i = 0; i<subRaiz->getCantidadArchivos(); i++){
        temp = subRaiz->obtenerArchivo(i);

        if(temp->getTipo() == arch->getTipo() && temp->getNombre() == arch->getNombre() && temp->getRuta() == arch->getRuta())
            return subRaiz;

        else if(subRaiz->getTipo() == "Folder"){
            QStringList split = arch->getRuta().split('/');
            if(split.at(cont) == temp->getNombre())
                return getParent(arch, (Folder*)temp, cont+1);
        }

    }
    if(subRaiz == raiz)
        return NULL;
}
