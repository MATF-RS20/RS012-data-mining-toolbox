#ifndef PARTITIONPARAMETERSDIALOG_HPP
#define PARTITIONPARAMETERSDIALOG_HPP

#include <QDialog>
#include <PartitionNode.hpp>
#include <QMessageBox>
#include <QString>

namespace Ui {
class PartitionParametersDialog;
}

class PartitionParametersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PartitionParametersDialog( PartitionNode* cvor, QWidget *parent = nullptr);
    ~PartitionParametersDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PartitionParametersDialog *ui;
    PartitionNode* prtCvor;
};

#endif // PARTITIONPARAMETERSDIALOG_HPP
