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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    SourceNode sn("SN!");
    //sn.setHasClass(true);
    sn.setFilename("../RS012-data-mining-toolbox/dogs.csv");
    sn.run();
    sn.filterBinarisedCol("breed");

    LinearRegressionNode lr("LR!");


    //DecisionTreeNode nn("nn");

    Stream s;
    s.add(&sn);
<<<<<<< HEAD
    s.add(&lr);
    s.connect_to(&sn, &lr);
    lr.run();
    //s.RunStream(&lr);

    std::cout << sn.OutputDataTable().DataMatrix() << std::endl << std::endl << std::endl << lr.OutputDataTable().DataMatrix() << std::endl;
=======
    s.add(&nn);
    s.connect_to(&sn, &nn);
    s.RunStream(&nn);*/

   // std::cout << sn.OutputDataTable().DataMatrix() << std::endl << std::endl << std::endl << nn.OutputDataTable().DataMatrix() << std::endl;
    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");

    /*
    StatisticsNode st("st");

    Stream s;
    s.add(&sn);
    s.add(&st);
    s.connect_to(&sn, &st);
    s.RunStream(&st);
>>>>>>> 59bddef1d2a1a5cc45864427b292f307edb84d78



   */

    return a.exec();
    //return 0;
}
