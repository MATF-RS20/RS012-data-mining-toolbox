#ifndef NORMALIZATIONNODE_H
#define NORMALIZATIONNODE_H

#include "Node.hpp"

class NormalizationNode : public Node {

public:

    NormalizationNode(std::string name);

    void run() override;

};

#endif // NORMALIZATIONNODE_H
