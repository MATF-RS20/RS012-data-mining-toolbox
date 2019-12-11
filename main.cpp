//#include "mainwindow.hpp"
#include "DataTable.hpp"
#include "SourceNode.hpp"

#include <iostream>

//#include <QApplication>

int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/

    //test DataTable

    DataTable dt(5);
    dt.addKey("kolona a");
    dt.SetField("kolona a", 0, 2.3);
    dt.SetField("kolona a", 1, 2.4);

    std::map<std::string, std::vector<double>> mapa = dt.DoubleColumns();
    std::cout << mapa["kolona a"][0] << " " << mapa["kolona a"][1] << std::endl;

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
}
