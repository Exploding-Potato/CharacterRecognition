std::vector<short> *MNISTReadLabels(std::string filePath, int maxExamples = INT32_MAX);

std::vector<arma::Row<short>> *MNISTTransformLabels(std::vector<short>, int labels);

std::vector<arma::Mat<short>> *MNISTReadImages(std::string filePath, int maxExamples = INT32_MAX);