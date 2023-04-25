#include "../headers/SortingUtilities.h"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <filesystem>
#include <sstream>

/**
 * Generates files with random numbers unsorted
 * input <unsigned int> amountOfRandomNumbers: amount of numbers to be present
 * in the file input <unsigned int> distributionMax: upper limit for uniform
 * integer distribution input <unsigned int> totalAmountOfFiles: Quantity of
 * files to be generated output void
 */
void SortingUtilities::generateInputFilesForSortingAlgorithm(
    unsigned int amountOfRandomNumbers, unsigned int distributionMax,
    unsigned int totalAmountOfFiles) {
  for (int quantity = 1; quantity <= totalAmountOfFiles; quantity++) {

    std::string fileName =
        "input_files/sorting/input_" + std::to_string(quantity) + ".txt";
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(1, distributionMax);
    std::vector<int> array;
    float increasingLength = (amountOfRandomNumbers/totalAmountOfFiles)*quantity;
    for (int i = 0; i < increasingLength; i++) {
      array.push_back(distribution(generator));
    }
    std::ofstream outputFile(fileName);
    if (outputFile.is_open()) {
      for (int i = 0; i < array.size(); i++) {
        outputFile << array[i] << "\n";
      }
      outputFile.close();
    } else {
      std::cout << "Error while creating the file: " << fileName << std::endl;
    }
  }
}

/**
 * Parses the numbers from an input file in the format n1 "\n" n2 "\n" ... n to
 * a vector input const std::string &filename: memory reference to the filename
 * input std::vector<int> &array: memory reference to the array that will hold
 * the incoming numbers output void
 */
void SortingUtilities::parseNumbersFromFile(const std::string &filename,
                                            std::vector<int> &array) {
  std::ifstream inputFile(filename);
  if (inputFile.is_open()) {
    int number;
    while (inputFile >> number) {
      array.push_back(number);
    }
    inputFile.close();
  } else {
    std::cerr << "Unable to open the file: " << filename << std::endl;
  }
}

void SortingUtilities::writeVectorToOutputFile(std::vector<int> array,const std::string& filename, const std::string& directory) {
  std::ofstream outFile(directory+"/"+filename);
  if (outFile.is_open()) {
    for (int val : array) {
      outFile << val << "\n";
    }
    outFile.close();
  }
}
