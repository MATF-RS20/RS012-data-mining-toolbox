#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include "DataTable.hpp"
#include "Node.hpp"

#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    
    TableWindow(QWidget *parent = nullptr);
    ~TableWindow();
    void view(const Node& node);

private:
    
    Ui::MainWindow *ui;
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;
};

#endif // TABLEWINDOW_H
