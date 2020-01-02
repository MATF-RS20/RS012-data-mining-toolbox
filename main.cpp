#include "MainWindow.hpp"
#include "DataTable.hpp"
#include "LinearRegressionNode.hpp"
#include "DecisionTreeNode.hpp"
#include "SourceNode.hpp"
#include "Stream.hpp"
#include "NormalizationNode.hpp"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
  /*  QApplication a(argc, argv);
    MainWindow w;
    w.show();*/


    SourceNode sn("SN!");
    //sn.setHasClass(true);
    sn.setFilename("../RS012-data-mining-toolbox/dogs.csv");
    sn.run();
    sn.filterBinarisedCol("breed");

    LinearRegressionNode lr("LR!");


    //DecisionTreeNode nn("nn");

    Stream s;
    s.add(&sn);
    s.add(&lr);
    s.connect_to(&sn, &lr);
    lr.run();
    //s.RunStream(&lr);

    std::cout << sn.OutputDataTable().DataMatrix() << std::endl << std::endl << std::endl << lr.OutputDataTable().DataMatrix() << std::endl;

   // return a.exec();
    return 0;
}
