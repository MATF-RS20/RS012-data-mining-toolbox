#include "SceneNode.hpp"

SceneNode::SceneNode(QString ID)
    : nodeID(ID)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
}

QString SceneNode::getID()
{
    return nodeID;
}

SceneNode::Stanje SceneNode::GetNodeState()
{
    return s;
}

void SceneNode::ClearNodeState()
{
    s = Neoznacen;
}



QRectF SceneNode::boundingRect() const
{
    return QRectF(10,10,50,50);
}

void SceneNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)


    QPen olovka(Qt::black);
    olovka.setWidth(2);

    if(isSelected()){

        QPen olovkaObod;
        olovkaObod.setStyle(Qt::DashLine);
        olovkaObod.setWidth(2);

        painter->setPen(olovkaObod);
        QRectF obod = boundingRect();
        painter->drawRect(obod);

        olovka.setColor(Qt::yellow);
    }


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



    QCharRef s1 = nodeID[2];
    QCharRef s2 = nodeID[3];

    olovka.setWidth(10);
    painter->setPen(olovka);

    if(s2 == '_'){

        QString nazivAlg;
        nazivAlg.resize(1);
        nazivAlg[0] = s1;
        painter->drawText(40,25,nazivAlg);

    }else{

        QString nazivAlg;
        nazivAlg.resize(2);
        nazivAlg[0] = s1;
        nazivAlg[1] = s2;
        painter->drawText(31,25,nazivAlg);

    }


    olovka.setColor(Qt::black);
    painter->setPen(olovka);

    if(s == Oznacen_1)
        painter->drawText(10,10, "1");
    if(s == Oznacen_2)
        painter->drawText(10,10, "2");
}


void SceneNode::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_1){
        s = Oznacen_1;
        update();
    }

    if(event->key() == Qt::Key_2){
        s = Oznacen_2;
        update();
    }

    if(event->key() == Qt::Key_3){
        s = Neoznacen;
        update();
    }
}





