#include "PartitionParametersDialog.hpp"
#include "ui_PartitionParametersDialog.h"

PartitionParametersDialog::PartitionParametersDialog( PartitionNode* cvor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PartitionParametersDialog),
    prtCvor(cvor)
{
    ui->setupUi(this);
}

PartitionParametersDialog::~PartitionParametersDialog()
{
    delete ui;
}

void PartitionParametersDialog::on_pushButton_clicked()
{
    QString unos = ui->Unos->text();
    if(unos.isEmpty()){
        QMessageBox::information(this,"Greska!", "Unesite zeljenu velicinu!");
        return;
    }

    bool ok;
    unos.toDouble(&ok);

    if(ok == false){
        QMessageBox::information(this,"Greska!", "Pogresan Unos! Unestie broj u intervalu [0.0, 1.0]");
        return;
    }


    const double unos_d = unos.toDouble();

    if(unos_d < 0.0 || unos_d > 1.0){
        QMessageBox::information(this,"Greska!", "Pogresan Unos! Broj nije u intervalu [0.0, 1.0]");
        return;
    }


    prtCvor->SetTestSizeRatio(unos_d);

    this->close();
}
