#include "MainWindow.hpp"
#include "ui_MainWindow.h"


//Konstruktor Glavnog Prozora
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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


    QString cvor;


    if(ui->LISTA_Preprocesiranje->isEnabled()){

        auto selektovani = ui->LISTA_Preprocesiranje->selectedItems();
        QListWidgetItem* item = selektovani.first();
        cvor = item->text();

    }else if(ui->LISTA_Klasifikacija->isEnabled()){

        auto selektovani = ui->LISTA_Klasifikacija->selectedItems();
        QListWidgetItem* item = selektovani.first();
        cvor = item->text();

    }else if(ui->LISTA_Klasterovanje->isEnabled()){

        auto selektovani = ui->LISTA_Klasterovanje->selectedItems();
        QListWidgetItem* item = selektovani.first();
        cvor = item->text();

    }else if(ui->LISTA_LinReg->isEnabled()){

        auto selektovani = ui->LISTA_LinReg->selectedItems();
        QListWidgetItem* item = selektovani.first();
        cvor = item->text();

    }else{
        return;
    }


    scena->addText(cvor);
    ui->GlavniTok->setScene(scena);

}
