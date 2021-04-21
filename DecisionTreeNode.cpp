#include "DecisionTreeNode.hpp"

#include <utility>

DecisionTreeNode::DecisionTreeNode(std::string name)
    : ClassificationNode(std::move(name)) {
  maximumDepth = 0;
  minimumLeafSize = 10;
}

// Getters
int DecisionTreeNode::MaximumDepth() const { return maximumDepth; }
int DecisionTreeNode::MinimumLeafSize() const { return minimumLeafSize; }

// Setters
void DecisionTreeNode::SetMaximumDepth(int depth) { maximumDepth = depth; }
void DecisionTreeNode::SetMinimumLeafSize(int size) { minimumLeafSize = size; }

void DecisionTreeNode::run() {

  // Checking if target is selected
  if (!this->IsVariableSelected()) {
    std::cout << "Target variable not selected" << std::endl;
    DataTable dt = *InputDataTable();
    this->setOutDataTable(dt);
    return;
  }

  // Getting target column
  targetColumn = TransformToArma();

  // Getting the number of classes
  SetNumClasses(InputDataTable()->CategoricalValues()[targetColumnName].size());

  // Filtering target from input
  DataTable dt = filter(targetColumnName);
  arma::mat data = dt.DataMatrix();

  // If there's no partition
  if (!dt.IsPartitioned()) {

    // Train the model on whole data
    data = trans(data);
    mlpack::tree::DecisionTree<> treeClassifier;
    treeClassifier.Train(data, this->targetColumn, NumClasses());

    // Classify data/get predictions
    arma::Row<size_t> predictions;
    treeClassifier.Classify(data, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;

    // Calculate precision
    ClassificationNode::Precision(targetColumn, predictions);
    std::cout << GetPrecision() << std::endl;

    // Calculate precision matrix
    ClassificationNode::ConfusionMatrix(targetColumn, predictions);
    std::cout << GetConfusionMatrix() << std::endl;

    SetClassPredictions(predictions);
  } // If there is partition
  else {

    // Split data and predictions into testData, testTarget and trainData,
    // trainTarget
    arma::mat testData(dt.TestSize(), data.n_cols);
    arma::mat trainData(data.n_rows - dt.TestSize(), data.n_cols);

    arma::Row<size_t> testTarget(dt.TestSize());
    arma::Row<size_t> trainTarget(data.n_rows - dt.TestSize());

    std::vector<bool> partition = dt.Partition();

    unsigned long train_index = 0;
    unsigned long test_index = 0;
    for (unsigned long i = 0; i < data.n_rows; i++) {
      if (partition[i]) {
        testTarget[test_index] = targetColumn[i];
        for (unsigned long j = 0; j < data.n_cols; j++) {
          testData(test_index, j) = data(i, j);
        }
        test_index++;
      } else {
        trainTarget[train_index] = targetColumn[i];
        for (unsigned long j = 0; j < data.n_cols; j++) {
          trainData(train_index, j) = data(i, j);
        }
        train_index++;
      }
    }

    // Train the model on trainData and trainTarget
    trainData = trans(trainData);
    testData = trans(testData);
    mlpack::tree::DecisionTree<> treeClassifier;
    treeClassifier.Train(trainData, trainTarget, NumClasses());

    // Calculate predictions from testData
    arma::Row<size_t> predictions;
    treeClassifier.Classify(testData, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;

    // Calculate precision and confusion matrix from testTarget and above
    // calculated predictions
    ClassificationNode::Precision(testTarget, predictions);
    std::cout << GetPrecision() << std::endl;

    ClassificationNode::ConfusionMatrix(testTarget, predictions);
    std::cout << GetConfusionMatrix() << std::endl;

    // Calculate predictions and confusion matrix on whole data
    arma::Row<size_t> allPredictions;
    data = trans(data);
    treeClassifier.Classify(data, allPredictions);
    SetClassPredictions(allPredictions);
    std::cout << ClassPredictions() << std::endl;
  }

  // Get the output
  std::string result = GetPrecision();
  result += GetConfusionMatrix();
  setOutputMessage(result);

  DataTable dataTable = *InputDataTable();
  this->setOutDataTable(dataTable);
}
