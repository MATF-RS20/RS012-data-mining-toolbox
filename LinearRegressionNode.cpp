#include "LinearRegressionNode.hpp"

LinearRegressionNode::LinearRegressionNode(std::string name) : Node(name) {}

LinearRegressionNode::~LinearRegressionNode() = default;

// Checking if target is selected
bool LinearRegressionNode::IsTargetSelected() const {
  return !(targetColumnName == "");
}

// Getters
arma::Row<double> LinearRegressionNode::TargetPredictions() const {
  return targetPredictions;
}

arma::vec LinearRegressionNode::Params() const { return params; }

double LinearRegressionNode::RssScore() const { return rssScore; }

// Setters
void LinearRegressionNode::SetTargetPredictions(
    const arma::Row<double> predictions) {
  targetPredictions = predictions;
}
void LinearRegressionNode::SetRssScore(const double &score) {
  rssScore = score;
}

void LinearRegressionNode::SetParams(const arma::vec &parameters) {
  params = parameters;
}

void LinearRegressionNode::setTarget(std::string targetName) {
  targetColumnName = targetName;
}

void LinearRegressionNode::SetTargetColumn() {

  std::vector<std::string> columns = inputDataTable->ColumnNames();
  std::map<std::string, std::set<std::string>> map =
      inputDataTable->CategoricalValues();
  size_t index = 0;
  // Finding the column with targetColumnName
  for (auto &column : columns) {
    if (targetColumnName == column) {
      if (map.find(targetColumnName) != map.end()) {
        std::cout << "Greska! Izabrana kolona sa kategorickom vrednoscu!"
                  << std::endl;
        return;
      } else {
        auto matrix = inputDataTable->DataMatrix();
        targetColumn.set_size(matrix.n_rows);
        std::copy(matrix.begin_col(index), matrix.end_col(index),
                  targetColumn.begin());
      }
      break;
    }

    // If the column we just passed was categorical, we increase index by the
    // number of values of that column in order to skip binarized columns
    if (map.find(column) != map.end()) {

      index += map.at(column).size();
    } else {

      index++;
    }
  }
}

// Calculating rssScore (sum(trueValue(i) - predictedValue(i))^2/numberOfTuples)
void LinearRegressionNode::RSS(arma::Row<double> values,
                               arma::Row<double> predictions) {

  size_t nRows = values.size();
  double sum = 0;

  for (unsigned long i = 0; i < nRows; i++) {

    sum += (values[i] - predictions[i]) * (values[i] - predictions[i]);
  }

  SetRssScore(sum);
}

void LinearRegressionNode::run() {

  // Checking to see of targetColumnName is selected
  if (!this->IsTargetSelected()) {
    std::cout << "Target variable not selected" << std::endl;
    DataTable dt = *InputDataTable();
    this->setOutDataTable(dt);
    return;
  }

  // Select targetColumn
  this->SetTargetColumn();
  // Filter targetColumn from data
  DataTable dt = filter(targetColumnName);
  arma::mat data = dt.DataMatrix();

  // If not partitioned
  if (!dt.IsPartitioned()) {

    // Make a model from whole data
    data = trans(data);
    mlpack::regression::LinearRegression lr(data, targetColumn);

    // Get and set parameters of regressioin
    SetParams(lr.Parameters());
    std::cout << "Parameters: " << std::endl;
    std::cout << Params() << std::endl;

    // Calculate predictions and rrsScore
    arma::Row<double> predictions;
    lr.Predict(data, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;

    RSS(targetColumn, predictions);
    std::cout << RssScore() << std::endl;

    SetTargetPredictions(predictions);

  } // If there is partition
  else {

    // Split data into test and train data and predictions
    arma::mat testData(dt.TestSize(), data.n_cols);
    arma::mat trainData(data.n_rows - dt.TestSize(), data.n_cols);

    arma::Col<double> testTarget(dt.TestSize());
    arma::Col<double> trainTarget(data.n_rows - dt.TestSize());

    std::vector<bool> partition = dt.Partition();

    // Fill test and train sets
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

    trainData = trans(trainData);
    testData = trans(testData);

    // Make model from train data
    mlpack::regression::LinearRegression lr(trainData, trainTarget);

    // Get and set parameters
    SetParams(lr.Parameters());
    std::cout << "Parameters: " << std::endl;
    std::cout << Params() << std::endl;

    // Calculate predictions and rssScore from test data
    arma::Row<double> predictions;
    lr.Predict(testData, predictions);
    std::cout << "Predictions: " << std::endl;
    std::cout << predictions << std::endl;

    RSS(testTarget, predictions);
    std::cout << RssScore() << std::endl;

    // Calculate predictions and rssScore from whole data
    arma::Row<double> allPredictions;
    data = trans(data);
    lr.Predict(data, allPredictions);
    SetTargetPredictions(allPredictions);
    std::cout << TargetPredictions() << std::endl;
  }

  // Set output
  std::string result = "Paramteres:";
  arma::vec parameters = Params();
  for (unsigned long i = 0; i < parameters.size(); i++) {
    result += " ";
    result += std::to_string(parameters[i]);
  }
  result += "\n";
  result += "RSS: ";
  result += std::to_string(RssScore());
  result += "\n";
  setOutputMessage(result);

  DataTable dataTable = *InputDataTable();
  this->setOutDataTable(dataTable);
}
