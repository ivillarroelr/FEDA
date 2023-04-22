#include <iostream>
#include <fstream>
#include <vector>
#include <random>

/**
 * Generates a file with random numbers unsorted
 * input <unsigned int> amountOfRandomNumbers: amount of numbers to be present in the file
 * input <unsigned int> distributionMax: upper limit for uniform integer distribution
 * input <std::string> fileName: name of the output file
 * output void
 */
void generateInputFileForSortingAlgorithm(unsigned int amountOfRandomNumbers, unsigned int distributionMax, std::string fileName){
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
    std::cout << "Error while creating the file" << std::endl;
  }
}

/**
 * OOB - out of the box input file generator for sorting algorithms
 */
int main(int argc, char *argv[]) {
  unsigned int amountOfRandomNumbers = atoi(argv[1]);
  unsigned int distributionMax = atoi(argv[2]); 
  std::string fileName = argv[3];
  generateInputFileForSortingAlgorithm(amountOfRandomNumbers, distributionMax, fileName);
  return 0;
}
