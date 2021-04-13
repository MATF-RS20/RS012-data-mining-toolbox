#include "PerceptronNode.hpp"

PerceptronNode::PerceptronNode(std::string name) : ClassificationNode(name) {}

void PerceptronNode::run() {

  // Checking if targetColumnName is selected
  if (!this->IsVariableSelected()) {
    std::cout << "Target variable not selected" << std::endl;
    DataTable dt = *InputDataTable();
    this->setOutDataTable(dt);
    return;
  }

  // Getting target column in form of arma::row
  targetColumn = TransformToArma();

  // Seting number of classes
  SetNumClasses(InputDataTable()->CategoricalValues()[targetColumnName].size());

  // Filtering target column from input
  DataTable dt = filter(targetColumnName);
  arma::mat data = dt.DataMatrix();

  // If there's not partition
  if (!dt.IsPartitioned()) {

    // Training the model on whole data
    data = trans(data);
    mlpack::perceptron::Perceptron<> perceptronClassifier(
        data, this->targetColumn, NumClasses());
    perceptronClassifier.Train(data, this->targetColumn, NumClasses());
    // perceptronClassifier.Train(data, this->targetColumn);

    // Getting and setting predictions
    arma::Row<size_t> predictions(this->targetColumn.size());
    perceptronClassifier.Classify(data, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;

    // Calculating precision and confusion matrix
    ClassificationNode::Precision(targetColumn, predictions);
    std::cout << GetPrecision() << std::endl;

    ClassificationNode::ConfusionMatrix(targetColumn, predictions);
    std::cout << GetConfusionMatrix() << std::endl;

    SetClassPredictions(predictions);

  } // If there is partition
  else {

    // Splitting data into testData, testTarget and trainData, trainTarget
    arma::mat testData(dt.TestSize(), data.n_cols);
    arma::mat trainData(data.n_rows - dt.TestSize(), data.n_cols);

    arma::Row<size_t> testTarget(dt.TestSize());
    arma::Row<size_t> trainTarget(data.n_rows - dt.TestSize());

    std::vector<bool> partition = dt.Partition();

    // Filling trainData, trainTarget and testData, testTarget
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

    // Training model on trainData and trainTarget
    trainData = trans(trainData);
    testData = trans(testData);
    mlpack::perceptron::Perceptron<> perceptronClassifier(
        trainData, trainTarget, NumClasses());
    perceptronClassifier.Train(trainData, trainTarget, NumClasses());
    // perceptronClassifier.Train(trainData, trainTarget);

    // Getting predictions from testData
    arma::Row<size_t> predictions(testTarget.size());
    perceptronClassifier.Classify(testData, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;

    // Calculating precision and confusion matrix from testTarget and above
    // calculated predictions
    ClassificationNode::Precision(testTarget, predictions);
    std::cout << GetPrecision() << std::endl;

    ClassificationNode::ConfusionMatrix(testTarget, predictions);
    std::cout << GetConfusionMatrix() << std::endl;

    // Getting predictions from whole data
    arma::Row<size_t> allPredictions;
    data = trans(data);
    perceptronClassifier.Classify(data, allPredictions);
    SetClassPredictions(allPredictions);
  }

  // Set output
  std::string result = GetPrecision();
  result += GetConfusionMatrix();
  setOutputMessage(result);

  DataTable dataTable = *InputDataTable();
  this->setOutDataTable(dataTable);
}
