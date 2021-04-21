#ifndef PERCEPTRONNODE_HPP
#define PERCEPTRONNODE_HPP

#include "ClassificationNode.hpp"
#include <mlpack/methods/perceptron/perceptron.hpp>
#include <string>

class PerceptronNode : public ClassificationNode {

public:
  explicit PerceptronNode(std::string name);

  void run() override;
};

#endif // PERCEPTRONNODE_HPP
