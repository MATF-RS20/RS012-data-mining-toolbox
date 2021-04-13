#include "ClusteringNode.hpp"

ClusteringNode::ClusteringNode(std::string name)
    : Node(name), silhouetteScore(-2) {}

// Getters
arma::Row<size_t> ClusteringNode::Labels() {
  /*
  if(0.00001 < fabs(-2- silhouetteScore)) {
      return labels;
  } else {
      std::cout << "1) Klasterovanje mora biti pokrenuto!" << std::endl;
      return nullptr;
  }
  */
  return labels;
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
  return centroids;
}

double ClusteringNode::SilhouetteScore() {

  if (0.00001 >= fabs(-2 - silhouetteScore)) {
    std::cout << "3) Klasterovanje mora biti pokrenuto!" << std::endl;
  }
  return silhouetteScore;
}

// A helper function used in silhouette_score. Measures distance between two
// tuples (given by indexes)
double ClusteringNode::distance(size_t i, size_t j) {

  auto matrix = inputDataTable->DataMatrix();
  std::vector<size_t> indexes(matrix.n_cols);
  std::iota(indexes.begin(), indexes.end(), 0);

  return std::accumulate(indexes.begin(), indexes.end(), 0.0,
                         [matrix, i, j](double acc, size_t x) {
                           return acc + (matrix(i, x) - matrix(j, x)) *
                                            (matrix(i, x) - matrix(j, x));
                         });
}

// A helper function used in silhouette_score. Sum of distances between
// specified tuple (given by index) and all tuples in specified cluster (given
// by label).
double ClusteringNode::SSC(size_t index, size_t label) {

  std::vector<size_t> indexes(labels.n_cols);
  std::iota(indexes.begin(), indexes.end(), 0);

  return std::accumulate(indexes.begin(), indexes.end(), 0.0,
                         [index, label, this](double acc, size_t x) {
                           if (label == labels(x))
                             return acc + distance(x, index);
                           return acc;
                         });
}

// Estimating the result of clustering. Caclulates the sum((Ai - Bi)/max(Ai,
// Bi))/n where Ai =SSC(i, label(i))/sizeOfCluster, Bi =SSC(i,
// label)/sizeOfCluster and label is the cluster nearest to the i-tuple that
// does not contain it.
void ClusteringNode::silhouette_shadow() {

  std::map<size_t, unsigned long> sizesOfClusters;
  std::set<size_t> setLabel(labels.begin(), labels.end());

  // Calculating size of clusters
  // If all clusters are of size 0 (every tuple is a noise, DBSCAN), exit
  int check = 0;
  for (auto l : setLabel) {

    sizesOfClusters[l] =
        std::accumulate(labels.begin(), labels.end(), static_cast<size_t>(0),
                        [l](size_t acc, size_t x) {
                          if (x == l)
                            return ++acc;
                          return acc;
                        });
    check *= sizesOfClusters[l];
  }
  if (0 == check) {

    silhouetteScore = -1;
    return;
  }

  double s = 0;
  // Iterating through tuples
  for (size_t i = 0; i < labels.n_cols; i++) {
    // Calculating Ai
    double a = SSC(i, labels(i)) / sizesOfClusters[labels[i]];
    // Calculating Bi
    double minNeighbour = std::numeric_limits<double>::infinity();
    for (auto l : setLabel) {

      if (l != labels[i]) {

        // If the sizeOfClusters is 0 (DBSCAN, noises), we will skip that label
        if (sizesOfClusters[l] == 0) {

          double tmp = SSC(i, labels(l)) / sizesOfClusters[l];
          if (tmp < minNeighbour && tmp > 0) {

            minNeighbour = tmp;
          }
        }
      }
    }

    s += (minNeighbour - a) / std::max(minNeighbour, a);
  }

  silhouetteScore = s / labels.n_cols;
}
