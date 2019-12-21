#include "SourceNode.hpp"
#include "csvreader.hpp"
#include <boost/algorithm/string.hpp>
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

void SourceNode::setHasClass(bool hasCl) {
    hasClass = hasCl;
}

std::vector<std::string> SourceNode::read() {

    std::vector<std::string> rows;

    csvReader reader(filename);
    if(!reader.file.is_open())
    {
        std::cerr << "Invalid path to file" << std::endl;
        return rows;
    }
    unsigned long n = 0;

    std::string line;

    while(getline(reader.file, line))
    {
        rows.push_back(line);
        n++;
    }
    return rows;
}

//TODO: Podeliti na read i set funkciju
void SourceNode::run()
{
    std::vector<std::string> rows = read();
    std::string line = rows.front();
    rows.erase(rows.begin());
    unsigned n = rows.size();

    std::vector<std::string> columns;
    boost::split(columns, line, boost::is_any_of(","));

    DataTable dt;
    for(auto col : columns)
    {
        dt.addKey(col);
    }

    //TODO: Is there a better way to initialize matrix?
    arma::mat matrix(n, columns.size());
    std::vector<std::string> strRow;
    int j = 0;
    for(auto r : rows) {
        boost::split(strRow, r, boost::is_any_of(","));
        for(auto i = 0; i < matrix.n_cols; i++) {
            matrix(j,i) = std::stod(strRow.at(i));
        }
    }
    dt.SetDataMatrix(matrix);

    this->setOutDataTable(dt);

}
