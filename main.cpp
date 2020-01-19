#include "MainWindow.hpp"
#include "TableWindow.hpp"
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

    //QApplication a(argc, argv);

    //MainWindow w;
    //TableWindow w1;

    //w.show();
     
    
    SourceNode sn("SN!");

    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.read();
    
   
    LinearRegressionNode dt("DT!");
    
    NormalizationNode nn("NN!");
    
    PartitionNode pn("PN!");

    Stream s;

    s.add(&sn);
    s.add(&nn);
    s.add(&pn);
    s.add(&dt);
   
    s.connect_to(&sn, &nn);
    s.connect_to(&nn, &pn);
    s.connect_to(&pn, &dt);
  
    dt.setTarget("Sepal_Length");

    s.RunStream(&dt);
    
    
    
    //w1.view(dt);
    //w1.show();
    

    //return a.exec();
    return 0;
}
