#ifndef PERCEPTRONPARAMETERSDIALOG_HPP
#define PERCEPTRONPARAMETERSDIALOG_HPP

#include <PerceptronNode.hpp>
#include <QDialog>
#include <QMessageBox>
#include <QString>

namespace Ui {
class PerceptronParametersDialog;
}

class PerceptronParametersDialog : public QDialog {
  Q_OBJECT

public:
  explicit PerceptronParametersDialog(PerceptronNode *cvor,
                                      QWidget *parent = nullptr);
  ~PerceptronParametersDialog();

private slots:
  void on_Odabir_clicked();

private:
  Ui::PerceptronParametersDialog *ui;
  PerceptronNode *prcN;
};

#endif // PERCEPTRONPARAMETERSDIALOG_HPP
