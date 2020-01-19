#ifndef DECISIONTREEPARAMETERSDIALOG_HPP
#define DECISIONTREEPARAMETERSDIALOG_HPP

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <DecisionTreeNode.hpp>

namespace Ui {
class DecisionTreeParametersDialog;
}

class DecisionTreeParametersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DecisionTreeParametersDialog(DecisionTreeNode* cvor, QWidget *parent = nullptr);
    ~DecisionTreeParametersDialog();

private slots:
    void on_Odaberi_clicked();

private:
    Ui::DecisionTreeParametersDialog *ui;
    DecisionTreeNode* dtN;
};

#endif // DECISIONTREEPARAMETERSDIALOG_HPP
