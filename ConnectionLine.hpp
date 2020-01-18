#ifndef LINIJA_H
#define LINIJA_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <cmath>
#include <QVector2D>
#include <SceneNode.hpp>

/*Jednostavna Klasa za Iscrtavanje Veza Izmedju Cvorova*/

class ConnectionLine : public QGraphicsItem
{
public:
    ConnectionLine(SceneNode* cvor1, SceneNode* cvor2);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    SceneNode* getPocetniCvor();
    SceneNode* getKrajnjiCvor();


private:
    SceneNode* pocetniCvor;
    SceneNode* krajnjiCvor;
};

#endif // LINIJA_H
