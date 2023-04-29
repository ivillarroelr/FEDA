#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "../headers/SortingAlgorithms.h"
#include "../headers/SortingUtilities.h"

std::vector<int> arrayOfNumbersRandomized;
std::vector<int> arrayOfNumbersPartial;
std::vector<int> arrayOfNumbersSemi;
std::vector<int> arrayOfNumbersBacksorted;
SortingAlgorithms sort;
SortingUtilities sUtils;

enum SortingExperiments {
  bubblesort,
  mergesort,
  quicksort,
  insertionsort,
  stlsort
};

const std::string SORTING_EXPERIMENT_OUTPUT = "statistics/sorting_results.csv";

void populateArrayAndExecuteExperiments(std::vector<int> &array,
                                        std::filesystem::path dir, int &counter,
                                        long totalFiles,
                                        TypeOfInputForSortingFiles type,
                                        std::ofstream &sortingOutputFile) {
  for (int i = 1; i <= totalFiles; i++) {
    int percentage = (i * 100) / totalFiles;
    std::cout << "\r"
              << "Bubblesort Working: " + std::to_string(percentage) + "%"
              << std::flush;
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
          std::cout << filename << std::endl;
          std::string line;
          while (std::getline(file, line)) {
            int number = std::stoi(line);
            array.push_back(number);
          }
          file.close();
          auto start = std::chrono::high_resolution_clock::now();
          sort.bubbleSort(array);
          auto stop = std::chrono::high_resolution_clock::now();
          auto duration =
              std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
                  .count();
          sUtils.writeVectorToOutputFile(
              array, "output_bubblesort_for_" + filename,
              "output_files");
          sortingOutputFile << "bubblesort"
                     << ","
                            << filename.substr(
                            0, filename.length())
                     << "," << array.size() << "," << duration << std::endl;
          } else {
          std::cerr << "Error al abrir el archivo: " << inputFile.path()
                    << '\n';
        }
      }
    }
    arrayOfNumbersRandomized.clear();
    arrayOfNumbersPartial.clear();
    arrayOfNumbersSemi.clear();
    arrayOfNumbersBacksorted.clear();
    counter++;
  }
}

int main(int argc, char *argv[]) {
  std::ofstream sortingOutputFile(SORTING_EXPERIMENT_OUTPUT);
  sortingOutputFile << "Experiment,Dataset,Entries,Time(us)" << std::endl;
  if (argc > 1) {
    unsigned int amountOfRandomNumbers = atoi(argv[1]);
    unsigned int distributionMax = atoi(argv[2]);
    unsigned int totalAmountOfFiles = atoi(argv[3]);

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

  int filecounterSortingRandomized = 1;
  const auto totalFilesSortingRandomized =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_randomized),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
      arrayOfNumbersRandomized, input_dir_path_sorting_randomized,
      filecounterSortingRandomized, totalFilesSortingRandomized, randomized,
      sortingOutputFile);
  int filecounterSortingPartial = 1;
  const auto totalFilesSortingPartial =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_partial),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
      arrayOfNumbersPartial, input_dir_path_sorting_partial,
      filecounterSortingPartial, totalFilesSortingPartial, partial,
      sortingOutputFile);
  int filecounterSortingSemi = 1;
  const auto totalFilesSortingSemi =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_semi),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
      arrayOfNumbersSemi, input_dir_path_sorting_semi,
      filecounterSortingSemi, totalFilesSortingSemi, semi, sortingOutputFile);
  int filecounterSortingBacksorted = 1;
  const auto totalFilesSortingBacksorted =
      std::distance(std::filesystem::recursive_directory_iterator(
                        input_dir_path_sorting_backsorted),
                    std::filesystem::recursive_directory_iterator{});

  populateArrayAndExecuteExperiments(
      arrayOfNumbersBacksorted, input_dir_path_sorting_backsorted,
      filecounterSortingBacksorted, totalFilesSortingBacksorted, backsorted,
      sortingOutputFile);
  std::cout << std::endl;
  return 0;
}
