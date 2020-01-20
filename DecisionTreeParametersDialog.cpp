#include "DecisionTreeParametersDialog.hpp"
#include "ui_DecisionTreeParametersDialog.h"

DecisionTreeParametersDialog::DecisionTreeParametersDialog(DecisionTreeNode* cvor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecisionTreeParametersDialog),
    dtN(cvor)
{
    ui->setupUi(this);
}

DecisionTreeParametersDialog::~DecisionTreeParametersDialog()
{
    delete ui;
}

void DecisionTreeParametersDialog::on_Odaberi_clicked()
{
    QString odabraniAtribut = ui->Unos->text();
    if(odabraniAtribut.isEmpty()){
        QMessageBox::information(this, "Greska!", "Unesite naziv ciljnog atributa!");
        return;
    }

    dtN->setTarget(odabraniAtribut.toStdString());

    this->close();
}
