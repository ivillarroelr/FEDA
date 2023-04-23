#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../headers/SortingAlgorithms.h"
#include "../headers/SortingUtilities.h"

std::vector<int> arrayOfNumbers;

int main(int argc, char *argv[]) {
  
  SortingAlgorithms sort;
  SortingUtilities utils;
  unsigned int amountOfRandomNumbers = atoi(argv[1]);
  unsigned int distributionMax = atoi(argv[2]);
  unsigned int totalAmountOfFiles = atoi(argv[3]);
  std::ofstream outputFile("statistics/sorting_results.csv");
  outputFile << "Experiment,Dataset,Time(us)" << std::endl;
  
  /*
   * generates input files from arguments
   * increasing complexity depends on input from command line: amountOfRandomNumbers, distributionMax
   * TODO: add functionality for different characteristics (semi-sorted, partially-sorted)
   */
  utils.generateInputFilesForSortingAlgorithm(
      amountOfRandomNumbers, distributionMax, totalAmountOfFiles);

  /**
   * Iterates over directory for the input files and then populates the array 
   */
  std::filesystem::path input_dir_path =
      std::filesystem::current_path() / "input_files";

  for (const auto &inputFile :
       std::filesystem::directory_iterator(input_dir_path)) {

    if (inputFile.is_regular_file()) {

      std::ifstream file(inputFile.path());
      if (file.is_open()) {

        std::string line;
        
        while (std::getline(file, line)) {
          int number = std::stoi(line);
          arrayOfNumbers.push_back(number);
        }
        
        file.close();

        /**
         * Executes the sorting algorithms saving the execution time
         */
        std::string experiment = "Bubblesort";
        auto start = std::chrono::high_resolution_clock::now();
        sort.bubbleSort(arrayOfNumbers);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
                .count();

        std::filesystem::path inputFilePathAux = inputFile.path();
        utils.writeVectorToOutputFile(arrayOfNumbers,
                                      "output_for_" +
                                          inputFilePathAux.filename().string(),
                                      "output_files");
        // escribe en el archivo de estadisticas el tiempo de ejecucion
        outputFile << experiment << "," << inputFilePathAux.filename() << "," << duration
                   << std::endl;
      } else {
        std::cerr << "Error al abrir el archivo: " << inputFile.path() << '\n';
      }
    }
  }
  return 0;
}
