#ifndef FILES_H
#define FILES_H
#include <QGraphicsItem>
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QMainWindow>
#include <QtWidgets>
#include "folder.h"

class Files : public QGraphicsItem
{
public:
    Files(Archivo * arch, int posX, int posY, bool painted);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateFile(bool);

    QImage * image;
    QRectF rect;
    Archivo * archivo;
    int posX, posY;
    bool painted;
};

#endif // FILES_H
