#ifndef PERCEPTRONNODE_HPP
#define PERCEPTRONNODE_HPP

#include "ClassificationNode.hpp"

class PerceptronNode : public ClassificationNode{

public:

    PerceptronNode(std::string name);

    void run() override;
};

#endif // PERCEPTRONNODE_HPP
