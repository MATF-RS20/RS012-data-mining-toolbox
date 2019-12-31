#ifndef CLASSIFICATIONNODE_H
#define CLASSIFICATIONNODE_H

#include "Node.hpp"
#include <mlpack/core.hpp>

class ClassificationNode : public Node{

public:

    ClassificationNode(std::string name);

    bool IsVariableSelected();

    std::vector<std::string> TargetVariable() const;

    void SetTargetVariable(std::vector<std::string> Variable);

    arma::Row<size_t> TransformToArma();

private:

    std::vector<std::string> targetVariable;

};

#endif // CLASSIFICATIONNODE_H
