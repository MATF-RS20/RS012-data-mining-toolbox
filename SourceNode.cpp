#include "SourceNode.hpp"
#include "csvreader.hpp"
#include <boost/algorithm/string.hpp>
#include <list>
#include <string>

SourceNode::SourceNode(std::string name): Node(name)
{
    this->setInputDataTable(nullptr);
}

//TODO: Proveriti da li je ovo neophodno! Dodato u pokusaju da proradi konstruktor kopije Stream klase (odnosno da bude pravo kopiranje cvorova)
//Nema veze sa kopiranjem Stream-a (proveriti kad kopiranje Stream-a proradi).
SourceNode::SourceNode(const SourceNode& sn) : Node(sn.NodeName()) {
    this->setFilename(sn.filename);
    this->setOutDataTable(sn.OutputDataTable());
}

void SourceNode::setFilename(std::string fName)
{
    filename = fName;
}

//TODO: Podeliti na read i set funkciju
void SourceNode::run()
{
    csvReader reader(filename);
    if(!reader.file.is_open())
    {
        std::cerr << "Invalid path to file" << std::endl;
        return;
    }
    unsigned long n = 0;

    std::string line;
    std::list<std::string> rows;

    getline(reader.file, line);
    std::list<std::string> columns;
    boost::split(columns, line, boost::is_any_of(","));

    while(getline(reader.file, line))
    {
        rows.push_back(line);
        n++;
    }

    DataTable dt(n);
    for(auto col : columns)
    {
        dt.addKey(col);
    }

    unsigned long i = 0;
    std::list<std::string> doubleRow;
    for(auto row : rows)
    {
        boost::split(doubleRow, row, boost::is_any_of(","));
        auto iter = doubleRow.cbegin();
        for(auto col : columns)
        {
            dt.SetField(col, i, std::stod(iter.operator*()));
            iter++;
        }
        i++;
    }

    this->setOutDataTable(dt);

}
