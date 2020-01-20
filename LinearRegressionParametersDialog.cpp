#include "LinearRegressionParametersDialog.hpp"
#include "ui_LinearRegressionParametersDialog.h"

LinearRegressionParametersDialog::LinearRegressionParametersDialog(LinearRegressionNode* cvor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinearRegressionParametersDialog),
    linN(cvor)
{
    ui->setupUi(this);
}

LinearRegressionParametersDialog::~LinearRegressionParametersDialog()
{
    delete ui;
}



void LinearRegressionParametersDialog::on_Odabir_clicked()
{
    QString odabraniAtribut = ui->Unos->text();
    if(odabraniAtribut.isEmpty()){
        QMessageBox::information(this, "Greska!", "Unesite naziv ciljnog atributa!");
        return;
    }


    linN->setTarget(odabraniAtribut.toStdString());

    this->close();
}
