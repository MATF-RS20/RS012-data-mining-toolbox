#ifndef LINEARREGRESSIONNODE_HPP
#define LINEARREGRESSIONNODE_HPP

#include "Node.hpp"


// Classification node that we use for testing for the time being
class LinearRegressionNode : public Node{

public:

    LinearRegressionNode(std::string name);

    ~LinearRegressionNode() override;

    void run() override;
};

#endif // LINEARREGRESSIONNODE_HPP
