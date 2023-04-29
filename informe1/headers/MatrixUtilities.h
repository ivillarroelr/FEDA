#include <string>
#include <vector>

enum MatrixType { square, rectangle };

class MatrixUtilities {
public:
  void generateMatrixFilesForProductAlgorithms(
      MatrixType matrixType, int matrixAMaxWitdh, int matrixAMaxHeigth,
      int matrixBMaxWitdh, int matrixBMaxHeigth, int totalSetOfFiles,
      int distributionMax);
  void writeMatrixToOutputFile(std::vector<std::vector<int>> array,
                               const std::string &filename,
                               const std::string &directory);
};