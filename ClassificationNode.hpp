#ifndef CLASSIFICATIONNODE_H
#define CLASSIFICATIONNODE_H

#include "Node.hpp"
#include <mlpack/core.hpp>
#include <map>

class ClassificationNode : public Node{

public:

    ClassificationNode(std::string name);

    bool IsVariableSelected();

    std::string TargetColumnName() const;
    arma::Row<size_t> TargetColumn() const;
    std::vector<std::string> unbinarize(std::string columnName);

    arma::Row<size_t> TransformToArma();
    void setTarget(std::string targetName);

protected:

    std::string targetColumnName;
    arma::Row<size_t> targetColumn;

};

#endif // CLASSIFICATIONNODE_H
