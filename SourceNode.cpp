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

double helper (std::string value, std::string comparingValue) {
    if(0 == value.compare(comparingValue)) {
        return 1;
    }
    else {
        return 0;
    }
}

std::pair<unsigned, std::vector<double>> helper2(std::pair<const unsigned, std::vector<double>> p, unsigned added) {
    std::pair<unsigned, std::vector<double>> solution;
    solution.first = p.first + added;
    solution.second = p.second;
    return solution;
}

bool isDouble(std::string s) {

    try {
        std::stod(s);
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}

//TODO: Make a set function
void SourceNode::run()
{
    //Reading from file
    std::vector<std::vector<std::string>> rows = csvReader(filename).read();


    //Taking and erasing column names from read data
    std::vector<std::string> columns = rows.front();
    rows.erase(rows.begin());


    //Checking and memorizing indexes of columns and columns that are categorical/numeric and casting numerical data into double
    bool isCategorical = false;
    std::map<unsigned, std::vector<std::string>> categoricalColumns;
    std::map<unsigned, std::vector<double>> numericalColumns;

    for(unsigned i = 0; i < rows[0].size(); i++) {
        std::vector<std::string> catCol;
        std::vector<double> numCol;
        for(unsigned j = 0; j < rows.size(); j++) {
            catCol.push_back(rows[j][i]);
            if(!isCategorical) {
                isCategorical = !isDouble(rows[j][i]);
                if(!isCategorical) {
                    numCol.push_back(std::stod(rows[j][i]));
                }
            }
        }
        if(isCategorical) {
            isCategorical = false;
            categoricalColumns[i] = catCol;
        }
        else {
            numericalColumns[i] = numCol;
        }
    }


    //Adding column names and their "binary" numbers into DataTable
    DataTable dt;
    for(unsigned i = 0; i < columns.size(); i++) {
        if(numericalColumns.find(i) != numericalColumns.end()) {
            dt.addKey(columns[i]);
        }
        else {
            dt.addKey(columns[i]);
        }
    }


    //Binarising categorical columns and adding categories in DataTable dt
    unsigned added = 0;
    for(auto c : categoricalColumns) {
        std::set<std::string> categories(c.second.begin(), c.second.end());
        dt.addCategoricalValues(c.first, categories);
        unsigned numOfCategories = categories.size();
        for(auto i = numericalColumns.rbegin(); i->first <= c.first + added; i++) {
            std::vector<double> tmp = i->second;
            numericalColumns[i->first + numOfCategories] = tmp;
        }
        for(auto v : categories) {
            std::vector<double> binCol(numericalColumns[0].size());
            std::transform(c.second.begin(), c.second.end(), binCol.begin(), std::bind(helper, std::placeholders::_1, v));
            numericalColumns[c.first + added] = binCol;
            added++;
        }
    }

    //TODO: Is there a better way to initialize matrix?
    arma::mat matrix(numericalColumns[0].size(), numericalColumns.size());
    for(unsigned j = 0; j < numericalColumns.size(); j++) {
        for(unsigned i = 0; i < numericalColumns[j].size(); i++) {
            matrix(i,j) = numericalColumns[j][i];
        }
    }

    dt.SetDataMatrix(matrix);

    this->setOutDataTable(dt);

}
