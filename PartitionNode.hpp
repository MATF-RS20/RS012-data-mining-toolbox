#ifndef PARTITIONNODE_H
#define PARTITIONNODE_H

#include "Node.hpp"

class PartitionNode : public Node {

public:

    PartitionNode(std::string name);

    void run() override;

    double TestSizeRatio() const;

    void SetTestSizeRatio(const double &size);

private:

    double testSizeRatio;
};

#endif // PARTITIONNODE_H
