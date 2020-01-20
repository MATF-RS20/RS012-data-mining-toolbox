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
    //Number of binarized columns we skip
    size_t catColSum = 0;
    size_t numOfFiltered = 0;

    //Iterating through column names in data table
    for (size_t i = 0; i != colNames.size(); i++) {

        //If the current column name exists in the set of column names that need to be filtered
        if(columnNames.end() != columnNames.find(colNames[i])) {

            //If the current column name exists also in categoricalValues of input
            if(catCol.find(colNames[i]) != catCol.end()) {

                //Erase column name from categoricalValues and
                size_t numOfCol = catCol.at(colNames[i]).size();
                catCol.erase(colNames[i]);
                //Shed column with index i, numOfCol times (arma::mat shed_cols(i), all indexes after i will decrement)
                //i-numOfFiltered because of the above reason (if we already sheded a column)
                while(numOfCol > 0) {

                    matrix.shed_col(i+catColSum-numOfFiltered);
                    numOfCol--;
                }
            //Otherwise, just shed i+catColSum (add the number of categorical binarized columns that we didnt filter)
            } else {

                matrix.shed_col(i +catColSum);
            }
            numOfFiltered++;
        } else {

            //Otherwise if column name is a key in the map categoricalValues, increase catColSum by the number of columns we skipped
            if(catCol.find(colNames[i]) != catCol.end()) {

                catColSum += catCol.at(colNames[i]).size() -1;
            }
        }
    }

    //Make a new vector of column names
    std::vector<std::string> filteredColNames(colNames.size() - columnNames.size());
    std::copy_if(colNames.begin(), colNames.end(), filteredColNames.begin(), [this](std::string x){return (columnNames.end() == columnNames.find(x));});

    //Make and set a new data table. Set it to be outDataTable
    DataTable dt(*inputDataTable);
    dt.SetDataMatrix(matrix);
    dt.SetColumnNames(filteredColNames);
    dt.SetCategoricalValues(catCol);
    this->setOutDataTable(dt);
}
