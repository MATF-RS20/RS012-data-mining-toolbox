#include "MainWindow.hpp"
#include "DataTable.hpp"
#include "LinearRegressionNode.hpp"
#include "DecisionTreeNode.hpp"
#include "SourceNode.hpp"
#include "Stream.hpp"
#include "NormalizationNode.hpp"
#include "StatisticsNode.hpp"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    MainWindow w;
    w.show();*/


    SourceNode sn("SN!");
    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");

    DecisionTreeNode dt("dt");

    Stream s;
    s.add(&sn);
    s.add(&dt);
    s.connect_to(&sn, &dt);
    dt.setTarget("Species");
    s.RunStream(&dt);

    //return a.exec();
    return 0;
}
