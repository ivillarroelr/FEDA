#include <algorithm>
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
std::vector<int> arrayOfNumbersBkp;
SortingAlgorithms sort;
SortingUtilities utils;
enum SortingExperiments { bubblesort, mergesort, quicksort, insertionsort, stlsort };
const std::string EXPERIMENT_OUTPUT = "statistics/results.csv";

void performExperiment(SortingExperiments experiment, std::vector<int> &array,
                       std::ofstream &outputFile,
                       std::filesystem::path inputFilePath) {
  switch (experiment) {
  case bubblesort: {
    auto start = std::chrono::high_resolution_clock::now();
    sort.bubbleSort(arrayOfNumbers);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    utils.writeVectorToOutputFile(arrayOfNumbers,
                                  "output_bubblesort_for_" +
                                      inputFilePath.filename().string(),
                                  "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "bubblesort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << ","<< arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case mergesort: {
    auto start = std::chrono::high_resolution_clock::now();
    sort.mergeSort(arrayOfNumbers, 0, arrayOfNumbers.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    utils.writeVectorToOutputFile(arrayOfNumbers,
                                  "output_mergesort_for_" +
                                      inputFilePath.filename().string(),
                                  "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "mergesort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << ","<< arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case quicksort: {
    auto start = std::chrono::high_resolution_clock::now();
    sort.quickSort(arrayOfNumbers, 0, arrayOfNumbers.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    utils.writeVectorToOutputFile(arrayOfNumbers,
                                  "output_quicksort_for_" +
                                      inputFilePath.filename().string(),
                                  "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "quicksort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << ","<< arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case insertionsort: {
    auto start = std::chrono::high_resolution_clock::now();
    sort.insertionSort(arrayOfNumbers);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    utils.writeVectorToOutputFile(arrayOfNumbers,
                                  "output_insertionsort_for_" +
                                      inputFilePath.filename().string(),
                                  "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "insertionsort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << ","<< arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case stlsort: {
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(arrayOfNumbers.begin(), arrayOfNumbers.end());
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    utils.writeVectorToOutputFile(arrayOfNumbers,
                                  "output_stlsort_for_" +
                                      inputFilePath.filename().string(),
                                  "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "stlsort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << ","<< arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  default: {
    std::cout << "not implemented yet" << std::endl;
    break;
  }
  }
  arrayOfNumbers = arrayOfNumbersBkp;
}

int main(int argc, char *argv[]) {
  std::ofstream outputFile(EXPERIMENT_OUTPUT);
  outputFile << "Experiment,Dataset,Entries,Time(us)" << std::endl;
  if (argc > 1) {
    unsigned int amountOfRandomNumbers = atoi(argv[1]);
    unsigned int distributionMax = atoi(argv[2]);
    unsigned int totalAmountOfFiles = atoi(argv[3]);
    /*
     * generates input files from arguments
     * increasing complexity depends on input from command line:
     * amountOfRandomNumbers, distributionMax
     * TODO: add functionality for different characteristics (semi-sorted,
     * partially-sorted)
     */
    utils.generateInputFilesForSortingAlgorithm(
        amountOfRandomNumbers, distributionMax, totalAmountOfFiles);
  }
  /**
   * Iterates over directory for the input files and then populates the array
   */
  std::filesystem::path input_dir_path =
      std::filesystem::current_path() / "input_files";

  int filecounter = 1;
  const auto totalFiles = std::distance(
      std::filesystem::recursive_directory_iterator(input_dir_path),
      std::filesystem::recursive_directory_iterator{});

  for (int i = 1; i <= totalFiles; i++) {
    std::string filename = "input_" + std::to_string(i) + ".txt";
    for (const auto &inputFile :
         std::filesystem::directory_iterator(input_dir_path)) {
      if ((inputFile.path().filename() == filename) &&
          inputFile.is_regular_file()) {

        int percentage = (filecounter * 100) / totalFiles;
        std::cout << "\r"
                  << "Working: " + std::to_string(percentage) + "%"
                  << std::flush;

        std::ifstream file(inputFile.path());
        if (file.is_open()) {

          std::string line;

          while (std::getline(file, line)) {
            int number = std::stoi(line);
            arrayOfNumbers.push_back(number);
          }
          arrayOfNumbersBkp = arrayOfNumbers;
          file.close();

          performExperiment(bubblesort, arrayOfNumbers, outputFile,
                            inputFile.path());
          performExperiment(insertionsort, arrayOfNumbers, outputFile,
                            inputFile.path());
          performExperiment(mergesort, arrayOfNumbers, outputFile,
                            inputFile.path());
          performExperiment(quicksort, arrayOfNumbers, outputFile,
                            inputFile.path());
          performExperiment(stlsort, arrayOfNumbers, outputFile,
                            inputFile.path());
        } else {
          std::cerr << "Error al abrir el archivo: " << inputFile.path()
                    << '\n';
        }
      }
    }
    filecounter++;
  }
  std::cout << std::endl;
  return 0;
}
