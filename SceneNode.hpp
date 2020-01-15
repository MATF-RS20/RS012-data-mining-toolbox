#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

class SceneNode : public QGraphicsItem
{
public:
    SceneNode(QString ID);

    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    bool pressed;
    bool selected;

    QString getID();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


private:

    QString nodeID;


};

#endif // SCENENODE_HPP
