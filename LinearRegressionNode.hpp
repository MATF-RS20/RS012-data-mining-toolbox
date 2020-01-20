#ifndef LINEARREGRESSIONNODE_HPP
#define LINEARREGRESSIONNODE_HPP

#include "Node.hpp"
#include <mlpack/methods/linear_regression/linear_regression.hpp>


// Node for Linear Regression
class LinearRegressionNode : public Node{

public:

    LinearRegressionNode(std::string name);

    ~LinearRegressionNode() override;

    //Getters
    arma::Col<double> TargetPredictions() const;
    double RssScore() const;
    arma::vec Params() const;

    //Setters
    void setTarget(std::string targetName);
    void SetTargetColumn();
    void SetTargetPredictions(const arma::Col<double> predictions);
    void SetRssScore(const double& score);
    void SetParams(const arma::vec& parameters);
    
    //Checking if target is selected
    bool IsTargetSelected() const;
    
    //Calculating rssScore
    void RSS(arma::Col<double> values, arma::Col<double> predictions);



    void run() override;

protected:
    //Target
    std::string targetColumnName;
    arma::Col<double> targetColumn;
    //Predictions
    arma::Col<double> targetPredictions;
    //Paramater that estimates the quality of the result model
    double rssScore;
    //Parameters
    arma::vec params;
};

#endif // LINEARREGRESSIONNODE_HPP
