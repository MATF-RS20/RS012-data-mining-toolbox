#include "ConnectionLine.hpp"

ConnectionLine::ConnectionLine(QGraphicsItem* cvor1, QGraphicsItem* cvor2)
    : pocetniCvor(cvor1), krajnjiCvor(cvor2)
{

}

QRectF ConnectionLine::boundingRect() const
{
    return QRectF(0, 0, 1, 1);

}

void ConnectionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)

    QPen olovka(Qt::black);
    olovka.setWidth(6);
    painter->setPen(olovka);

    QPointF pocetak(pocetniCvor->x(), pocetniCvor->y());
    QPointF kraj(krajnjiCvor->x(), krajnjiCvor->y());

    painter->drawLine(pocetak,kraj);

};

