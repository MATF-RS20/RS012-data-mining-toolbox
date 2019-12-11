//#include "mainwindow.hpp"
#include "DataTable.hpp"
<<<<<<< HEAD
#include "LinearRegressionNode.hpp"
=======
#include "SourceNode.hpp"
>>>>>>> 6116bbebaf44a8e2eb6ba9f37ed0ebd10d6f6e82

#include <iostream>

//#include <QApplication>

int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    //test DataTable

<<<<<<< HEAD
  /*  DataTable dt(5);
=======
    DataTable dt(5);
    dt.addKey("kolona a");
>>>>>>> 6116bbebaf44a8e2eb6ba9f37ed0ebd10d6f6e82
    dt.SetField("kolona a", 0, 2.3);
    dt.SetField("kolona a", 1, 2.4);

    std::map<std::string, std::vector<double>> mapa = dt.DoubleColumns();
    std::cout << mapa["kolona a"][0] << " " << mapa["kolona a"][1] << std::endl;
*/

<<<<<<< HEAD
    LinearRegressionNode lrn("mnj");
    lrn.run();
=======
    SourceNode sn("Test SourceNod");
    sn.setFilename("/home/aleksandra/Documents/faks/7.semestar/RS/projekat1/RS012-data-mining-toolbox/zoo.csv");
    sn.run();

    mapa = sn.OutputDataTable().DoubleColumns();
    int rowNum = mapa["KOSA"].size();
    for(auto m : mapa)
    {
        std::cout << m.first << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < rowNum; i++)
    {
        for(auto m : mapa)
        {
            std::cout << m.second[i] << " ";
        }
        std::cout << std::endl;
    }
>>>>>>> 6116bbebaf44a8e2eb6ba9f37ed0ebd10d6f6e82
}
