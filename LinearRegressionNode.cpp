#include "LinearRegressionNode.hpp"

#include <armadillo>
#include <mlpack/methods/linear_regression/linear_regression.hpp>
//#include <mlpack/core.hpp>

LinearRegressionNode::LinearRegressionNode(std::string name)
    :Node(name){}

LinearRegressionNode::~LinearRegressionNode(){}

void LinearRegressionNode::run(){
    arma::mat dataMatrix = arma::mat(3, 3, arma::fill::zeros);

    double k = 1.0;
    for(unsigned long long i = 0; i < dataMatrix.n_rows; i++){
        for (unsigned long long j = 0; j < dataMatrix.n_cols; j++){
            dataMatrix(i, j) = k;
            k += 1.0;
        }
    }

    for(unsigned long long i = 0; i < dataMatrix.n_rows; i++){
        for (unsigned long long j = 0; j < dataMatrix.n_cols; j++){
            std::cout << dataMatrix(i, j) << " ";
        }
        std::cout << std::endl;
    }

    //arma::mat data;
    //arma::mat data = {(0),(1),(2),(3),(4)};
    arma::vec responses = {3,6,7};

     //Regress.
    mlpack::regression::LinearRegression lr(trans(dataMatrix), responses);
    // Get the parameters, or coefficients.
    arma::vec parameters = lr.Parameters();
    std::cout << parameters << std::endl;

    arma::vec predictions;
    lr.Predict(trans(dataMatrix), predictions);
    std::cout << predictions << std::endl;
}
