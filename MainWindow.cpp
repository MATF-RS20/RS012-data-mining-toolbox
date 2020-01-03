#include "MainWindow.hpp"
#include "ui_MainWindow.h"


//Konstruktor Glavnog Prozora
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      privremeniBrojacCvorova(0)
{
    ui->setupUi(this);
    scena = new QGraphicsScene(this); //scena cvorova
    TokPodataka = new Stream();       //odgovarajuci tok podataka

}


//Destruktor Glavnog Prozora
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_AddNodeButton_clicked()
{


    QString nazivAlgoritma;

    //dohvatanje naziva algoritma iz liste
    if(!izabranaLista.compare("Prepocesiranje")){

        auto selektovani = ui->LISTA_Preprocesiranje->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else if(!izabranaLista.compare("Klasifikacija")){

        auto selektovani = ui->LISTA_Klasifikacija->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else if(!izabranaLista.compare("Klasterovanje")){

        auto selektovani = ui->LISTA_Klasterovanje->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else if(!izabranaLista.compare("LinearnaRegresija")){

        auto selektovani = ui->LISTA_LinReg->selectedItems();
        QListWidgetItem* item = selektovani.first();
        nazivAlgoritma = item->text();

    }else{
        return;
    }


    nacrtajCvor(nazivAlgoritma);

    dodajCvorUTok(nazivAlgoritma);

}

void MainWindow::nacrtajCvor(QString nazivCvora){

    QPen blackPen(Qt::black);
    blackPen.setWidth(2);
    QBrush brush;
    if(!izabranaLista.compare("Prepocesiranje"))
        brush = QBrush(Qt::darkCyan);
    else if(!izabranaLista.compare("Klasifikacija"))
        brush = QBrush(Qt::darkGreen);
    else if(!izabranaLista.compare("Klasterovanje"))
        brush = QBrush(Qt::darkBlue);
    else if(!izabranaLista.compare("LinearnaRegresija"))
        brush = QBrush(Qt::darkRed);
    else
        brush = QBrush(Qt::red);


    QGraphicsEllipseItem *cvor = scena->addEllipse(10,10,50,50,blackPen,brush);
    cvor->setFlag(QGraphicsItem::ItemIsMovable);
    cvor->setFlag(QGraphicsItem::ItemIsSelectable);

    ui->GlavniTok->setScene(scena);
}

void MainWindow::dodajCvorUTok(QString nazivCvora){

    Node *noviCvor;

    if(!nazivCvora.compare("Particionisanje")){

        noviCvor = new PartitionNode(std::to_string(privremeniBrojacCvorova));
        TokPodataka->add(noviCvor);
        privremeniBrojacCvorova++;

    }else if(!nazivCvora.compare("Normalizacija")){

        noviCvor = new NormalizationNode(std::to_string(privremeniBrojacCvorova));
        TokPodataka->add(noviCvor);
        privremeniBrojacCvorova++;

    }else if(!nazivCvora.compare("Statistike")){

        noviCvor = new StatisticsNode(std::to_string(privremeniBrojacCvorova));
        TokPodataka->add(noviCvor);
        privremeniBrojacCvorova++;

    }else if(!nazivCvora.compare("Stablo Odlucivanja")){

        noviCvor = new DecisionTreeNode(std::to_string(privremeniBrojacCvorova));
        TokPodataka->add(noviCvor);
        privremeniBrojacCvorova++;

    }else if(!nazivCvora.compare("K-Sredina")){

        //JOS NIJE IMPLEMENTIRANO
        return;

    }else if(!nazivCvora.compare("DBSCAN")){

        //JOS NIJE IMPLEMENTIRANO
        return;

    }else if(!nazivCvora.compare("Prosta Linearna regresija")){

        noviCvor = new LinearRegressionNode(std::to_string(privremeniBrojacCvorova));
        TokPodataka->add(noviCvor);
        privremeniBrojacCvorova++;

    }else
        return;


}







void MainWindow::on_LISTA_Preprocesiranje_clicked(const QModelIndex &index)
{
    izabranaLista = "Prepocesiranje";

}

void MainWindow::on_LISTA_Klasifikacija_clicked(const QModelIndex &index)
{
    izabranaLista = "Klasifikacija";
}

void MainWindow::on_LISTA_Klasterovanje_clicked(const QModelIndex &index)
{
    izabranaLista = "Klasterovanje";
}

void MainWindow::on_LISTA_LinReg_clicked(const QModelIndex &index)
{
    izabranaLista = "LinearnaRegresija";
}
