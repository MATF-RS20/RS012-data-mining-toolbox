#include "LinearSVMNode.hpp"

LinearSVMNode::LinearSVMNode(std::string name) : ClassificationNode(name){}

double LinearSVMNode::Lambda() const{
    return lambda;
}
double LinearSVMNode::Delta() const{
    return delta;
}

void LinearSVMNode::SetLambda(double lambda){
    this->lambda = lambda;
}
void LinearSVMNode::SetDelta(double delta){
    this->delta = delta;
}
