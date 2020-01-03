#include "MainWindow.hpp"
#include "DataTable.hpp"
#include "LinearRegressionNode.hpp"
#include "DecisionTreeNode.hpp"
#include "SourceNode.hpp"
#include "Stream.hpp"
#include "StatisticsNode.hpp"
#include "NormalizationNode.hpp"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    SourceNode sn("SN!");

    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.read();

    LinearRegressionNode lr("LR!");    
    DecisionTreeNode dt("DT!");
    StatisticsNode st("ST!");
    NormalizationNode nn("NN!");

    Stream s;
    s.add(&sn);
    s.add(&lr);
    s.add(&dt);
    s.add(&st);
    s.add(&nn);
    s.connect_to(&sn, &nn);
    s.connect_to(&sn, &st);
    s.connect_to(&nn, &dt);
    s.connect_to(&nn, &lr);
    lr.setTarget("Sepal_Length");
    dt.setTarget("Species");
    s.RunStream(&dt);

    return a.exec();
    //return 0;
}
