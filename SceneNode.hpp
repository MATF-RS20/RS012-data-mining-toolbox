#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDateTime>
#include <QKeyEvent>


class SceneNode : public QGraphicsItem
{
public:

    enum Stanje{
        Neoznacen,
        Oznacen_1,
        Oznacen_2
    };

    SceneNode(QString ID);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


    QString getID();
    Stanje GetNodeState();
    void ClearNodeState();

protected:

    void keyPressEvent(QKeyEvent *event) override;

private:

    QString nodeID;
    Stanje s;
};

#endif // SCENENODE_HPP
