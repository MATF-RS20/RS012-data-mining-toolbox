#ifndef TABLEDIALOG_HPP
#define TABLEDIALOG_HPP

#include <QDialog>
#include <QDesktopWidget>
#include <MainWindow.hpp>
#include <DataTable.hpp>
#include <Node.hpp>

namespace Ui {
class TableDialog;
}

class TableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableDialog(QWidget *parent = nullptr);
    ~TableDialog();
    void view(Node* node);

private:
    Ui::TableDialog *ui;
    QStringList TableHeader;
};

#endif // TABLEDIALOG_HPP
