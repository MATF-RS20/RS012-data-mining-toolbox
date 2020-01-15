#include "SceneNode.hpp"

SceneNode::SceneNode(QString ID)
    :pressed(false), selected(false), nodeID(ID)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
}

QRectF SceneNode::boundingRect() const
{
    return QRectF(10,10,50,50);
}

void SceneNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)


    if(isSelected()){

        QPen olovkaObod;
        olovkaObod.setStyle(Qt::DashLine);
        olovkaObod.setWidth(2);

        painter->setPen(olovkaObod);
        QRectF obod = boundingRect();
        painter->drawRect(obod);
    }



    QPen olovka(Qt::black);
    olovka.setWidth(2);

    QBrush cetkica(Qt::cyan);

    if(nodeID[0] == 'P')
        cetkica.setColor(Qt::darkCyan);
    else if(nodeID[0] == 'K')
        cetkica.setColor(Qt::darkGreen);
    else if(nodeID[0] == 'C')
        cetkica.setColor(Qt::darkBlue);
    else if(nodeID[0] == 'R')
        cetkica.setColor(Qt::darkRed);
    else if(nodeID[0] == 'U')
        cetkica.setColor(Qt::magenta);


    painter->setPen(olovka);
    painter->setBrush(cetkica);

    painter->drawEllipse(10,10,50,50);


}

void SceneNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    setSelected(true);
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void SceneNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}


QString SceneNode::getID()
{
    return nodeID;
}
