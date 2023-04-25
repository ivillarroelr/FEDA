#include <vector>
#include <string>

class MatrixUtilities {
  public:
    void generateMatrixFilesForProductAlgorithms(int matrixAMaxWitdh, int matrixAMaxHeigth,
                                                 int matrixBMaxWitdh, int matrixBMaxHeigth,
                                                 int totalSetOfFiles, int distributionMax);
    void writeMatrixToOutputFile(std::vector<std::vector<int>> array,
                                 const std::string& filename,
                                 const std::string& directory);
};