#ifndef DECISIONTREEPARAMETERSDIALOG_HPP
#define DECISIONTREEPARAMETERSDIALOG_HPP

#include <DecisionTreeNode.hpp>
#include <QDialog>
#include <QMessageBox>
#include <QString>

namespace Ui {
class DecisionTreeParametersDialog;
}

class DecisionTreeParametersDialog : public QDialog {
  Q_OBJECT

public:
  explicit DecisionTreeParametersDialog(DecisionTreeNode *cvor,
                                        QWidget *parent = nullptr);
  ~DecisionTreeParametersDialog();

private slots:
  void on_Odaberi_clicked();

private:
  Ui::DecisionTreeParametersDialog *ui;
  DecisionTreeNode *dtN;
};

#endif // DECISIONTREEPARAMETERSDIALOG_HPP
