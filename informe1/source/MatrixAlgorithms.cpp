#include <vector>
#include <string>

#include "../headers/MatrixAlgorithms.h"


std::vector<std::vector<int>> MatrixAlgorithms::standard_mm(
    const std::vector<std::vector<int>> &A,
    const std::vector<std::vector<int>> &B) {
  int n = A.size();
  int m = A[0].size();
  int k = B[0].size();

  std::vector<std::vector<int>> C(n, std::vector<int>(k, 0));

  for(int i = 0; i < n; i++) 
    for(int j = 0; j < k; j++)
      for(int k = 0; k < m; k++)
        C[i][j] += A[i][k] * B[k][j];

  return C;
}