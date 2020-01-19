#ifndef LINEARREGRESSIONNODE_HPP
#define LINEARREGRESSIONNODE_HPP

#include "Node.hpp"


// Classification node that we use for testing for the time being
class LinearRegressionNode : public Node{

public:

    LinearRegressionNode(std::string name);

    ~LinearRegressionNode() override;

    void setTarget(std::string targetName);
    void SetTargetColumn();
    void run() override;
    
    bool IsTargetSelected() const;
    
    void RSS(arma::Col<double> values, arma::Col<double> predictions);
    
    arma::Col<double> TargetPredictions() const;
    void SetTargetPredictions(const arma::Col<double> predictions);
    
    double RssScore() const;
    void SetRssScore(const double& score);
    
    arma::vec Params() const;
    void SetParams(const arma::vec& parameters);


protected:
    std::string targetColumnName;
    arma::Col<double> targetColumn;
    arma::Col<double> targetPredictions;
    double rssScore;
    arma::vec params;
};

#endif // LINEARREGRESSIONNODE_HPP
