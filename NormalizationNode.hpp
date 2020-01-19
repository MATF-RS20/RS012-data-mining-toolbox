#ifndef NORMALIZATIONNODE_H
#define NORMALIZATIONNODE_H

#include "Node.hpp"

//Node that normalizes data (put all fields in range of [0,1])
class NormalizationNode : public Node {

public:

    NormalizationNode(std::string name);

    void run() override;

};

#endif // NORMALIZATIONNODE_H
