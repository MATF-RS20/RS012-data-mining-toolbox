#ifndef LINEARREGRESSIONNODE_HPP
#define LINEARREGRESSIONNODE_HPP

#include "Node.hpp"

class LinearRegressionNode : public Node{

public:

    LinearRegressionNode(std::string name);

    ~LinearRegressionNode() override;

    void run() override;
};

#endif // LINEARREGRESSIONNODE_HPP
