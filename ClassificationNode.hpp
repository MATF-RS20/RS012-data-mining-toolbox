#ifndef CLASSIFICATIONNODE_H
#define CLASSIFICATIONNODE_H

#include "Node.hpp"
#include <mlpack/core.hpp>
#include <map>
#include <algorithm>
#include <string.h>

//Abstract class that every classification will inherit
class ClassificationNode : public Node{

public:

    //Constructor
    ClassificationNode(std::string name);

    //Checking if target is selected
    bool IsVariableSelected();

    //Transforming target column into arma::row of numbers instead of the class values
    arma::Row<size_t> TransformToArma();

    //Setters
    void setTarget(std::string targetName);
    void SetNumClasses(const size_t& size);
    void SetClassPredictions(const arma::Row<size_t> predictions);
    
    //Methods that calculate precision and confusion matrix
    void Precision(arma::Row<size_t> values, arma::Row<size_t> predictions);
    void ConfusionMatrix(arma::Row<size_t> values, arma::Row<size_t> predictions);
    
    //Getters
    std::string TargetColumnName() const;
    arma::Row<size_t> TargetColumn() const;
    size_t NumClasses() const;
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
