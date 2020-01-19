#include "FilterNode.hpp"

FilterNode::FilterNode(std::string name) : Node(name) {}

std::set<std::string> FilterNode::ColumnNames() {

    return columnNames;
}

void FilterNode::SetColumnNames(std::set<std::string> colNames) {

    columnNames = colNames;
}

void FilterNode::AddColumn(std::string colName) {

    columnNames.insert(colName);
}

void FilterNode::RemoveColName(std::string colName) {

    for(auto iter = columnNames.begin(); iter != columnNames.end(); iter++) {

        if(0 == colName.compare(*iter)) {

            columnNames.erase(iter);
            break;
        }
    }
}

void FilterNode::run() {

    auto matrix = inputDataTable->DataMatrix();
    auto colNames = inputDataTable->ColumnNames();
    auto catCol = inputDataTable->CategoricalValues();
    size_t catColSum = 0;
    size_t numOfFiltered = 0;

    for (size_t i = 0; i != colNames.size(); i++) {

        if(columnNames.end() != columnNames.find(colNames[i])) {

            if(catCol.find(colNames[i]) != catCol.end()) {

                size_t numOfCol = catCol.at(colNames[i]).size();
                catCol.erase(colNames[i]);
                while(numOfCol > 0) {

                    matrix.shed_col(i-numOfFiltered);
                    numOfCol--;
                }
            } else {

                matrix.shed_col(i +catColSum);
            }
            numOfFiltered++;
        } else {

            if(catCol.find(colNames[i]) != catCol.end()) {

                catColSum += catCol.at(colNames[i]).size() -1;
            }
        }
    }

    std::vector<std::string> filteredColNames(colNames.size() - columnNames.size());
    std::copy_if(colNames.begin(), colNames.end(), filteredColNames.begin(), [this](std::string x){return (columnNames.end() == columnNames.find(x));});

    DataTable dt(*inputDataTable);
    dt.SetDataMatrix(matrix);
    dt.SetColumnNames(filteredColNames);
    dt.SetCategoricalValues(catCol);
    this->setOutDataTable(dt);
}
