#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../headers/MatrixAlgorithms.h"
#include "../headers/MatrixUtilities.h"
#include "../headers/SortingAlgorithms.h"
#include "../headers/SortingUtilities.h"

std::vector<int> arrayOfNumbers;
std::vector<int> arrayOfNumbersBkp;
SortingAlgorithms sort;
SortingUtilities sUtils;
MatrixAlgorithms matrix;
MatrixUtilities mUtils;

enum SortingExperiments {
  bubblesort,
  mergesort,
  quicksort,
  insertionsort,
  stlsort
};

enum MatrixExperiments { matrixproduct, matrixproductoptimized, strassen };

const std::string EXPERIMENT_OUTPUT = "statistics/results.csv";

void performSortingExperiment(SortingExperiments experiment,
                              std::vector<int> &array,
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

    sUtils.writeVectorToOutputFile(arrayOfNumbers,
                                   "output_bubblesort_for_" +
                                       inputFilePath.filename().string(),
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "bubblesort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << "," << arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case mergesort: {
    auto start = std::chrono::high_resolution_clock::now();
    sort.mergeSort(arrayOfNumbers, 0, arrayOfNumbers.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    sUtils.writeVectorToOutputFile(arrayOfNumbers,
                                   "output_mergesort_for_" +
                                       inputFilePath.filename().string(),
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "mergesort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << "," << arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case quicksort: {
    auto start = std::chrono::high_resolution_clock::now();
    sort.quickSort(arrayOfNumbers, 0, arrayOfNumbers.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    sUtils.writeVectorToOutputFile(arrayOfNumbers,
                                   "output_quicksort_for_" +
                                       inputFilePath.filename().string(),
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "quicksort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << "," << arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case insertionsort: {
    auto start = std::chrono::high_resolution_clock::now();
    sort.insertionSort(arrayOfNumbers);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    sUtils.writeVectorToOutputFile(arrayOfNumbers,
                                   "output_insertionsort_for_" +
                                       inputFilePath.filename().string(),
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "insertionsort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << "," << arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  case stlsort: {
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(arrayOfNumbers.begin(), arrayOfNumbers.end());
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    sUtils.writeVectorToOutputFile(arrayOfNumbers,
                                   "output_stlsort_for_" +
                                       inputFilePath.filename().string(),
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "stlsort"
               << ","
               << inputFilePath.filename().string().substr(
                      0, inputFilePath.filename().string().length())
               << "," << arrayOfNumbers.size() << "," << duration << std::endl;
    break;
  }
  default: {
    std::cout << "not implemented yet" << std::endl;
    break;
  }
  }
  arrayOfNumbers = arrayOfNumbersBkp;
}

void performMatrixExperiment(MatrixExperiments experiment,
                             std::ofstream &outputFile, int set, int m,
                             std::vector<std::vector<int>> matrixA,
                             std::vector<std::vector<int>> matrixB) {
  switch (experiment) {
  case matrixproduct: {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> resultMatrix =
        matrix.standard_mm(matrixA, matrixB);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    mUtils.writeMatrixToOutputFile(resultMatrix,
                                   "output_matrix_for_" + std::to_string(set),
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "matrixproduct"
               << "," << set << "," << m << "," << duration << std::endl;
    break;
  }
  default: {
  }
  }
}

int main(int argc, char *argv[]) {
  std::ofstream outputFile(EXPERIMENT_OUTPUT);
  outputFile << "Experiment,Dataset,Entries,Time(us)" << std::endl;
  if (argc > 1) {
    unsigned int amountOfRandomNumbers = atoi(argv[1]);
    unsigned int distributionMax = atoi(argv[2]);
    unsigned int totalAmountOfFiles = atoi(argv[3]);
    unsigned int matrixAMaxWidth = atoi(argv[4]);
    unsigned int matrixAMaxHeight = atoi(argv[5]);
    unsigned int matrixBMaxWidth = atoi(argv[6]);
    unsigned int matrixBMaxHeight = atoi(argv[7]);
    unsigned int matrixTotalSetOfFiles = atoi(argv[8]);
    unsigned int matrixDistributionMax = atoi(argv[9]);

    /* TODO: refactor comments
     * generates input files from arguments
     * increasing complexity depends on input from command line:
     * amountOfRandomNumbers, distributionMax
     * TODO: add functionality for different characteristics (semi-sorted,
     * partially-sorted)
     */
    sUtils.generateInputFilesForSortingAlgorithm(
        amountOfRandomNumbers, distributionMax, totalAmountOfFiles);

    mUtils.generateMatrixFilesForProductAlgorithms(
        matrixAMaxWidth, matrixAMaxHeight, matrixBMaxWidth, matrixBMaxHeight,
        matrixTotalSetOfFiles, matrixDistributionMax);
  }

  /**
   * Iterates over directory for the input files and then populates the array
   */
  std::filesystem::path input_dir_path_sorting =
      std::filesystem::current_path() / "input_files/sorting";

  std::filesystem::path input_dir_path_matrix =
      std::filesystem::current_path() / "input_files/matrix";

  int filecounterSorting = 1;
  const auto totalFilesSorting = std::distance(
      std::filesystem::recursive_directory_iterator(input_dir_path_sorting),
      std::filesystem::recursive_directory_iterator{});

  int filecounterMatrix = 1;
  const auto totalFilesMatrix = std::distance(
      std::filesystem::recursive_directory_iterator(input_dir_path_matrix),
      std::filesystem::recursive_directory_iterator{});

  for (int j = 1; j <= filecounterMatrix / 2; j++) {
    std::string filenameA = "matrix_input_a" + std::to_string(j) + ".txt";
    std::string filenameB = "matrix_input_b" + std::to_string(j) + ".txt";
    std::vector<std::vector<int>> auxMatrixA;
    std::vector<std::vector<int>> auxMatrixB;

    int percentage = (filecounterMatrix * 100) / totalFilesMatrix;
    std::cout << "\r"
              << "Matrix Working: " + std::to_string(percentage) + "%"
              << std::flush;

    for (const auto &inputFile :
         std::filesystem::directory_iterator(input_dir_path_sorting)) {
      if ((inputFile.path().filename() == filenameA) &&
          inputFile.is_regular_file()) {

        std::ifstream file(inputFile.path());
        if (file.is_open()) {

          std::string line;

          while (std::getline(file, line)) {
            std::vector<int> aux;
            std::stringstream ss(line);
            int num;
            while (ss >> num) {
              aux.push_back(num);
            }
            auxMatrixA.push_back(aux);
          }

          file.close();
            }
        } else if ((inputFile.path().filename() == filenameB) &&
                   inputFile.is_regular_file()) {

          std::ifstream file(inputFile.path());
          if (file.is_open()) {

            std::string line;

            while (std::getline(file, line)) {
              std::vector<int> aux;
              std::stringstream ss(line);
              int num;
              while (ss >> num) {
                aux.push_back(num);
              }
              auxMatrixB.push_back(aux);
            }

            file.close();

          } else {
            std::cerr << "Error al abrir el archivo: " << inputFile.path()
                      << '\n';
          }
        }
      performMatrixExperiment(matrixproduct, outputFile, j,
                              auxMatrixA[0].size(), auxMatrixA, auxMatrixB);
      filecounterSorting++;
    }
  }
    for (int i = 1; i <= totalFilesSorting; i++) {
      std::string filename = "input_" + std::to_string(i) + ".txt";
      for (const auto &inputFile :
           std::filesystem::directory_iterator(input_dir_path_sorting)) {
        if ((inputFile.path().filename() == filename) &&
            inputFile.is_regular_file()) {

          int percentage = (filecounterSorting * 100) / totalFilesSorting;
          std::cout << "\r"
                    << "Sorting Working: " + std::to_string(percentage) + "%"
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

            performSortingExperiment(bubblesort, arrayOfNumbers, outputFile,
                                     inputFile.path());
            performSortingExperiment(insertionsort, arrayOfNumbers, outputFile,
                                     inputFile.path());
            performSortingExperiment(mergesort, arrayOfNumbers, outputFile,
                                     inputFile.path());
            performSortingExperiment(quicksort, arrayOfNumbers, outputFile,
                                     inputFile.path());
            performSortingExperiment(stlsort, arrayOfNumbers, outputFile,
                                     inputFile.path());
          } else {
            std::cerr << "Error al abrir el archivo: " << inputFile.path()
                      << '\n';
          }
        }
      }
      filecounterSorting++;
    }
    std::cout << std::endl;
    return 0;
    }
