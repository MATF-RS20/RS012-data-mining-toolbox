#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <Stream.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:


    void on_AddNodeButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scena; //scena koja se iscrtava
    Stream *TokPodataka;   //glavni tok podataka

};


#endif // MAINWINDOW_H
