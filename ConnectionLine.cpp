#include "ConnectionLine.hpp"

ConnectionLine::ConnectionLine(SceneNode *cvor1, SceneNode *cvor2)
    : pocetniCvor(cvor1), krajnjiCvor(cvor2) {}

SceneNode *ConnectionLine::getPocetniCvor() { return pocetniCvor; }

SceneNode *ConnectionLine::getKrajnjiCvor() { return krajnjiCvor; };

QRectF ConnectionLine::boundingRect() const { return {0, 0, 1, 1}; }

void ConnectionLine::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget) {
  Q_UNUSED(option)

  // fja iscrtava liniju od pocetnog ka krajnjem cvoru

  QPen olovka(Qt::black);

  if (isSelected())
    olovka.setColor(Qt::yellow);

  olovka.setWidth(6);
  painter->setPen(olovka);

  QPointF pocetak(pocetniCvor->x() + 35, pocetniCvor->y() + 35);
  QPointF kraj(krajnjiCvor->x() + 35, krajnjiCvor->y() + 35);

  painter->drawLine(pocetak, kraj);

  painter->drawEllipse(kraj, 5, 5);
  painter->drawEllipse(pocetak, 5, 5);
}
