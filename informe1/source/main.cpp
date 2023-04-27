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

const std::string SORTING_EXPERIMENT_OUTPUT = "statistics/sorting_results.csv";
const std::string MATRIX_EXPERIMENT_OUTPUT = "statistics/matrix_results.csv";

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
                                   "output_matrixproduct_for_" +
                                       std::to_string(set) + ".txt",
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "matrixproduct"
               << "," << set << "," << m << "," << duration << std::endl;
    break;
  }
  case matrixproductoptimized: {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> resultMatrix =
        matrix.transpose_mm(matrixA, matrixB);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    mUtils.writeMatrixToOutputFile(resultMatrix,
                                   "output_matrixproductoptimized_for_" +
                                       std::to_string(set) + ".txt",
                                   "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "matrixproductoptimized"
               << "," << set << "," << m << "," << duration << std::endl;
    break;
  }
  case strassen: {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> resultMatrix =
        matrix.strassen(matrixA, matrixB);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
            .count();

    mUtils.writeMatrixToOutputFile(
        resultMatrix, "output_strassen_for_" + std::to_string(set) + ".txt",
        "output_files");
    // escribe en el archivo de estadisticas el tiempo de ejecucion
    outputFile << "strassen"
               << "," << set << "," << m << "," << duration << std::endl;
    break;
  }
  default: {
    std::cout << "not implemented yet" << std::endl;
    break;
  }
  }
}

void populateArrayAndExecuteExperiments(std::filesystem::path dir,
                                        int &counter,
                                        long totalFiles,
                                        TypeOfInputForSortingFiles type,
                                        std::ofstream &sortingOutputFile) {
  for (int i = 1; i <= totalFiles; i++) {
    std::string filename;
    switch (type) {
    case randomized: {
      filename = "input_randomized_" + std::to_string(i) + ".txt";
      break;
    }
    case partial: {
      filename = "input_partial_" + std::to_string(i) + ".txt";
      break;
    }
    case semi: {
      filename = "input_semi_" + std::to_string(i) + ".txt";
      break;
    }
    case backsorted: {
      filename = "input_backsorted_" + std::to_string(i) + ".txt";
      break;
    }
    default: {
      filename = "input_randomized_" + std::to_string(i) + ".txt";
      break;
    }
    }
    for (const auto &inputFile : std::filesystem::directory_iterator(dir)) {
      if ((inputFile.path().filename() == filename) &&
          inputFile.is_regular_file()) {

        std::ifstream file(inputFile.path());
        if (file.is_open()) {

          std::string line;

          while (std::getline(file, line)) {
            int number = std::stoi(line);
            arrayOfNumbers.push_back(number);
          }
          arrayOfNumbersBkp = arrayOfNumbers;
          file.close();

          performSortingExperiment(bubblesort, arrayOfNumbers,
                                   sortingOutputFile, inputFile.path());
          performSortingExperiment(insertionsort, arrayOfNumbers,
                                   sortingOutputFile, inputFile.path());
          performSortingExperiment(mergesort, arrayOfNumbers, sortingOutputFile,
                                   inputFile.path());
          performSortingExperiment(quicksort, arrayOfNumbers, sortingOutputFile,
                                   inputFile.path());
          performSortingExperiment(stlsort, arrayOfNumbers, sortingOutputFile,
                                   inputFile.path());
        } else {
          std::cerr << "Error al abrir el archivo: " << inputFile.path()
                    << '\n';
        }
      }
    }
    counter++;
  }
}

