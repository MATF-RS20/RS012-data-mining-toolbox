#include "StatisticsNode.hpp"

StatisticsNode::StatisticsNode(std::string name) : Node(name){}


void StatisticsNode::run() {

    arma::mat data = InputDataTable()->DataMatrix();
    std::vector<std::string> columns = InputDataTable()->ColumnNames();
    std::map<std::string, std::set<std::string>> mapOfCategories = InputDataTable()->CategoricalValues();

    unsigned long k = 0;
    for (unsigned long j = 0; j < columns.size(); j++){
        std::cout << "Column name: " << columns[j] << std::endl;
        if (mapOfCategories.find(columns[j]) == mapOfCategories.end()){

            double minimum_value = data(0, k);
            double maximum_value = data(0, k);
            double mean_value = 0;

            for(unsigned long i = 0; i < data.n_rows; i++) {
                if (minimum_value > data(i, k)){
                    minimum_value = data(i, k);
                } else if (maximum_value < data(i, k)){
                    maximum_value = data(i, k);
                }
                mean_value += data(i, k);
            }
            mean_value /= data.n_rows;

            double variance_value = 0;

            for(unsigned long i = 0; i < data.n_rows; i++) {
                variance_value += (data(i, k) - mean_value)*(data(i, k) - mean_value);
            }
            variance_value /= data.n_rows;

            std::cout << "Min: " << minimum_value << " Max: " << maximum_value
                      << " Mean: " << mean_value << " Var: " << variance_value << std::endl;
            k++;
        } else {
            //TODO
            k += mapOfCategories[columns[j]].size();
        }
    }

    DataTable dt = *InputDataTable();
    this->setOutDataTable(dt);

}

