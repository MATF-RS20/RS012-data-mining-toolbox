#ifndef KMEANSPARAMETERSDIALOG_HPP
#define KMEANSPARAMETERSDIALOG_HPP

#include <KMeansNode.hpp>
#include <QDialog>
#include <QMessageBox>
#include <QString>

namespace Ui {
class KMeansParametersDialog;
}

class KMeansParametersDialog : public QDialog {
  Q_OBJECT

public:
  explicit KMeansParametersDialog(KMeansNode *cvor, QWidget *parent = nullptr);
  ~KMeansParametersDialog();

private slots:
  void on_Odabir_clicked();

private:
  Ui::KMeansParametersDialog *ui;
  KMeansNode *kmN;
};

#endif // KMEANSPARAMETERSDIALOG_HPP
