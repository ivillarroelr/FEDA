#include <string>
#include <vector>

#include "../headers/MatrixAlgorithms.h"

std::vector<std::vector<int>>
MatrixAlgorithms::standard_mm(const std::vector<std::vector<int>> &A,
                              const std::vector<std::vector<int>> &B) {
  int n = A.size();
  int m = A[0].size();
  int k = B[0].size();

  std::vector<std::vector<int>> C(n, std::vector<int>(k, 0));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < k; j++)
      for (int k = 0; k < m; k++)
        C[i][j] += A[i][k] * B[k][j];

  return C;
}

std::vector<std::vector<int>>
MatrixAlgorithms::transpose_mm(const std::vector<std::vector<int>> &A,
                               const std::vector<std::vector<int>> &B) {
  int n = A.size();
  int m = A[0].size();
  int k = B[0].size();

  std::vector<std::vector<int>> Bt(k, std::vector<int>(m, 0));

  for (int i = 0; i < k; i++)
    for (int j = 0; j < m; j++)
      Bt[i][j] = B[j][i];

  std::vector<std::vector<int>> C(n, std::vector<int>(k, 0));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < k; j++) {
      int dotProduct = 0;
      for (int k = 0; k < m; k++)
        dotProduct += A[i][k] * Bt[j][k];
      C[i][j] = dotProduct;
    }

  return C;
}

// Función para sumar dos matrices
std::vector<std::vector<int>> MatrixAlgorithms::sumMatrix(const std::vector<std::vector<int>> &A,
                              const std::vector<std::vector<int>> &B) {
  int n = A.size();
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i][j] = A[i][j] + B[i][j];
    }
  }

  return result;
}

// Función para restar dos matrices
std::vector<std::vector<int>> MatrixAlgorithms::subMatrix(const std::vector<std::vector<int>> &A,
                                   const std::vector<std::vector<int>> &B) {
  int n = A.size();
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i][j] = A[i][j] - B[i][j];
    }
  }

  return result;
}

// Función para multiplicar dos matrices usando el algoritmo de Strassen
std::vector<std::vector<int>> MatrixAlgorithms::strassen(const std::vector<std::vector<int>> &A,
                                     const std::vector<std::vector<int>> &B) {
  int n = A.size();

  // Caso base: si la matriz es de tamaño 1x1
  if (n == 1) {
    std::vector<std::vector<int>> result(1, std::vector<int>(1, 0));
    result[0][0] = A[0][0] * B[0][0];
    return result;
  }

  // Dividir las matrices en submatrices más pequeñas
  int halfSize = n / 2;
  std::vector<std::vector<int>> a11(halfSize, std::vector<int>(halfSize, 0));
  std::vector<std::vector<int>> a12(halfSize, std::vector<int>(halfSize, 0));
  std::vector<std::vector<int>> a21(halfSize, std::vector<int>(halfSize, 0));
  std::vector<std::vector<int>> a22(halfSize, std::vector<int>(halfSize, 0));
  std::vector<std::vector<int>> b11(halfSize, std::vector<int>(halfSize, 0));
  std::vector<std::vector<int>> b12(halfSize, std::vector<int>(halfSize, 0));
  std::vector<std::vector<int>> b21(halfSize, std::vector<int>(halfSize, 0));
  std::vector<std::vector<int>> b22(halfSize, std::vector<int>(halfSize, 0));

  for (int i = 0; i < halfSize; i++) {
    for (int j = 0; j < halfSize; j++) {
      a11[i][j] = A[i][j];
      a12[i][j] = A[i][j + halfSize];
      a21[i][j] = A[i + halfSize][j];
      a22[i][j] = A[i + halfSize][j + halfSize];

      b11[i][j] = B[i][j];
      b12[i][j] = B[i][j + halfSize];
      b21[i][j] = B[i + halfSize][j];
      b22[i][j] = B[i + halfSize][j + halfSize];
    }
  }

  // Calcular los productos intermedios recursivamente
  std::vector<std::vector<int>> p1 =
      strassen(sumMatrix(a11, a22), sumMatrix(b11, b22));
  std::vector<std::vector<int>> p2 = strassen(sumMatrix(a21, a22), b11);
  std::vector<std::vector<int>> p3 = strassen(a11, subMatrix(b12, b22));
  std::vector<std::vector<int>> p4 = strassen(a22, subMatrix(b21, b11));
  std::vector<std::vector<int>> p5 = strassen(sumMatrix(a11, a12), b22);
  std::vector<std::vector<int>> p6 =
      strassen(subMatrix(a21, a11), sumMatrix(b11, b12));
  std::vector<std::vector<int>> p7 =
      strassen(subMatrix(a12, a22), sumMatrix(b21, b22));

  // Calcular las submatrices del resultado
  std::vector<std::vector<int>> c11 =
      sumMatrix(subMatrix(sumMatrix(p1, p4), p5), p7);
  std::vector<std::vector<int>> c12 = sumMatrix(p3, p5);
  std::vector<std::vector<int>> c21 = sumMatrix(p2, p4);
  std::vector<std::vector<int>> c22 =
      sumMatrix(subMatrix(sumMatrix(p1, p3), p2), p6);

  // Combinar las submatrices en la matriz resultante
  std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
  for (int i = 0; i < halfSize; i++) {
    for (int j = 0; j < halfSize; j++) {
      result[i][j] = c11[i][j];
      result[i][j + halfSize] = c12[i][j];
      result[i + halfSize][j] = c21[i][j];
      result[i + halfSize][j + halfSize] = c22[i][j];
    }
  }

  return result;
}