int main(int argc, char *argv[]) {
  std::ofstream sortingOutputFile(SORTING_EXPERIMENT_OUTPUT);
  sortingOutputFile << "Experiment,Dataset,Entries,Time(us)" << std::endl;
  std::ofstream matrixOutputFile(MATRIX_EXPERIMENT_OUTPUT);
  matrixOutputFile << "Experiment,Dataset,m,Time(us)" << std::endl;
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

    /*
     * generates input files from arguments
     * increasing complexity depends on input from command line:
     * amountOfRandomNumbers, distributionMax
     */
    sUtils.generateInputFilesForSortingAlgorithm(
        amountOfRandomNumbers, distributionMax, totalAmountOfFiles, randomized);

    sUtils.generateInputFilesForSortingAlgorithm(
        amountOfRandomNumbers, distributionMax, totalAmountOfFiles, partial);

    sUtils.generateInputFilesForSortingAlgorithm(
        amountOfRandomNumbers, distributionMax, totalAmountOfFiles, semi);

    sUtils.generateInputFilesForSortingAlgorithm(
        amountOfRandomNumbers, distributionMax, totalAmountOfFiles, backsorted);

    mUtils.generateMatrixFilesForProductAlgorithms(
        matrixAMaxWidth, matrixAMaxHeight, matrixBMaxWidth, matrixBMaxHeight,
        matrixTotalSetOfFiles, matrixDistributionMax);
  }

  /**
   * Iterates over directory for the input files and then populates the array
   */
  std::filesystem::path input_dir_path_sorting_randomized =
      std::filesystem::current_path() / "input_files/sorting/randomized";

  std::filesystem::path input_dir_path_sorting_partial =
      std::filesystem::current_path() / "input_files/sorting/partial";

  std::filesystem::path input_dir_path_sorting_semi =
      std::filesystem::current_path() / "input_files/sorting/semi";

  std::filesystem::path input_dir_path_sorting_backsorted =
      std::filesystem::current_path() / "input_files/sorting/backsorted";

  std::filesystem::path input_dir_path_matrix =
      std::filesystem::current_path() / "input_files/matrix";

  int filecounterSortingRandomized = 1;
  const auto totalFilesSortingRandomized =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_randomized),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
  input_dir_path_sorting_randomized,
  filecounterSortingRandomized,
  totalFilesSortingRandomized,
  randomized,
  sortingOutputFile);

  int filecounterSortingPartial = 1;
  const auto totalFilesSortingPartial =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_partial),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
      input_dir_path_sorting_partial,
      filecounterSortingPartial,
      totalFilesSortingPartial,
  partial,
  sortingOutputFile);

  int filecounterSortingSemi = 1;
  const auto totalFilesSortingSemi =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_semi),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
  input_dir_path_sorting_semi,
  filecounterSortingSemi,
  totalFilesSortingSemi,
  semi,
  sortingOutputFile);

  int filecounterSortingBacksorted = 1;
  const auto totalFilesSortingBacksorted =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_backsorted),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
  input_dir_path_sorting_backsorted,
  filecounterSortingBacksorted,
  totalFilesSortingBacksorted,
  backsorted,
  sortingOutputFile);

  int filecounterMatrix = 1;
  const auto totalFilesMatrix = std::distance(
      std::filesystem::recursive_directory_iterator(input_dir_path_matrix),
      std::filesystem::recursive_directory_iterator{});


  for (int j = 1; j <= totalFilesMatrix; j++) {
    std::string filenameA = "matrix_input_a_" + std::to_string(j) + ".txt";
    std::string filenameB = "matrix_input_b_" + std::to_string(j) + ".txt";
    std::vector<std::vector<int>> auxMatrixA;
    std::vector<std::vector<int>> auxMatrixB;

    int percentage = (filecounterMatrix * 100) / totalFilesMatrix;
    std::cout << "\r"
              << "Matrix Working: " + std::to_string(percentage) + "%"
              << std::flush;

    try {
      for (const auto &inputFile :
           std::filesystem::directory_iterator(input_dir_path_matrix)) {
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
        }
        if ((inputFile.path().filename() == filenameB) &&
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
      }
    } catch (const std::exception &e) {
      std::cout << "An exception occurred: " << e.what() << std::endl;
    }
    if (auxMatrixA.size() > 0 && auxMatrixB.size() > 0) {
      performMatrixExperiment(matrixproduct, matrixOutputFile, j,
                              auxMatrixA[0].size(), auxMatrixA, auxMatrixB);
      performMatrixExperiment(matrixproductoptimized, matrixOutputFile, j,
                              auxMatrixA[0].size(), auxMatrixA, auxMatrixB);
      performMatrixExperiment(strassen, matrixOutputFile, j,
                              auxMatrixA[0].size(), auxMatrixA, auxMatrixB);
    }
    filecounterMatrix++;
  }
  std::cout << std::endl;
  return 0;
}
