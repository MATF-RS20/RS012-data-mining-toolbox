#include "KMeansNode.hpp"

#include "mlpack/methods/kmeans/kmeans.hpp"

KMeansNode::KMeansNode(std::string name) : ClusteringNode(name), numberOfClusters(2),
                                           distance(distances::EuclideanDistance), maxNumberOfIterations(1000) {}
KMeansNode::KMeansNode(std::string name, size_t numCLus) : KMeansNode(name) { numberOfClusters = numCLus; }
KMeansNode::KMeansNode(std::string name, distances d) : KMeansNode(name) { distance = d; }
KMeansNode::KMeansNode(std::string name, size_t numCLus, size_t maxNumIter) : KMeansNode(name) { numberOfClusters = numCLus;
                                                                                                 maxNumberOfIterations = maxNumIter; }
KMeansNode::KMeansNode(std::string name, distances d, size_t maxNumIter) : KMeansNode(name) { distance = d;
                                                                                              maxNumberOfIterations = maxNumIter;}
KMeansNode::KMeansNode(std::string name, size_t numCLus, distances d, size_t maxNumIter) : ClusteringNode(name), numberOfClusters(numCLus),
                                                                                           distance(d), maxNumberOfIterations(maxNumIter) {}

size_t KMeansNode::NumberOfClusters() {

    return  numberOfClusters;
}

void KMeansNode::SetNumberOfClusters(size_t number) {

    numberOfClusters = number;
}

KMeansNode::distances KMeansNode::Distance() {

    return distance;
}

void KMeansNode::SetDistance(distances dist) {

    distance = dist;
}

size_t KMeansNode::MaxNumberOfIterations() {

    return  maxNumberOfIterations;
}

void KMeansNode::SetMaxNumberOfIterations(size_t number) {

    maxNumberOfIterations = number;
}

void KMeansNode::run() {

    if(distances::EuclideanDistance == distance) {

        mlpack::kmeans::KMeans<mlpack::metric::EuclideanDistance> model(maxNumberOfIterations);
        model.Cluster(trans(inputDataTable->DataMatrix()), numberOfClusters, labels, centroids, false, false);
    } else if(distances::ManhattanDistance == distance) {

        mlpack::kmeans::KMeans<mlpack::metric::ManhattanDistance> model(maxNumberOfIterations);
        model.Cluster(trans(inputDataTable->DataMatrix()), numberOfClusters, labels, centroids, false, false);
    } else if(distances::SquaredEuclideanDistance == distance) {

        mlpack::kmeans::KMeans<mlpack::metric::SquaredEuclideanDistance> model(maxNumberOfIterations);
        model.Cluster(trans(inputDataTable->DataMatrix()), numberOfClusters, labels, centroids, false, false);
    } else if(distances::ChebyshevDistance == distance) {

        mlpack::kmeans::KMeans<mlpack::metric::ChebyshevDistance> model(maxNumberOfIterations);
        model.Cluster(trans(inputDataTable->DataMatrix()), numberOfClusters, labels, centroids, false, false);
    }

    centroids = trans(centroids);

    DataTable dt(*InputDataTable());
    setOutDataTable(dt);

    silhouette_shadow();
}
