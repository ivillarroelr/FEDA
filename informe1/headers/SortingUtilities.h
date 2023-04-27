#include <string>
#include <vector>

enum TypeOfInputForSortingFiles { randomized, partial, semi, backsorted };

class SortingUtilities {
public:
  void generateInputFilesForSortingAlgorithm(
      unsigned int amountOfRandomNumbers, unsigned int distributionMax,
      unsigned int totalAmountOfFiles, TypeOfInputForSortingFiles typeOfInput);
  void parseNumbersFromFile(const std::string &filename,
                            std::vector<int> &array);
  void fileToVector(std::vector<int> &array, std::string &directory_path);
  void writeVectorToOutputFile(std::vector<int> array,
                               const std::string &filename,
                               const std::string &directory);
};