#ifndef LINEARREGRESSIONNODE_HPP
#define LINEARREGRESSIONNODE_HPP

#include "Node.hpp"


// Classification node that we use for testing for the time being
class LinearRegressionNode : public Node{

public:

    LinearRegressionNode(std::string name);

    ~LinearRegressionNode() override;

    void setTarget(std::string targetName);
    void run() override;


protected:
    std::string targetColumnName;
    arma::Col<double> targetColumn;
};

#endif // LINEARREGRESSIONNODE_HPP
