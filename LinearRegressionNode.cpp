#include "LinearRegressionNode.hpp"

#include <mlpack/methods/linear_regression/linear_regression.hpp>
//#include <mlpack/core.hpp>

LinearRegressionNode::LinearRegressionNode(std::string name)
    :Node(name){}

LinearRegressionNode::~LinearRegressionNode(){}

void LinearRegressionNode::run(){

    arma::mat data = InputDataTable()->DataMatrix();

    // target column (used just for testing)
    arma::vec responses = arma::vec(InputDataTable()->DataMatrix().n_rows, arma::fill::ones);

    mlpack::regression::LinearRegression lr(trans(data), responses);

    arma::vec parameters = lr.Parameters();
    std::cout << "Paramtetes: " << std::endl;
    std::cout << parameters << std::endl;

    arma::vec predictions;
    lr.Predict(trans(data), predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;
}
