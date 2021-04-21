#ifndef DATATABLE_H
#define DATATABLE_H

#include <iostream>
#include <map>
#include <mlpack/core.hpp>
#include <vector>

class DataTable {

public:
  // Constructor
  DataTable();

  // Copy constructor
  DataTable(const DataTable &dt);

  // Destructor
  ~DataTable();

  // Getters
  arma::mat DataMatrix() const;
  std::vector<std::string> ColumnNames() const;
  std::map<std::string, std::set<std::string>> CategoricalValues() const;
  std::vector<bool> Partition() const;
  bool IsPartitioned() const;
  unsigned long TestSize() const;

  // Setters
  void SetDataMatrix(const arma::mat &matrix);
  void SetCategoricalValues(
      const std::map<std::string, std::set<std::string>> &catVal);
  void SetColumnNames(const std::vector<std::string> &colNames);
  void SetPartition(const std::vector<bool> &vector);
  void SetIsPartitioned(const bool &isSet);
  void SetTestSize(const unsigned long &size);

  // Adding in maps
  void addKey(const std::string &keyName);
  void addCategoricalValues(unsigned columnIndex, std::set<std::string>);

private:
  // Data from .csv file are cast in double or binarized and put in dataMatrix.
  arma::mat dataMatrix;

  // Names of columns are read from .csv file and put in vector.
  std::vector<std::string> columnNames;

  // Columns that are categorical and cannot be cast in double are binarized,
  // and the set of their possible values is remembered in in map
  // categoricalValues, where key is the name of that column.
  std::map<std::string, std::set<std::string>> categoricalValues;

  // If there is partition of data, this vector has info for every tuple is it
  // in training or in test set.
  std::vector<bool> partition;

  // If there is partition of data, testSize is number of tuples in test set.
  unsigned long testSize;

  // Indicator of whether there is partition of data.
  bool isPartitioned = false;
};

#endif // DATATABLE_H
