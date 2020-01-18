#ifndef CLUSTERINGNODE_HPP
#define CLUSTERINGNODE_HPP
#include "Node.hpp"

class ClusteringNode : public Node {
public:
    ClusteringNode(std::string name);

    arma::Row<size_t> Labels();
    arma::mat Centroids();
    double silhouette_shadow();
    double SSC(size_t index, size_t label);
    double distance(size_t i , size_t j);

protected:
    arma::Row<size_t> labels;
    arma::mat centroids;
};

#endif // CLUSTERINGNODE_HPP
