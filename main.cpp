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
    
   
    DecisionTreeNode dt("DT!");
    
    NormalizationNode nn("NN!");

    Stream s;

    s.add(&sn);
    s.add(&nn);
    s.add(&dt);
   
    s.connect_to(&sn, &nn);
    s.connect_to(&nn, &dt);
  
    dt.setTarget("Species");

    s.RunStream(&dt);
    
    */

    return a.exec();
    //return 0;
}
