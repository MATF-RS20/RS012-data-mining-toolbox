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

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
  /*  QApplication a(argc, argv);
    MainWindow w;
    w.show();*/


    SourceNode sn("SN!");

    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.read();
    
    PartitionNode pn("PN!");

    DecisionTreeNode dt("DT!");
    
    Stream s;
 
    s.add(&sn);
    s.add(&pn);
    s.add(&dt);
 
    s.connect_to(&sn, &pn);
    s.connect_to(&pn, &dt);
 
    dt.setTarget("Species");
    s.RunStream(&dt);
    

    //return a.exec();
    return 0;
}
