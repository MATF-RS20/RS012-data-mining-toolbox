#include "LinearRegressionNode.hpp"

#include <mlpack/methods/linear_regression/linear_regression.hpp>
//#include <mlpack/core.hpp>

LinearRegressionNode::LinearRegressionNode(std::string name)
    :Node(name){}

LinearRegressionNode::~LinearRegressionNode(){}

void LinearRegressionNode::setTarget(std::string targetName) {
    targetColumnName = targetName;

    std::vector<std::string> columns = inputDataTable->ColumnNames();
    for(unsigned i = 0; i < columns.size(); i++) {
        if(0 == columns[i].compare(targetName)) {
            std::map<std::string, std::set<std::string>> map = inputDataTable->CategoricalValues();
            if(map.find(targetName) != map.end()) {
                std::cout << "Greska! Izabrana kolona sa kategorickom vrednoscu!" << std::endl;
                return;
            }
            else {
                targetColumn = *(inputDataTable->DataMatrix().begin_col(i));
            }
        }
    }
}

void LinearRegressionNode::run(){

    arma::mat data = InputDataTable()->DataMatrix();
    mlpack::regression::LinearRegression lr(trans(data), targetColumn);

    arma::vec parameters = lr.Parameters();
    std::cout << "Paramtetes: " << std::endl;
    std::cout << parameters << std::endl;

<<<<<<< HEAD
    arma::Col<double> predictions;
=======
    arma::Row<double> predictions;
>>>>>>> 59bddef1d2a1a5cc45864427b292f307edb84d78
    lr.Predict(trans(data), predictions);

    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;
}
