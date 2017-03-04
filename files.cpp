#include "files.h"

Files::Files(Archivo * arch, int posX, int posY){
    archivo = arch;
    QString path = "C:\\Users\\Leovavi\\Documents\\UNITEC\\Recursos\\File Explorer\\";
    path += (arch->getTipo() == "Folder" ? "folder.png" : "texto.png");

    image = new QImage(path);
    this->posX = posX;
    this->posY = posY;
}

QRectF Files::boundingRect() const{
    return QRectF(posX, posY, 100, 150);
}

void Files::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();
    painter->drawImage(rect, *image, QRectF(0,0,100,150));
    painter->drawText(QRectF(posX, posY+40, 100, 150), Qt::AlignCenter | Qt::TextWordWrap | Qt::TextDontClip, archivo->getNombre());
}

void Files::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    extern FileSystem * fs;
    Archivo * cargado = NULL;
    cargado = fs->cargarArchivo(archivo->getRuta());
    bool confirm = false;

    if(archivo->getTipo() == "Folder"){
        fs->selected = (Folder*)cargado;
    }else{
        ArchivoTexto * archText = (ArchivoTexto*)cargado;

        QString text = QInputDialog::getText(NULL, archText->getNombre(), QGraphicsScene::tr("Contenido:"),
                                             QLineEdit::Normal, archText->getContenido(), &confirm);

        if(confirm)
            archText->setContenido(text);
    }
}
