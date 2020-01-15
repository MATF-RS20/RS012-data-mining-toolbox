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

    /*QApplication a(argc, argv);
    MainWindow w;
    TableWindow w1;

    w.show();*/

    SourceNode sn("SN!");

    sn.setFilename("../RS012-data-mining-toolbox/zoo.csv");
    sn.read();
    
    //PartitionNode pn("PN!");

    LinearRegressionNode lr("LR");
    /*DecisionTreeNode dt("DT!");

    KMeansNode kn("KM");
    kn.SetDistance(KMeansNode::distances::SquaredEuclideanDistance);
    kn.SetMaxNumberOfIterations(1000);
    kn.SetNumberOfClusters(2);

    DBSCANNode dn("DN!");
    dn.SetEpsilon(0.5);
    dn.SetMinPoints(3);*/

    FilterNode fn("FN!");
    fn.SetColumnNames(std::set<std::string>({"IME", "KLASA"}));

    DecisionTreeNode dt("DT!");
    Stream s;

    s.add(&sn);

    s.add(&fn);
    /*s.add(&pn);

    s.add(&dt);*/
    s.add(&lr);
    /*s.add(&dn);
    s.add(&kn);*/

    s.connect_to(&sn, &fn);
    s.connect_to(&fn, &lr);
    /*s.connect_to(&fn, &pn);

    s.connect_to(&fn, &dn);
    s.connect_to(&fn, &kn);

    s.connect_to(&pn, &lr);
    s.connect_to(&pn, &dt);*/
 
    lr.setTarget("DOMACA");
    //dt.setTarget("KLASA");

    s.RunStream(&lr);


    //return a.exec();
    return 0;
}
