#include "DBSCANNode.hpp"

#include <utility>

#include "mlpack/methods/dbscan/dbscan.hpp"

DBSCANNode::DBSCANNode(std::string name, double e, size_t mp)
    : ClusteringNode(std::move(name)), eps(e), minPoints(mp) {}

double DBSCANNode::Eps() { return eps; }

size_t DBSCANNode::MinPoints() { return minPoints; }

void DBSCANNode::SetEps(double e) { eps = e; }

void DBSCANNode::SetMinPoints(size_t mp) { minPoints = mp; }

void DBSCANNode::run() {

  mlpack::dbscan::DBSCAN<> model(eps, minPoints);
  model.Cluster(inputDataTable->DataMatrix(), labels, centroids);

  silhouette_shadow();

  std::cout << "~~~~~~" << std::endl;
  // std::cout << db.Labels() << std::endl;
}
