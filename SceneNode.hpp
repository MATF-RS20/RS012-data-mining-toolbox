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


    //stanje cvora predstavlja oznaku dodeljjenu cvoru pritiskom na tastere 1,2 ili 3
    //koristi se za utvrdjivanje smera grane prilikom vezivanje cvorova i isto tako
    //za brisanje odgovarajuce grane tj veze izmedju cvorva
    //grana ide o cvora Oznacen_1 ka cvoru Oznacen_2
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


    QString getID();        //fja za dohvatanje ID cvora na sceni
    Stanje GetNodeState();  //fja za dohvatanje stanja cvora
    void ClearNodeState();  //fja za ciscene stanja cvora

protected:

    void keyPressEvent(QKeyEvent *event) override; //stanje cvora se menja pritiskom da tastere 1,2 i 3
                                                   //ova fja detktuje pritiske na tastere i postavlja stanje cvora

private:

    QString nodeID;//jedinstveni ID cvora (vidi fju generisiID (MainWindow.cpp))
    Stanje s; //stanje cvora
};

#endif // SCENENODE_HPP
