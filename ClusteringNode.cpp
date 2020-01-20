#include "ClusteringNode.hpp"
#include <limits>

ClusteringNode::ClusteringNode(std::string name)
    : Node(name), silhouetteScore(-2)
{}

arma::Row<size_t> ClusteringNode::Labels() {
    /*
    if(0.00001 < fabs(-2- silhouetteScore)) {
        return labels;
    } else {
        std::cout << "1) Klasterovanje mora biti pokrenuto!" << std::endl;
        return nullptr;
    }
    */
    return  labels;
}

arma::mat ClusteringNode::Centroids() {
    /*
    if(0.00001 < fabs(-2- silhouetteScore)) {
        return centroids;
    } else {
        std::cout << "2) Klasterovanje mora biti pokrenuto!" << std::endl;
        return nullptr;
    }
    */
    return  centroids;
}

double ClusteringNode::SilhouetteScore() {

    if(0.00001 >= fabs(-2- silhouetteScore)) {
        std::cout << "3) Klasterovanje mora biti pokrenuto!" << std::endl;
    }
    return silhouetteScore;
}

double ClusteringNode::distance(size_t i, size_t j) {

    auto matrix = inputDataTable->DataMatrix();
    std::vector<size_t> indexes(matrix.n_cols);
    std::iota(indexes.begin(), indexes.end(), 0);

    return  std::accumulate(indexes.begin(), indexes.end(), 0.0,
                            [matrix, i, j](double acc, size_t x){return acc+(matrix(i, x) - matrix(j, x))*(matrix(i, x) - matrix(j, x));});
}

double ClusteringNode::SSC(size_t index, size_t label) {

    std::vector<size_t> indexes(labels.n_cols);
    std::iota(indexes.begin(), indexes.end(), 0);

    return std::accumulate(indexes.begin(), indexes.end(), 0.0,
                    [index, label, this](double acc, size_t x){if(label == labels(x)) return acc+distance(x, index);
                                                        else return acc;});
}

void ClusteringNode::silhouette_shadow() {

    std::map<size_t, unsigned long> sizesOfClusters;
    std::set<size_t> setLabel(labels.begin(), labels.end());

    for(auto l : setLabel) {


        sizesOfClusters[l] = std::accumulate(labels.begin(), labels.end(), static_cast<size_t>(0),
                                             [l](size_t acc, size_t x){if (x == l) return ++acc; else return acc;});
        if(sizesOfClusters[l] == 0){
            silhouetteScore = 0;
               return;
        }
    }

    double s = 0;
    for(size_t i = 0; i < labels.n_cols; i++) {
        double a = SSC(i, labels(i))/ sizesOfClusters[labels[i]];
        double minNeighbour = std::numeric_limits<double>::infinity();
        for(auto l : setLabel) {

            if(l != labels[i]) {

                double tmp = SSC(i, labels(l)) /sizesOfClusters[l];
                if(tmp < minNeighbour) {

                    minNeighbour = tmp;
                }
            }
        }

        s += (minNeighbour - a)/std::max(minNeighbour, a);
    }

    silhouetteScore = s/labels.n_cols;
}
