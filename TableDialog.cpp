#include "TableDialog.hpp"
#include "ui_TableDialog.h"

TableDialog::TableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableDialog)
{
    ui->setupUi(this);
}

TableDialog::~TableDialog()
{
    delete ui;
}

void TableDialog::view(Node* node)
{
    DataTable dataInfo = node->OutputDataTable();
    arma::mat matrix = dataInfo.DataMatrix();
    std::vector<std::string> columnNames = dataInfo.ColumnNames();
     std::map<std::string, std::set<std::string>> mapOfCategories = dataInfo.CategoricalValues();
    unsigned long nRows = dataInfo.DataMatrix().n_rows;
    unsigned long nCols = dataInfo.DataMatrix().n_cols;

    ui->Tabelica->setRowCount(nRows);
    ui->Tabelica->setColumnCount(nCols);

    for(unsigned long j = 0; j < columnNames.size(); j++){
        QString qstr = QString::fromStdString(columnNames[j]);
        TableHeader<<qstr;
    }

    ui->Tabelica->setHorizontalHeaderLabels(TableHeader);
    ui->Tabelica->verticalHeader()->setVisible(false);
    ui->Tabelica->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Tabelica->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Tabelica->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->Tabelica->setShowGrid(false);
    ui->Tabelica->setStyleSheet("QTableView {selection-background-color: red;}");
   // ui->Tabelica->setGeometry(QApplication::desktop()->screenGeometry());

    unsigned long k = 0;
    for(unsigned long j = 0; j < columnNames.size(); j++){
        if (mapOfCategories.find(columnNames[j]) == mapOfCategories.end()){
            for(unsigned long i = 0; i < nRows; i++){
                std::string field = std::to_string(matrix(i, k));
                QString qstr = QString::fromStdString(field);
                ui->Tabelica->setItem(i, j, new QTableWidgetItem(qstr));
            }
            k++;
        } else {
            auto column = node->unbinarize(columnNames[j]);
            for(unsigned long i = 0; i < nRows; i++){
                QString qstr = QString::fromStdString(column[i]);
                ui->Tabelica->setItem(i, j, new QTableWidgetItem(qstr));
            }
            k += mapOfCategories[columnNames[j]].size();
        }
    }

}
