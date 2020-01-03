#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

#include <Stream.hpp>
#include <Node.hpp>
#include <NormalizationNode.hpp>
#include <PartitionNode.hpp>
#include <StatisticsNode.hpp>
#include <DecisionTreeNode.hpp>
#include <LinearRegressionNode.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void on_AddNodeButton_clicked();
    void on_LISTA_Preprocesiranje_clicked(const QModelIndex &index);
    void on_LISTA_Klasifikacija_clicked(const QModelIndex &index);
    void on_LISTA_Klasterovanje_clicked(const QModelIndex &index);
    void on_LISTA_LinReg_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scena; //scena koja se iscrtava
    Stream *TokPodataka;   //glavni tok podataka
    QString izabranaLista;
    void nacrtajCvor(QString nazivAlgoritma);
    void dodajCvorUTok(QString nazivAlgoritma);
    int privremeniBrojacCvorova;
};


#endif // MAINWINDOW_H
