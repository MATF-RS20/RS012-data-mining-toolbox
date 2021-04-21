#include "FilterParametersDialog.hpp"
#include "ui_FilterParametersDialog.h"

FilterParametersDialog::FilterParametersDialog(FilterNode *cvor,
                                               QWidget *parent)
    : QDialog(parent), ui(new Ui::FilterParametersDialog), filN(cvor) {
  ui->setupUi(this);
}

FilterParametersDialog::~FilterParametersDialog() { delete ui; }

void FilterParametersDialog::on_OdabirKolone_clicked() {
  QString imeKolone = ui->Unos->text();
  ui->ListaKolona->addItem(imeKolone);
  ui->Unos->clear();
}

void FilterParametersDialog::on_IzbacivanjeKolone_clicked() {
  auto selektovani = ui->ListaKolona->selectedItems();
  if (selektovani.empty()) {
    QMessageBox::information(
        this, "Graska!", "Obaderite kolonu za izbacivanje iz prikazane liste");
    return;
  }

  for (auto l : selektovani) {
    ui->ListaKolona->takeItem(ui->ListaKolona->row(l));
  }
}

void FilterParametersDialog::on_Potvrda_clicked() {
  std::set<std::string> skupKolona;

  QListWidgetItem *kolona;

  while ((kolona = ui->ListaKolona->takeItem(0)) != nullptr) {

    QString nazivKolone = kolona->text();
    skupKolona.insert(nazivKolone.toStdString());
  }

  filN->SetColumnNames(skupKolona);
  this->close();
}
