#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "../headers/MatrixUtilities.h"

void MatrixUtilities::generateMatrixFilesForProductAlgorithms(
    MatrixType matrixType, int matrixAMaxWitdh, int matrixAMaxHeight,
    int matrixBMaxWitdh, int matrixBMaxHeight, int totalSetOfFiles,
    int distributionMax) {
  for (int quantity = 0; quantity < totalSetOfFiles; quantity++) {
    std::string fileNameA, fileNameB;
    switch (matrixType) {
    case square: {
      fileNameA = "input_files/matrix/square/matrix_square_input_a_" +
                  std::to_string(quantity + 1) + ".txt";
      fileNameB = "input_files/matrix/square/matrix_square_input_b_" +
                  std::to_string(quantity + 1) + ".txt";
      break;
    }
    case rectangle: {
      fileNameA = "input_files/matrix/rectangle/matrix_rectangle_input_a_" +
                  std::to_string(quantity + 1) + ".txt";
      fileNameB = "input_files/matrix/rectangle/matrix_rectangle_input_b_" +
                  std::to_string(quantity + 1) + ".txt";
      break;
    }
    default: {
      fileNameA = "input_files/matrix/square/matrix_square_input_a_" +
                  std::to_string(quantity + 1) + ".txt";
      fileNameB = "input_files/matrix/square/matrix_square_input_b_" +
                  std::to_string(quantity + 1) + ".txt";
      break;
    }
    }
    int A[matrixAMaxWitdh][matrixAMaxHeight];
    int B[matrixBMaxWitdh][matrixBMaxHeight];
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(1, distributionMax);
    std::vector<int> array;
    float increasingComplexityAW =
        (matrixAMaxWitdh / totalSetOfFiles) * quantity;
    float increasingComplexityAH =
        (matrixAMaxHeight / totalSetOfFiles) * quantity;
    float increasingComplexityBW =
        (matrixBMaxWitdh / totalSetOfFiles) * quantity;
    float increasingComplexityBH =
        (matrixBMaxHeight / totalSetOfFiles) * quantity;

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

void MatrixUtilities::writeMatrixToOutputFile(
    std::vector<std::vector<int>> array, const std::string &filename,
    const std::string &directory) {
  std::ofstream outFile(directory + "/" + filename);
  if (outFile.is_open()) {
    for (int i = 0; i < array.size(); i++) {
      for (int j = 0; j < array[0].size(); j++) {
        outFile << array[i][j] << " ";
      }
      outFile.close();
    }
  }
}