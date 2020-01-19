#include "SourceParametersDialog.hpp"
#include "ui_SourceParametersDialog.h"

SourceParametersDialog::SourceParametersDialog(SourceNode* cvor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceParametersDialog),
    UlazniCvor(cvor)
{
    ui->setupUi(this);
}

SourceParametersDialog::~SourceParametersDialog()
{
    delete ui;
}

void SourceParametersDialog::on_OdaberiCvor_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Odaberite CSV Fajl"),
                "/home",
                "CSV Files (*.csv)"
                );

    ui->NazivFajla->setText(fileName);
}

void SourceParametersDialog::on_Potvrdi_clicked()
{
    QString nazivFjla = ui->NazivFajla->toPlainText();
    UlazniCvor->setFilename(nazivFjla.toStdString());
    UlazniCvor->read();
    this->close();
}
