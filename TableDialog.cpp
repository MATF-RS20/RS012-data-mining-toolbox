#include <vector>

#include "TableDialog.hpp"
#include "ui_TableDialog.h"

TableDialog::TableDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TableDialog) {
  ui->setupUi(this);
}

TableDialog::~TableDialog() { delete ui; }

void TableDialog::view(Node *node) {
  DataTable dataInfo = node->OutputDataTable();
  arma::mat matrix = dataInfo.DataMatrix();
  std::vector<std::string> columnNames = dataInfo.ColumnNames();
  std::map<std::string, std::set<std::string>> mapOfCategories =
      dataInfo.CategoricalValues();
  unsigned long nRows = dataInfo.DataMatrix().n_rows;
  bool hasOneMoreColumn = false;
  std::vector<std::string> lastColumn(nRows);
  std::string lastColumnName;

  std::string nodeType = node->NodeName();
  if (nodeType[0] == 'K') {

    if (nodeType[2] == 'S' && nodeType[3] == 'O') {
      hasOneMoreColumn = true;
      lastColumnName = "DT predictions";
      auto dt = dynamic_cast<DecisionTreeNode *>(node);
      arma::Row<size_t> predictions = dt->ClassPredictions();
      std::vector<std::string> vectorOfNames(
          mapOfCategories[dt->TargetColumnName()].size());
      unsigned long vecIndex = 0;
      for (auto c : mapOfCategories[dt->TargetColumnName()]) {
        vectorOfNames[vecIndex] = c;
        vecIndex++;
      }

      for (unsigned long i = 0; i < predictions.size(); i++) {

        lastColumn[i] = vectorOfNames[predictions[i]];
      }
    }

    if (nodeType[2] == 'P') {
      hasOneMoreColumn = true;
      lastColumnName = "Per. predictions";
      auto prcn = dynamic_cast<PerceptronNode *>(node);
      arma::Row<size_t> predictions = prcn->ClassPredictions();
      for (unsigned long i = 0; i < predictions.size(); i++) {
        lastColumn[i] = std::to_string(predictions[i]);
      }
    }

  } else if (nodeType[0] == 'C') {

    if (nodeType[2] == 'K' && nodeType[3] == 'S') {
      hasOneMoreColumn = true;
      lastColumnName = "KMeans labels";
      auto ks = dynamic_cast<KMeansNode *>(node);
      arma::Row<size_t> labels = ks->Labels();
      for (unsigned long i = 0; i < labels.size(); i++) {
        lastColumn[i] = std::to_string(labels[i]);
      }
    }

  } else if (nodeType[0] == 'R') {
    if (nodeType[2] == 'L') {
      hasOneMoreColumn = true;
      lastColumnName = "Reg. predictions";
      auto lrn = dynamic_cast<LinearRegressionNode *>(node);
      arma::Row<double> predictions = lrn->TargetPredictions();
      for (unsigned long i = 0; i < nRows; i++) {
        lastColumn[i] = std::to_string(predictions(i));
      }
    }
  }

  int numOfColumns = static_cast<int>(columnNames.size());
  if (hasOneMoreColumn) {
    if (numOfColumns != 0) {
      numOfColumns++;
    } else {
      hasOneMoreColumn = false;
    }
  }

  ui->Tabelica->setRowCount(static_cast<int>(nRows));
  ui->Tabelica->setColumnCount(numOfColumns);

  for (auto &columnName : columnNames) {
    QString qstr = QString::fromStdString(columnName);
    TableHeader << qstr;
  }
  if (hasOneMoreColumn) {
    QString qstr = QString::fromStdString(lastColumnName);
    TableHeader << qstr;
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
  for (unsigned long j = 0; j < columnNames.size(); j++) {
    if (mapOfCategories.find(columnNames[j]) == mapOfCategories.end()) {
      for (unsigned long i = 0; i < nRows; i++) {
        std::string field = std::to_string(matrix(i, k));
        QString qstr = QString::fromStdString(field);
        ui->Tabelica->setItem(static_cast<int>(i), static_cast<int>(j),
                              new QTableWidgetItem(qstr));
      }
      k++;
    } else {
      auto column = node->unbinarize(columnNames[j]);
      for (unsigned long i = 0; i < nRows; i++) {
        QString qstr = QString::fromStdString(column[i]);
        ui->Tabelica->setItem(static_cast<int>(i), static_cast<int>(j),
                              new QTableWidgetItem(qstr));
      }
      k += mapOfCategories[columnNames[j]].size();
    }
  }
  if (hasOneMoreColumn) {
    for (unsigned long i = 0; i < lastColumn.size(); i++) {
      QString qstr = QString::fromStdString(lastColumn[i]);
      ui->Tabelica->setItem(static_cast<int>(i),
                            static_cast<int>(columnNames.size()),
                            new QTableWidgetItem(qstr));
    }
  }

  QString ispis = QString::fromStdString(node->OutputMessage());
  ui->Ispis->setText(ispis);
}
