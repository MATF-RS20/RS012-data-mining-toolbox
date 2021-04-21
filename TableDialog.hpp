#ifndef TABLEDIALOG_HPP
#define TABLEDIALOG_HPP

#include <DataTable.hpp>
#include <MainWindow.hpp>
#include <Node.hpp>
#include <QDesktopWidget>
#include <QDialog>

namespace Ui {
class TableDialog;
}

class TableDialog : public QDialog {
  Q_OBJECT

public:
  explicit TableDialog(QWidget *parent = nullptr);
  ~TableDialog();
  void view(Node *node);

private:
  Ui::TableDialog *ui;
  QStringList TableHeader;
};

#endif // TABLEDIALOG_HPP
