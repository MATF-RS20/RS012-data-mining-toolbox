#include "MainWindow.hpp"
#include "ui_MainWindow.h"



//konstruktor glavnog prozora
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //vezivanje dugmica sa dogadjajima i rekcijama
    connect(ui->RunStreamButton, SIGNAL(clicked()), this, SLOT(buttonRunStreamClicked()));
    connect(ui->AddNodeButton,   SIGNAL(clicked()), this, SLOT(buttonAddNodeClicked()));
}


//destruktor glavnog prozora
MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::buttonRunStreamClicked()
{
    //TODO
}

void MainWindow::buttonAddNodeClicked()
{
    //TODO
}
