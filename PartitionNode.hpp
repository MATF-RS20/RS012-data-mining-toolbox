#ifndef PARTITIONNODE_H
#define PARTITIONNODE_H

#include "Node.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Partitions data to train and test set
class PartitionNode : public Node {

public:
  // Constructor
  explicit PartitionNode(std::string name);

  // Getter
  double TestSizeRatio() const;

  // Setter
  void SetTestSizeRatio(const double &size);

  void run() override;

private:
  // Ratio of size of test set
  double testSizeRatio;
};

#endif // PARTITIONNODE_H
