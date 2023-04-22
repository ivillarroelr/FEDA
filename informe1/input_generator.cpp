#include <iostream>
#include <fstream>
#include <vector>
#include <random>

/**
 * Generates files with random numbers unsorted
 * input <unsigned int> amountOfRandomNumbers: amount of numbers to be present in the file
 * input <unsigned int> distributionMax: upper limit for uniform integer distribution
 * input <unsigned int> totalAmountOfFiles: Quantity of files to be generated
 * output void
 */
void generateInputFilesForSortingAlgorithm(unsigned int amountOfRandomNumbers, unsigned int distributionMax, unsigned int totalAmountOfFiles){
  for(int quantity = 1; quantity <= totalAmountOfFiles; quantity++){
    std::string fileName = "input_" + std::to_string(quantity) + ".txt";
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(1, distributionMax);
    std::vector<int> array;
    for (int i = 0; i < amountOfRandomNumbers; i++) {
      array.push_back(distribution(generator));
    }
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
      for (int i = 0; i < array.size(); i++) {
        outputFile << array[i] << "\n";
      }
      outputFile.close();
    } else {
      std::cout << "Error while creating the file: "<< fileName << std::endl;
    }
  }
}

int main(int argc, char *argv[]) {
  unsigned int amountOfRandomNumbers = atoi(argv[1]);
  unsigned int distributionMax = atoi(argv[2]); 
  unsigned int totalAmountOfFiles = atoi(argv[3]);
  generateInputFilesForSortingAlgorithm(amountOfRandomNumbers, distributionMax, totalAmountOfFiles);
  return 0;
}
