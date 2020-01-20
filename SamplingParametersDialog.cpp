#include "SamplingParametersDialog.hpp"
#include "ui_SamplingParametersDialog.h"

SamplingParametersDialog::SamplingParametersDialog(SamplingNode* cvor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplingParametersDialog),
    smplN(cvor)
{
    ui->setupUi(this);
}

SamplingParametersDialog::~SamplingParametersDialog()
{
    delete ui;
}

void SamplingParametersDialog::on_Odabir_clicked()
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


    smplN->SetSampleSizeRatio(unos_d);

    this->close();
}
