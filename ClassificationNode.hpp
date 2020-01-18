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
    size_t NumClasses() const;
    std::vector<std::string> unbinarize(std::string columnName);

    arma::Row<size_t> TransformToArma();
    void setTarget(std::string targetName);
    void SetNumClasses(const size_t& size);
    
    double Precision(arma::Row<size_t> values, arma::Row<size_t> predictions) const;
    void ConfussionMatrix(arma::Row<size_t> values, arma::Row<size_t> predictions) const;

protected:

    std::string targetColumnName;
    arma::Row<size_t> targetColumn;
    size_t numClasses;

};

#endif // CLASSIFICATIONNODE_H
