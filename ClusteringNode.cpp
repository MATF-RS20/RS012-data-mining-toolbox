#include "ClusteringNode.hpp"

ClusteringNode::ClusteringNode(std::string name) : Node(name) {}

arma::Row<size_t> ClusteringNode::Labels() {
    return labels;
}
arma::mat ClusteringNode::Centroids() {
    return centroids;
}


double ClusteringNode::silhouette_shadow() {
    return -1;
}
