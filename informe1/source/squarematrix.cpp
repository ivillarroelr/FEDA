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

MatrixAlgorithms matrix;
MatrixUtilities mUtils;

enum MatrixExperiments { matrixproduct, matrixproductoptimized, strassen };

const std::string MATRIX_EXPERIMENT_OUTPUT = "statistics/matrix_results.csv";

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
                                   "output_matrixproduct_square_for_" +
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
                                   "output_matrixproductoptimized_square_for_" +
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
        resultMatrix, "output_strassen_square_for_" + std::to_string(set) + ".txt",
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

int main(int argc, char *argv[]) {
  std::ofstream matrixOutputFile(MATRIX_EXPERIMENT_OUTPUT, std::ios::app);
  matrixOutputFile << "Experiment,Dataset,m,Time(us)" << std::endl;
  if (argc > 1) {
    unsigned int matrixAMaxWidth = atoi(argv[1]);
    unsigned int matrixAMaxHeight = atoi(argv[2]);
    unsigned int matrixBMaxWidth = atoi(argv[3]);
    unsigned int matrixBMaxHeight = atoi(argv[4]);
    unsigned int matrixTotalSetOfFiles = atoi(argv[5]);
    unsigned int matrixDistributionMax = atoi(argv[6]);

    /*
     * generates input files from arguments
     * increasing complexity depends on input from command line:
     * amountOfRandomNumbers, distributionMax
     */
    mUtils.generateMatrixFilesForProductAlgorithms(square,
        matrixAMaxWidth, matrixAMaxHeight, matrixBMaxWidth, matrixBMaxHeight,
        matrixTotalSetOfFiles, matrixDistributionMax);
  }

  /**
   * Iterates over directory for the input files and then populates the array
   */
  std::filesystem::path input_dir_path_matrix =
      std::filesystem::current_path() / "input_files/matrix/square";

  int filecounterMatrix = 1;
  const auto totalFilesMatrix = std::distance(
      std::filesystem::recursive_directory_iterator(input_dir_path_matrix),
      std::filesystem::recursive_directory_iterator{});

  for (int j = 1; j <= totalFilesMatrix; j++) {
    std::string filenameA = "matrix_square_input_a_" + std::to_string(j) + ".txt";
    std::string filenameB = "matrix_square_input_b_" + std::to_string(j) + ".txt";
    std::vector<std::vector<int>> auxMatrixA;
    std::vector<std::vector<int>> auxMatrixB;

    int percentage = (filecounterMatrix * 100) / totalFilesMatrix;
    std::cout << "\r"
              << "Square Matrix Working: " + std::to_string(percentage) + "%"
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
