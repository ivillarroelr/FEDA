#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "../headers/MatrixUtilities.h"

void MatrixUtilities::generateMatrixFilesForProductAlgorithms(
    int matrixAMaxWitdh, int matrixAMaxHeigth, int matrixBMaxWitdh,
    int matrixBMaxHeigth, int totalSetOfFiles, int distributionMax) {
  for (int quantity = 1; quantity <= totalSetOfFiles+1; quantity++) {
    std::string fileNameA =
        "input_files/matrix_input_a_" + std::to_string(quantity) + ".txt";
    std::string fileNameB =
        "input_files/matrix_input_b_" + std::to_string(quantity) + ".txt";
    int A[matrixAMaxWitdh][matrixAMaxHeigth];
    int B[matrixBMaxWitdh][matrixBMaxHeigth];
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(1, distributionMax);
    std::vector<int> array;
    float increasingComplexityAW =
        (matrixAMaxWitdh / totalSetOfFiles) * quantity;
    float increasingComplexityAH =
        (matrixAMaxHeigth / totalSetOfFiles) * quantity;
    float increasingComplexityBW =
        (matrixBMaxWitdh / totalSetOfFiles) * quantity;
    float increasingComplexityBH =
        (matrixBMaxHeigth / totalSetOfFiles) * quantity;

    for (int i = 0; i < increasingComplexityAW; i++) {
      for (int j = 0; j < increasingComplexityAH; j++) {
        A[i][j] = distribution(generator);
      }
    }
    for (int i = 0; i < increasingComplexityBW; i++) {
      for (int j = 0; j < increasingComplexityBH; j++) {
        B[i][j] = distribution(generator);
      }
    }
    std::ofstream outputFileA(fileNameA);
    std::ofstream outputFileB(fileNameB);
    if (outputFileA.is_open() && outputFileB.is_open()) {
      for (int i = 0; i < increasingComplexityAW; i++) {
        for (int j = 0; j < increasingComplexityAH; j++) {
          outputFileA << A[i][j] << " ";
        }
        outputFileA << std::endl;
      }
      for (int i = 0; i < increasingComplexityBW; i++) {
        for (int j = 0; j < increasingComplexityBH; j++) {
          outputFileB << B[i][j] << " ";
        }
        outputFileB << std::endl;
      }
      outputFileA.close();
      outputFileB.close();
    } else {
      std::cout << "Error while creating the matrix input files" << std::endl;
    }
  }
}