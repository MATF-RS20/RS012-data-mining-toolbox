#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <ConnectionLine.hpp>
#include <SceneNode.hpp>

#include <iostream>
#include <Stream.hpp>
#include <Node.hpp>
#include <NormalizationNode.hpp>
#include <PartitionNode.hpp>
#include <StatisticsNode.hpp>
#include <DecisionTreeNode.hpp>
#include <LinearRegressionNode.hpp>
#include <SamplingNode.hpp>
#include <PerceptronNode.hpp>
#include <SourceNode.hpp>
#include <FilterNode.hpp>
#include <KMeansNode.hpp>

#include <TableDialog.hpp>
#include <SourceParametersDialog.hpp>
#include <PartitionParametersDialog.hpp>
#include <SamplingParametersDialog.hpp>
#include <FilterParametersDialog.hpp>
#include <KMeansParametersDialog.hpp>
#include <DecisionTreeParametersDialog.hpp>
#include <PerceptronParametersDialog.hpp>
#include <LinearRegressionParametersDialog.hpp>


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
    void on_LISTA_Preprocesiranje_clicked(const QModelIndex &index);
    void on_LISTA_Klasifikacija_clicked(const QModelIndex &index);
    void on_LISTA_Klasterovanje_clicked(const QModelIndex &index);
    void on_LISTA_LinReg_clicked(const QModelIndex &index);
    void on_LISTA_Ulaz_clicked(const QModelIndex &index);

    void on_AddNodeButton_clicked();
    void on_RunStreamButton_clicked();
    void on_ConnectButton_clicked();




    void on_DisconnectButton_clicked();

    void on_ClearScene_clicked();

    void on_DataViewButton_clicked();


    void on_SetParameters_clicked();

private:
    void nacrtajCvor(QString nodeID);
    void dodajCvorUTok(QString nodeID);
    QString generisiID(QString nazivAlgoritma);
    Node* pronadjiCvor(QString ID);

    void podesiParametre_Ulazni(Node* cvor);
    void podesiParametre_Uzorkovanje(Node* cvor);
    void podesiParametre_Particionisanje(Node* cvor);
    void podesiParametre_Filter(Node* cvor);
    void podesiParametre_KSredina(Node* cvor);
    void podesiParametre_StabloOdlucivanja(Node* cvor);
    void podesiParametre_Perceptron(Node* cvor);
    void podesiParametre_LinearnaRegresija(Node* cvor);

    Ui::MainWindow *ui;
    QGraphicsScene *scena; //scena koja se iscrtava
    Stream *TokPodataka;   //glavni tok podataka
    QString izabranaLista; //odabrana lista algoritama

    int broj_cvorova;
};


#endif // MAINWINDOW_H
