#ifndef FILTERPARAMETERSDIALOG_HPP
#define FILTERPARAMETERSDIALOG_HPP

#include <FilterNode.hpp>
#include <QDialog>
#include <QMessageBox>
#include <QString>

namespace Ui {
class FilterParametersDialog;
}

class FilterParametersDialog : public QDialog {
  Q_OBJECT

public:
  explicit FilterParametersDialog(FilterNode *cvor, QWidget *parent = nullptr);
  ~FilterParametersDialog();

private slots:
  void on_OdabirKolone_clicked();

  void on_IzbacivanjeKolone_clicked();

  void on_Potvrda_clicked();

private:
  Ui::FilterParametersDialog *ui;
  FilterNode *filN;
};

#endif // FILTERPARAMETERSDIALOG_HPP
