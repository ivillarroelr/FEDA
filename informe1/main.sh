#!/bin/bash
arg="$1"
current_directory=$(pwd)

function fc_clean {
  zip_file_sorting="input_files/sorting/sorting_input_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_matrix="input_files/matrix/matrix_input_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_output="output_files/output_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_results="statistics/results_$(date +"%Y%m%d%H%M%S").zip"
  txt_files_sorting=$(find input_files/sorting/ -name "*.txt")
  txt_files_matrix=$(find input_files/matrix/ -name "*.txt")
  txt_files_output=$(find output_files/ -name "*.txt")
  csv_files_results=$(find statistics/ -name "*.csv")

  zip -q "$zip_file_sorting" $txt_files_sorting
  zip -q "$zip_file_matrix" $txt_files_matrix
  zip -q "$zip_file_output" $txt_files_output
  zip -q "$zip_file_results" $csv_files_results

  echo "Files zipped"
  rm input_files/matrix/*.txt input_files/sorting/*.txt output_files/*.txt statistics/*.csv
  echo "Experiment files cleaned"
}

function fc_newrun {
  echo "Parameters for sorting experiments"
  echo "Enter amount of random numbers:"
  read amount_of_random_numbers
  echo "Enter distribution max:"
  read distribution_max
  echo "Enter total amount of files:"
  read total_amount_of_files
  echo "Parameters for matrix experiments"
  echo "Enter matrix A max. width:"
  read matrix_a_max_width
  echo "Enter matrix A max. height:"
  read matrix_a_max_height
  echo "Enter matrix B max. width:"
  read matrix_b_max_width
  echo "Enter matrix B max. height:"
  read matrix_b_max_height
  echo "Enter total set of files:"
  read matrix_total_set_of_files
  echo "Enter distribution max:"
  read matrix_distribution_max
  echo "Executing main program..."
  ./main $amount_of_random_numbers $distribution_max $total_amount_of_files $matrix_a_max_width $matrix_a_max_height $matrix_b_max_width $matrix_b_max_height $matrix_total_set_of_files $matrix_distribution_max
}

function fc_recompile {
  rm main
  g++ -lstdc++fs source/main.cpp source/SortingAlgorithms.cpp source/SortingUtilities.cpp source/MatrixAlgorithms.cpp source/MatrixUtilities.cpp -o main
  echo "Program recompiled"
}

function fc_rerun {
  zip_file_output="output_files/output_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_results="statistics/results_$(date +"%Y%m%d%H%M%S").zip"
  txt_files_output=$(find output_files/ -name "*.txt")
  csv_files_results=$(find statistics/ -name "*.csv")
  zip -q "$zip_file_output" $txt_files_output
  zip -q "$zip_file_results" $csv_files_results
  echo "Files zipped"
  rm output_files/*.txt statistics/*.csv
  echo "Experiment files cleaned"
  echo "Executing main program..."
  ./main
}

function fc_display {
  python3 graph/graphUtility.py
}

case $arg in
  clean)
    echo "Cleaning experiment files"
    fc_clean
    ;;
  rerun)
    echo "Re run"
    fc_rerun
    ;;
  newrun)
    echo "New run"
    fc_newrun
    ;;
   recompile)
    echo "Recompiling"
    fc_recompile
    ;;
   display)
    echo "Displaying results"
    fc_display
    ;;
  *)
    echo "Opción no reconocida"
    exit 1
    ;;
esac