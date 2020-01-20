#ifndef CLUSTERINGNODE_HPP
#define CLUSTERINGNODE_HPP

#include "Node.hpp"
#include <limits>

//Abstract class for all clustering algorithms
class ClusteringNode : public Node {
public:

    //Constructor
    ClusteringNode(std::string name);

    //Getters
    arma::Row<size_t> Labels();
    arma::mat Centroids();
    double SilhouetteScore();

    //Method that estimates results
    void silhouette_shadow();
    //Helper functions for above method
    double SSC(size_t index, size_t label);
    double distance(size_t i , size_t j);

protected:

    //Result of an algorithm should be a row of labels, one for every tuple, indicating in which cluster the tuple belongs,
    //and matrix of centroids of clusters.
    arma::Row<size_t> labels;
    arma::mat centroids;
    //Estimation of the result
    double silhouetteScore;
};

#endif // CLUSTERINGNODE_HPP
