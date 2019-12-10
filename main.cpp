//#include "mainwindow.hpp"
#include "DataTable.hpp"

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
    dt.SetField("kolona a", 0, 2.3);
    dt.SetField("kolona a", 1, 2.4);

   std::map<std::string, std::vector<double>> mapa = dt.DoubleColumns();

    std::cout << mapa["kolona a"][0] << " " << mapa["kolona a"][1] << std::endl;

}
