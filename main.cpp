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
  /*  QApplication a(argc, argv);
    MainWindow w;
    w.show();*/


    SourceNode sn("SN!");
    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.run();

    arma::mat matrix = sn.filterBinarisedCol("Species");
    for(unsigned i = 0; i < matrix.n_rows; i++) {
        for(unsigned j = 0; j< matrix.n_cols; j++) {
            std::cout << matrix(i,j) << " ";
        }
        std::cout << std::endl;
    }

    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");

    StatisticsNode st("st");

    Stream s;
    s.add(&sn);
    s.add(&st);
    s.connect_to(&sn, &st);
    s.RunStream(&st);

   // return a.exec();
    return 0;
}
