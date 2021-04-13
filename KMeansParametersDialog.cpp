#include "KMeansParametersDialog.hpp"
#include "ui_KMeansParametersDialog.h"

KMeansParametersDialog::KMeansParametersDialog(KMeansNode *cvor,
                                               QWidget *parent)
    : QDialog(parent), ui(new Ui::KMeansParametersDialog), kmN(cvor) {
  ui->setupUi(this);
}

KMeansParametersDialog::~KMeansParametersDialog() { delete ui; }

void KMeansParametersDialog::on_Odabir_clicked() {
  if (ui->UnosIteracija->text().isEmpty() ||
      ui->UnosBrKlastera->text().isEmpty() ||
      ui->Rastojanja->selectedItems().isEmpty()) {
    QMessageBox::information(
        this, "Greska!", "Popunite sva polja i odaberite zeljeno rastojanje!");
    return;
  }

  bool ok;
  int brIter = ui->UnosIteracija->text().toInt(&ok);
  if (ok == false) {
    QMessageBox::information(
        this, "Greska!", "Unesite odgovarajucu vrednost za broj iteracija!");
    return;
  }
  if (brIter < 0) {
    QMessageBox::information(this, "Greska!",
                             "Broj iteracija ne moze biti negativan!");
    return;
  }

  size_t brIter_t = brIter;

  int brKlastera = ui->UnosBrKlastera->text().toInt(&ok);
  if (ok == false) {
    QMessageBox::information(
        this, "Greska!",
        "Unesite odgovarajucu vrednost za broj klastera (>= 2)!");
    return;
  }
  if (brKlastera < 2) {
    QMessageBox::information(this, "Greska!", "Unesite broj klastera >= 2 !");
    return;
  }

  size_t brKlastera_t = brKlastera;

  kmN->SetNumberOfClusters(brKlastera_t);
  kmN->SetMaxNumberOfIterations(brIter_t);

  auto odabranoRastojanje = ui->Rastojanja->selectedItems();
  if (odabranoRastojanje[0]->text() == "Euklidsko Rastojanje") {

    kmN->SetDistance(KMeansNode::distances::EuclideanDistance);

  } else if (odabranoRastojanje[0]->text() ==
             "Kvadratno Euklidsko Rastojanje") {

    kmN->SetDistance(KMeansNode::distances::SquaredEuclideanDistance);

  } else if (odabranoRastojanje[0]->text() == "Menhetn Rastojanje") {

    kmN->SetDistance(KMeansNode::distances::ManhattanDistance);

  } else if (odabranoRastojanje[0]->text() == "Cebisevljevo Rastojanje") {

    kmN->SetDistance(KMeansNode::distances::ChebyshevDistance);

  } else {
    QMessageBox::information(this, "Greska!", "Doslo je do nepoznate greske!");
    return;
  }

  this->close();
}
