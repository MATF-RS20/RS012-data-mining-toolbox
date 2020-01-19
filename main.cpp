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

     
    
    SourceNode sn("SN!");

    sn.setFilename("../RS012-data-mining-toolbox/iris.csv");
    sn.read();
    
   
   /* LinearRegressionNode dt("DT!");
    
    NormalizationNode nn("NN!");
    
    PartitionNode pn("PN!");*/

    /*
    StatisticsNode st("ST!");

    Stream s;

    s.add(&sn);
    s.add(&st);
    s.connect_to(&sn, &st);

    s.add(&nn);
    s.add(&pn);
    s.add(&dt);
   
    s.connect_to(&sn, &nn);
    s.connect_to(&nn, &pn);
    s.connect_to(&pn, &dt);
  
    dt.setTarget("Sepal_Length");

    s.RunStream(&st);
    std::cout << st.GetStatistics() << std::endl;
    */
    

    return a.exec();
    //return 0;
}
