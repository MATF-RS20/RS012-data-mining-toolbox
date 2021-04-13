#include "StatisticsNode.hpp"

StatisticsNode::StatisticsNode(std::string name) : Node(name) {}

void StatisticsNode::run() {

  arma::mat data = InputDataTable()->DataMatrix();
  std::vector<std::string> columns = InputDataTable()->ColumnNames();
  std::map<std::string, std::set<std::string>> mapOfCategories =
      InputDataTable()->CategoricalValues();

  unsigned long k = 0;
  std::string result;
  for (auto &column : columns) {
    // Putting a column name in the reulting string
    result += "Column name: ";
    result += column;
    result += "\n";
    if (mapOfCategories.find(column) == mapOfCategories.end()) {

      double minimum_value = data(0, k);
      double maximum_value = data(0, k);
      double mean_value = 0;

      // Finding min, max and mean for the values in that column
      for (unsigned long i = 0; i < data.n_rows; i++) {
        if (minimum_value > data(i, k)) {
          minimum_value = data(i, k);
        } else if (maximum_value < data(i, k)) {
          maximum_value = data(i, k);
        }
        mean_value += data(i, k);
      }
      mean_value /= data.n_rows;

      // Finding variance for the values in that column
      double variance_value = 0;

      for (unsigned long i = 0; i < data.n_rows; i++) {
        variance_value += (data(i, k) - mean_value) * (data(i, k) - mean_value);
      }
      variance_value /= data.n_rows;

      // Puting all those values in the resulting string
      result += "Min: ";
      result += std::to_string(minimum_value);
      result += " Max: ";
      result += std::to_string(maximum_value);
      result += " Mean: ";
      result += std::to_string(mean_value);
      result += " Var: ";
      result += std::to_string(variance_value);
      result += "\n";
      k++;
    } else {
      // TODO
      k += mapOfCategories[column].size();
    }
  }

  // Setting output message and outputDataTable
  statistics = result;
  setOutputMessage(result);
  DataTable dt = *InputDataTable();
  this->setOutDataTable(dt);
}

// Getter
std::string StatisticsNode::GetStatistics() const { return statistics; }
