#include "MainWindow.hpp"
#include "DataTable.hpp"
#include "LinearRegressionNode.hpp"
#include "DecisionTreeNode.hpp"
#include "SourceNode.hpp"
#include "Stream.hpp"
#include "StatisticsNode.hpp"
#include "SamplingNode.hpp"
#include "NormalizationNode.hpp"
#include "PerceptronNode.hpp"
#include "KMeansNode.hpp"
#include "DBSCANNode.hpp"
#include "FilterNode.hpp"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

     
    /*
    SourceNode sn("SN!");

    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.read();
    
    DBSCANNode db("asdf", 0.5, 3);
    */


   /* LinearRegressionNode dt("DT!");
    
    NormalizationNode nn("NN!");
    
    PartitionNode pn("PN!");*/



    /*
    NormalizationNode nn("NN!");

    Stream s;

    s.add(&sn);
    s.add(&db);
    s.add(&nn);

    s.connect_to(&sn, &nn);
    s.connect_to(&nn, &db);

    s.RunStream(&db);

    std::cout << db.SilhouetteScore() << std::endl;

    std::cout << db.Centroids() << std::endl;
    std::cout << db.Labels() << std::endl;
    */


    return a.exec();
    //return 0;
}
