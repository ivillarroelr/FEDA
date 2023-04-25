#include <vector>
#include <string>


class MatrixAlgorithms {
public:
  std::vector<std::vector<int>> standard_mm(
      const std::vector<std::vector<int> > &A,
      const std::vector<std::vector<int> > &B);

  std::vector<std::vector<int>> transpose_mm(
      const std::vector<std::vector<int> > &A,
      const std::vector<std::vector<int> > &B);

  std::vector<std::vector<int>> strassen(
  const std::vector<std::vector<int> > &A,
  const std::vector<std::vector<int> > &B);

  private:
    std::vector<std::vector<int>> sumMatrix(
        const std::vector<std::vector<int> >& A,
        const std::vector<std::vector<int> >&B);

    std::vector<std::vector<int>> subMatrix(
        const std::vector<std::vector<int> >& A,
        const std::vector<std::vector<int> >& B);

};