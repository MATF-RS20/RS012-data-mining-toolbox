#ifndef LINIJA_H
#define LINIJA_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

/*Jednostavna Klasa za Iscrtavanje Veza Izmedju Cvorova*/

class ConnectionLine : public QGraphicsItem
{
public:
    ConnectionLine(QGraphicsItem* cvor1, QGraphicsItem* cvor2);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    QGraphicsItem* pocetniCvor;
    QGraphicsItem* krajnjiCvor;
};

#endif // LINIJA_H
