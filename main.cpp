//#include "mainwindow.hpp"
#include "DataTable.hpp"
#include "LinearRegressionNode.hpp"
#include "SourceNode.hpp"
#include "Stream.hpp"

#include <iostream>

//#include <QApplication>

int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    Stream s;

    SourceNode sn("SN!");
    s.add(&sn);
    LinearRegressionNode lr("LR!");
    s.add(&lr);
    s.connect_to(&sn, &lr);

    sn.setFilename("../RS012-data-mining-toolbox/zoo.csv");

    s.RunStream(&lr);
}
