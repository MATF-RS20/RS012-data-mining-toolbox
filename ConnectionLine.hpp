#ifndef LINIJA_H
#define LINIJA_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QVector2D>
#include <SceneNode.hpp>
#include <cmath>

/*Jednostavna Klasa za Iscrtavanje Veza Izmedju Cvorova*/

class ConnectionLine : public QGraphicsItem {
public:
  ConnectionLine(SceneNode *cvor1, SceneNode *cvor2);

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  SceneNode *getPocetniCvor(); // fja vraca pocetni cvor
  SceneNode *getKrajnjiCvor(); // fja vraca krajnji cvor

private:
  // pamtimo pocetni i krajnji cvor veze
  SceneNode *pocetniCvor;
  SceneNode *krajnjiCvor;
};

#endif // LINIJA_H
