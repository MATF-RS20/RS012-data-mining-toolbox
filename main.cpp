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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    SourceNode sn("SN!");
<<<<<<< HEAD
    //sn.setHasClass(true);
    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.run();

    arma::mat matrix = sn.filterBinarisedCol("Species");
    for(unsigned i = 0; i < matrix.n_rows; i++) {
        for(unsigned j = 0; j< matrix.n_cols; j++) {
            std::cout << matrix(i,j) << " ";
        }
        std::cout << std::endl;
    }

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


    /*DecisionTreeNode nn("nn");

    Stream s;
    s.add(&sn);
    s.add(&nn);
    s.connect_to(&sn, &nn);
    s.RunStream(&nn);*/

   // std::cout << sn.OutputDataTable().DataMatrix() << std::endl << std::endl << std::endl << nn.OutputDataTable().DataMatrix() << std::endl;
=======
    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");

    /*
    StatisticsNode st("st");

    Stream s;
    s.add(&sn);
    s.add(&st);
    s.connect_to(&sn, &st);
    s.RunStream(&st);
>>>>>>> f57bfa3c82f7ee28866da04c91b69dac3eac0446


   */

    return a.exec();
    //return 0;
}
