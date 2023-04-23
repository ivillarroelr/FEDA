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

void SortingAlgorithms::mergeSort(std::vector<int>& array, int left, int right) {
  if (left < right) {
    int middle = left + (right - left) / 2;
    mergeSort(array, left, middle);
    mergeSort(array, middle + 1, right);
    merge(array, left, middle, right);
  }
}

void SortingAlgorithms::quickSort(std::vector<int>& array, int low, int high) {
  if (low < high) {
    int pivot = partition(array, low, high);
    quickSort(array, low, pivot - 1);
    quickSort(array, pivot + 1, high);
  }
}

void SortingAlgorithms::merge(std::vector<int>& array, int left, int middle, int right) {
  int n1 = middle - left + 1;
  int n2 = right - middle;
  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; i++) {
    L[i] = array[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = array[middle + 1 + j];
  }

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      array[k] = L[i];
      i++;
    }
        else {
      array[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    array[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    array[k] = R[j];
    j++;
    k++;
  }
}

int SortingAlgorithms::partition(std::vector<int>& array, int low, int high) {
  int pivot = array[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (array[j] < pivot) {
      i++;
      int temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }

  int temp = array[i + 1];
  array[i + 1] = array[high];
  array[high] = temp;

  return i + 1;
}