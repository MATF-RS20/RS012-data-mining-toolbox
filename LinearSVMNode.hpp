#ifndef LINEARSVMNODE_HPP
#define LINEARSVMNODE_HPP

#include "ClassificationNode.hpp"

class LinearSVMNode : public ClassificationNode {

public:
  LinearSVMNode(std::string name);

  double Lambda() const;
  double Delta() const;

  void SetLambda(double lambda);
  void SetDelta(double delta);

private:
  double lambda;
  double delta;
};

#endif // LINEARSVMNODE_HPP
