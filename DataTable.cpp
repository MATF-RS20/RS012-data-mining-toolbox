#include "DataTable.hpp"

//Constructor
DataTable::DataTable(){
    isPartitioned = false;
    testSize = 0;
}

//Destructor
DataTable::~DataTable()= default;


//Copy constructor
DataTable::DataTable(const DataTable& dt)
    : dataMatrix(dt.DataMatrix()),
      columnNames(dt.ColumnNames()),
      categoricalValues(dt.CategoricalValues()),
      partition(dt.Partition()),
      isPartitioned(dt.IsPartitioned()),
      testSize(dt.TestSize()){}

      
//Getters
arma::mat DataTable::DataMatrix() const {
    return dataMatrix;
}

std::vector<std::string> DataTable::ColumnNames() const {
    return columnNames;
}

std::map<std::string, std::set<std::string>> DataTable::CategoricalValues() const {
    return categoricalValues;
}

std::vector<bool> DataTable::Partition() const {
    return partition;
}

bool DataTable::IsPartitioned() const {
    return isPartitioned;
}

unsigned long DataTable::TestSize() const {
    return testSize;
}


//Setters
void DataTable::SetDataMatrix(const arma::mat& matrix){
    dataMatrix = matrix;
}

void DataTable::SetCategoricalValues(const std::map<std::string, std::set<std::string>> & catVal){
    categoricalValues = catVal;
}
   
void DataTable::SetColumnNames(const std::vector<std::string>& colNames){
    columnNames = colNames;
}

void DataTable::SetPartition(const std::vector<bool>& vector){
    partition = vector;
}

void DataTable::SetIsPartitioned(const bool & isSet){
    isPartitioned = isSet;
}

void DataTable::SetTestSize(const unsigned long & size){
    testSize = size;
}


//Adding a key (that means column name) into a vector of column names
void DataTable::addKey(const std::string& keyName) {
    columnNames.emplace_back(keyName);
}

//Adding a set of values for a categorical column with given index into categoricalValues
void DataTable::addCategoricalValues(unsigned columnIndex, std::set<std::string> setOfValues) {
    categoricalValues[columnNames[columnIndex]] = setOfValues;
}
