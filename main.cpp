//#include "mainwindow.hpp"
#include "DataTable.hpp"
#include "LinearRegressionNode.hpp"
#include "SourceNode.hpp"
#include "Stream.hpp"

#include <iostream>

//#include <QApplication>

int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/


/***********************PROVERA DODAVANJA, VEZIVANJA I POKRETANJA CVOROVA U KLASI STREAM***************************/
    Stream s;

    SourceNode sn("SN!");
    s.add(&sn);
    LinearRegressionNode lr("LR!");
    s.add(&lr);
    s.connect_to(&sn, &lr);
    //Dodavanje u cvorova u Stream i medjusobno vezivanje cvorova u Stream-u radi

    sn.setFilename("../RS012-data-mining-toolbox/zoo.csv");

    s.RunStream(&lr);
    //Pokretanje Stream-a od zeljenog cvora pa nazad radi
/***************************************PROVERA PROSLA*************************************************************/



/***************************************PROVERA KOPIRANJA KLASE STREAM*********************************************/
    Stream s1(s);
    //Stream s2 = s;

    //Poenta je naci bilo koji ne-sourceNode i pokrenuti kopiju Stream-a od njega, a sourceNode promeniti u neki drugi csv radi provere kopije.
    auto map = s1.MapOfNodes();
    //Node* testNode;
    SourceNode* test;
    for(auto m : map)
    {
        test = dynamic_cast<SourceNode*>(m.first);
        if(!test)
        {
            continue;
        }
        test->setFilename("/home/aleksandra/Documents/faks/7.semestar/RS/projekat1/RS012-data-mining-toolbox/dogs.csv");
        test->run();
        break;
        /*if(!test)
        {
            testNode = m.first;
            break;
        }
        else
        {
            test->setFilename("/home/aleksandra/Documents/faks/7.semestar/RS/projekat1/RS012-data-mining-toolbox/dogs.csv");
            test->run();
        }*/
    }

    //Posmatra se da li je promena source cvora u kopiji izazvala promenu source cvora u originalu. Posmatraju se imena kolona zato.
    std::vector<std::string> colName = (sn.OutputDataTable()).ColumnNames();
    for(auto iter = colName.begin(); iter != colName.end(); iter++){
        std::cout << iter.operator*() << std::endl;
    }
    std::cout << std::endl;

    colName = test->OutputDataTable().ColumnNames();
    for(auto iter = colName.begin(); iter != colName.end(); iter++){
        std::cout << iter.operator*() << std::endl;
    }
    std::cout << std::endl;

    //s1.RunStream(testNode);
    //s2.RunStream(&lr);
    //Pokrecu se kopije strima. Nisu se dobili ocekivani rezultati.
    /***************************************PROVERA NIJE PROSLA!!!*************************************************************/
}
