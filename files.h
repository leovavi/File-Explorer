#ifndef FILES_H
#define FILES_H
#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QMainWindow>
#include <QtWidgets>
#include "folder.h"
#include "filesystem.h"

class Files : public QGraphicsItem
{
public:
    Files(Archivo * arch, int posX, int posY);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

    QImage * image;
    Archivo * archivo;
    int posX, posY;
};

#endif // FILES_H
