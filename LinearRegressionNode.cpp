#include "LinearRegressionNode.hpp"

#include <armadillo>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
//#include <mlpack/core.hpp>

LinearRegressionNode::LinearRegressionNode(std::string name)
    :Node(name){}

LinearRegressionNode::~LinearRegressionNode(){}

void LinearRegressionNode::run(){

    // parsing DataTable object into arma matrix
    // TODO: implement parsing as a member function of class Node
    arma::mat data(InputDataTable()->NumberOfRows(), InputDataTable()->ColumnNames().size());
    unsigned long j;
    for (unsigned long i = 0; i < InputDataTable()->NumberOfRows(); i++){
        j = 0;
        for (auto column : InputDataTable()->ColumnNames()){
             data(i, j) = InputDataTable()->DoubleColumns()[column][i];
             j++;
        }
    }

    // target column (used just for testing)
    arma::vec responses = arma::vec(InputDataTable()->NumberOfRows(), arma::fill::ones);

    mlpack::regression::LinearRegression lr(trans(data), responses);

    arma::vec parameters = lr.Parameters();
    std::cout << "Paramtetes: " << std::endl;
    std::cout << parameters << std::endl;

    arma::vec predictions;
    lr.Predict(trans(data), predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;
}
