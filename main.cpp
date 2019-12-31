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
    sn.setHasClass(true);
    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
  //  sn.run();

   /* for(auto col : sn.OutputDataTable().ColumnNames())
    {
        std::cout << col << " ";
    }
    std::cout << std::endl;

    for(auto col : sn.OutputDataTable().ClassTargetVariable())
    {
        std::cout << col << " ";
    }
    std::cout << std::endl;*/


    DecisionTreeNode nn("nn");

    Stream s;
    s.add(&sn);
    s.add(&nn);
    s.connect_to(&sn, &nn);
    s.RunStream(&nn);

   // std::cout << sn.OutputDataTable().DataMatrix() << std::endl << std::endl << std::endl << nn.OutputDataTable().DataMatrix() << std::endl;

   // return a.exec();
    return 0;
}
