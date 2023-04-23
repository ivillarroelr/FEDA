#include <vector>

#include "../headers/SortingAlgorithms.h"

void SortingAlgorithms::bubbleSort(std::vector<int>& array) {
  int arraySize = array.size();
  for (int i = 0; i < arraySize - 1; ++i) {
    for (int j = 0; j < arraySize - i - 1; ++j) {
      if (array[j] > array[j + 1]) {
        // Swap arr[j] and arr[j + 1]
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}