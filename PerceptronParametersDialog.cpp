#include "PerceptronParametersDialog.hpp"
#include "ui_PerceptronParametersDialog.h"

PerceptronParametersDialog::PerceptronParametersDialog(PerceptronNode *cvor,
                                                       QWidget *parent)
    : QDialog(parent), ui(new Ui::PerceptronParametersDialog), prcN(cvor) {
  ui->setupUi(this);
}

PerceptronParametersDialog::~PerceptronParametersDialog() { delete ui; }

void PerceptronParametersDialog::on_Odabir_clicked() {
  QString odabraniAtribut = ui->Unos->text();
  if (odabraniAtribut.isEmpty()) {
    QMessageBox::information(this, "Greska!",
                             "Unesite naziv ciljnog atributa!");
    return;
  }

  prcN->setTarget(odabraniAtribut.toStdString());

  this->close();
}
