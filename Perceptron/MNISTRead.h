arma::Row<short> *MNISTReadLabels(std::string filePath, int32_t maxExamples = INT32_MAX);

std::vector<arma::Mat<short>> *MNISTReadImages(std::string filePath, int32_t maxExamples = INT32_MAX);