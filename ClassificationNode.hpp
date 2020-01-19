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
    void SetClassPredictions(const arma::Row<size_t> predictions);
    
    void Precision(arma::Row<size_t> values, arma::Row<size_t> predictions);
    void ConfusionMatrix(arma::Row<size_t> values, arma::Row<size_t> predictions);
    
    std::string GetPrecision() const;
    std::string GetConfusionMatrix() const;
    arma::Row<size_t> ClassPredictions() const;

protected:

    std::string targetColumnName;
    arma::Row<size_t> targetColumn;
    size_t numClasses;
    
    std::string precision;
    std::string confusionMatrix;
    
    arma::Row<size_t> classPredictions;

};

#endif // CLASSIFICATIONNODE_H
