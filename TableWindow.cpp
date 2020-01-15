#include "TableWindow.hpp"
#include "ui_MainWindow.h"
#include "DataTable.hpp"
#include "Node.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>

TableWindow::TableWindow(QWidget *parent)
 : QMainWindow(parent),
 m_pTableWidget(NULL)
{}

TableWindow::~TableWindow()
{
   
}

void TableWindow::view(const Node& node){
    DataTable dataInfo = node.OutputDataTable();
    arma::mat matrix = dataInfo.DataMatrix();
    std::vector<std::string> columnNames = dataInfo.ColumnNames();
     std::map<std::string, std::set<std::string>> mapOfCategories = dataInfo.CategoricalValues();
    unsigned long nRows = dataInfo.DataMatrix().n_rows;
    unsigned long nCols = dataInfo.DataMatrix().n_cols;
    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setRowCount(nRows);
    m_pTableWidget->setColumnCount(columnNames.size());

    for(unsigned long j = 0; j < columnNames.size(); j++){
        QString qstr = QString::fromStdString(columnNames[j]);
        m_TableHeader<<qstr;
    }
    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableWidget->setShowGrid(false);
    m_pTableWidget->setStyleSheet("QTableView {selection-background-color: red;}");
    m_pTableWidget->setGeometry(QApplication::desktop()->screenGeometry());

    unsigned long k = 0;
    for(unsigned long j = 0; j < columnNames.size(); j++){
        if (mapOfCategories.find(columnNames[j]) == mapOfCategories.end()){
            for(unsigned long i = 0; i < nRows; i++){
                std::string field = std::to_string(matrix(i, k));
                QString qstr = QString::fromStdString(field);
                m_pTableWidget->setItem(i, j, new QTableWidgetItem(qstr));
            }
            k++;
        } else {
            auto column = node.unbinarize(columnNames[j]);
            for(unsigned long i = 0; i < nRows; i++){
                QString qstr = QString::fromStdString(column[i]);
                m_pTableWidget->setItem(i, j, new QTableWidgetItem(qstr));
            }
            k += mapOfCategories[columnNames[j]].size();
        }
    }
}
