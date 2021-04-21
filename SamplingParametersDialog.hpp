#ifndef SAMPLINGPARAMETERSDIALOG_HPP
#define SAMPLINGPARAMETERSDIALOG_HPP

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <SamplingNode.hpp>

namespace Ui {
class SamplingParametersDialog;
}

class SamplingParametersDialog : public QDialog {
  Q_OBJECT

public:
  explicit SamplingParametersDialog(SamplingNode *cvor,
                                    QWidget *parent = nullptr);
  ~SamplingParametersDialog();

private slots:
  void on_Odabir_clicked();

private:
  Ui::SamplingParametersDialog *ui;
  SamplingNode *smplN;
};

#endif // SAMPLINGPARAMETERSDIALOG_HPP
