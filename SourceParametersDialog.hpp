#ifndef SOURCEPARAMETERSDIALOG_HPP
#define SOURCEPARAMETERSDIALOG_HPP

#include <Node.hpp>
#include <QDialog>
#include <QFileDialog>
#include <QString>
#include <SourceNode.hpp>

namespace Ui {
class SourceParametersDialog;
}

class SourceParametersDialog : public QDialog {
  Q_OBJECT

public:
  explicit SourceParametersDialog(SourceNode *cvor, QWidget *parent = nullptr);
  ~SourceParametersDialog();

private slots:
  void on_Potvrdi_clicked();
  void on_OdaberiFajl_clicked();

private:
  Ui::SourceParametersDialog *ui;
  SourceNode *UlazniCvor;
};

#endif // SOURCEPARAMETERSDIALOG_HPP
