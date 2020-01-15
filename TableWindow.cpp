#include "TableWindow.hpp"
#include "ui_MainWindow.h"
#include "DataTable.hpp"

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

void TableWindow::view(const DataTable& data){
    DataTable dataInfo = data;
    arma::mat matrix = dataInfo.DataMatrix();
    unsigned long nRows = dataInfo.DataMatrix().n_rows;
    unsigned long nCols = dataInfo.DataMatrix().n_cols;
    m_pTableWidget = new QTableWidget(this);
    m_pTableWidget->setRowCount(nRows);
    m_pTableWidget->setColumnCount(nCols);

    std::vector<std::string> columnNames = dataInfo.ColumnNames();
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

    
    for(unsigned long i = 0; i < nRows; i++){
        for(unsigned long j = 0; j < nCols; j++){
            std::string field = std::to_string(matrix(i, j));
            QString qstr = QString::fromStdString(field);
            m_pTableWidget->setItem(i, j, new QTableWidgetItem(qstr));
        }
    }
}
