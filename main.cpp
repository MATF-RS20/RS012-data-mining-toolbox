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

    SourceNode sn("SN!");
    sn.setHasClass(true);
    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.run();

    for(auto col : sn.OutputDataTable().ColumnNames())
    {
        std::cout << col << " ";
    }
    std::cout << std::endl;
}
