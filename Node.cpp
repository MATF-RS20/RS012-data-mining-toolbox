#include "Node.hpp"

Node::Node(std::string name) : nodeName(name){}

const DataTable* Node::InputDataTable() const{
    return inputDataTable;
}

DataTable Node::OutputDataTable() const {
    return outputDataTable;
}

//TODO: Proveriti da li je ovo neophodno! Dodato u pokusaju da se pozove konstruktor Node klase u konstruktoru kopije klase SourceNode
std::string Node::NodeName() const {
    return nodeName;
}

//TODO: Proveriti da li je ovo neophodno! Dodato u pokusaju da proradi destruktor Stream klase
DataTable * Node::RefOutputDataTable(){
    return &outputDataTable;
}

void Node::setInputDataTable(DataTable* inDataTable)
{
    inputDataTable = inDataTable;
}

void Node::setOutDataTable(DataTable outDataTable)
{
    outputDataTable = outDataTable;
}


std::vector<std::string> Node::unbinarize(std::string columnName) {
    std::vector<std::string> result(InputDataTable()->DataMatrix().n_rows);
    unsigned colIndex = 0;
    const std::map<std::string, std::set<std::string>> map_tmp = InputDataTable()->CategoricalValues();
    for(auto i = InputDataTable()->ColumnNames().begin(); i != InputDataTable()->ColumnNames().end(); i++) {
        if(0 == (*i).compare(columnName)) {
            break;
        }
        else if(map_tmp.find(*i) != map_tmp.end()) {
            colIndex += map_tmp.at(*i).size();
        }
        else {
            colIndex++;
        }
    }

    for(unsigned i = 0; i < InputDataTable()->DataMatrix().n_rows; i++) {
        unsigned tmp = colIndex;
        for(auto c : map_tmp.at(columnName)) {
            //std::transform(OutputDataTable().DataMatrix().begin_col(colIndex), OutputDataTable().DataMatrix().end_col(colIndex), result.begin(), [c](double x){if (fabs(x-1) < 0.00001) return c;});
            if(InputDataTable()->DataMatrix()(i, colIndex)) {
                result[i] = c;
                break;
            }
            colIndex++;
        }
        colIndex = tmp;
    }

    return result;
}

arma::mat Node::filterBinarisedCol(std::string colName) {
    std::vector<std::string> colNames = inputDataTable->ColumnNames();
    unsigned index = 0;
    for(unsigned i = 0; i != colNames.size(); i++) {
        if(0 == colNames[i].compare(colName)) {
            index = i;
            break;
        }
    }

    unsigned numberOfCol = inputDataTable->CategoricalValues()[colName].size();

    arma::mat result = inputDataTable->DataMatrix();
    for(unsigned i = index+numberOfCol -1; i >= index; i--) {
        result.shed_col(i);
    }

    return result;
}
