#include "ClusteringNode.hpp"
#include <limits>

ClusteringNode::ClusteringNode(std::string name) : Node(name) {}

arma::Row<size_t> ClusteringNode::Labels() {
    return labels;
}

arma::mat ClusteringNode::Centroids() {
    return centroids;
}

double ClusteringNode::distance(size_t i, size_t j) {

    auto matrix = inputDataTable->DataMatrix();
    std::vector<size_t> indexes(matrix.n_cols);
    std::iota(indexes.begin(), indexes.end(), 0);

    return  std::accumulate(indexes.begin(), indexes.end(), 0,
                            [matrix, i, j](double acc, size_t x){return acc+(matrix(i, x) - matrix(j, x))*(matrix(i, x) - matrix(j, x));});
}

double ClusteringNode::SSC(size_t index, size_t label) {

    std::vector<size_t> indexes(labels.n_cols);
    std::iota(indexes.begin(), indexes.end(), 0);

    return std::accumulate(indexes.begin(), indexes.end(), 0,
                    [index, label, this](double acc, size_t x){if(label == labels(x)) return acc+distance(x, index);
                                                        else return acc;});
}

double ClusteringNode::silhouette_shadow() {

    std::map<size_t, unsigned long> sizesOfClusters;
    std::set<size_t> setLabel(labels.begin(), labels.end());

    for(auto l : setLabel) {
        sizesOfClusters[l] = std::accumulate(labels.begin(), labels.end(), 0,
                                             [l](unsigned long acc, size_t x){if (x == l) return ++acc; else return acc;});
    }

    double s = 0;
    for(size_t i = 0; i < labels.n_cols; i++) {
        double a = SSC(i, labels(i))/ sizesOfClusters[labels[i]];
        double minNeighbour = std::numeric_limits<double>::infinity();
        for(auto l : setLabel) {

            if(l != labels[i]) {

                double tmp = SSC(i, labels[l])/ sizesOfClusters[l];
                if(tmp < minNeighbour) {

                    minNeighbour = tmp;
                }
            }
        }

        s += (minNeighbour - a)/std::max(minNeighbour, a);
    }

    return s/labels.n_cols;
}
