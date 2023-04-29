#!/bin/bash
arg="$1"
current_directory=$(pwd)
time=$(date +"%Y%m%d%H%M%S")

function fc_clean {
  zip_file_sorting_randomized="input_files/sorting/randomized/sorting_input_randomized_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_sorting_partial="input_files/sorting/partial/sorting_input_partial_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_sorting_semi="input_files/sorting/semi/sorting_input_semi_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_sorting_backsorted="input_files/sorting/backsorted/sorting_input_backsorted_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_matrix_square="input_files/matrix/square/matrix_square_input_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_matrix_rectangle="input_files/matrix/rectangle/matrix_rectangle_input_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_output="output_files/output_$(date +"%Y%m%d%H%M%S").zip"
  zip_file_results="statistics/results_$(date +"%Y%m%d%H%M%S").zip"
  txt_files_sorting_randomized=$(find input_files/sorting/randomized/ -name "*.txt")
  txt_files_sorting_partial=$(find input_files/sorting/partial/ -name "*.txt")
  txt_files_sorting_semi=$(find input_files/sorting/semi/ -name "*.txt")
  txt_files_sorting_backsorted=$(find input_files/sorting/backsorted/ -name "*.txt")
  txt_files_matrix_square=$(find input_files/matrix/square/ -name "*.txt")
  txt_files_matrix_rectangle=$(find input_files/matrix/rectangle/ -name "*.txt")
  txt_files_output=$(find output_files/ -name "*.txt")
  csv_files_results=$(find statistics/ -name "*.csv")

  zip -q "$zip_file_sorting_randomized" $txt_files_sorting_randomized
  zip -q "$zip_file_sorting_partial" $txt_files_sorting_partial
  zip -q "$zip_file_sorting_semi" $txt_files_sorting_semi
  zip -q "$zip_file_sorting_backsorted" $txt_files_sorting_backsorted
  zip -q "$zip_file_matrix_square" $txt_files_matrix_square
  zip -q "$zip_file_matrix_rectangle" $txt_files_matrix_rectangle
  zip -q "$zip_file_output" $txt_files_output
  zip -q "$zip_file_results" $csv_files_results

  echo "Files zipped"
  rm *.out input_files/matrix/*.txt input_files/sorting/*/*.txt output_files/*.txt statistics/*.csv
  echo "Experiment files cleaned"
}

function fc_delete {
    echo "Are you sure to delete all experiment files? (yes/no)"
    read answer
    if [ "$answer" = "yes" ]; then
      rm input_files/matrix/*
      rm input_files/sorting/backsorted/*
      rm input_files/sorting/partial/*
      rm input_files/sorting/randomized/*
      rm input_files/sorting/semi/*
      rm output_files/*
      rm statistics/*
      rm *.out
      echo "Files deleted"
    else
      echo "Operation canceled"
    fi

  }

function fc_newrun {
  echo "Parameters for sorting experiments"
  echo "Enter amount of random numbers:"
  read amount_of_random_numbers
  echo "amount_of_random_numbers,$amount_of_random_numbers" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter distribution max:"
  read distribution_max
  echo "distribution_max,$distribution_max" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter total amount of files:"
  read total_amount_of_files
  echo "total_amount_of_files,$total_amount_of_files" >> "statistics/newrun_parameters_$time.csv"
  echo "Parameters for SQUARE matrix experiments"
  echo "Enter matrix A max. width:"
  read matrix_square_a_max_width
  echo "matrix_square_a_max_width,$matrix_square_a_max_width" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter matrix A max. height:"
  read matrix_square_a_max_height
  echo "matrix_square_a_max_height,$matrix_square_a_max_height" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter matrix B max. width:"
  read matrix_square_b_max_width
  echo "matrix_square_b_max_width,$matrix_square_b_max_width" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter matrix B max. height:"
  read matrix_square_b_max_height
  echo "matrix_square_b_max_height,$matrix_square_b_max_height" >> "statistics/newrun_parameters_$time.csv"
  echo "Parameters for RECTANGLE matrix experiments"
  echo "Enter matrix A max. width:"
  read matrix_rectangle_a_max_width
  echo "matrix_rectangle_a_max_width,$matrix_rectangle_a_max_width" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter matrix A max. height:"
  read matrix_rectangle_a_max_height
  echo "matrix_rectangle_a_max_height,$matrix_rectangle_a_max_height" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter matrix B max. width:"
  read matrix_rectangle_b_max_width
  echo "matrix_rectangle_b_max_width,$matrix_rectangle_b_max_width" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter matrix B max. height:"
  read matrix_rectangle_b_max_height
  echo "matrix_rectangle_b_max_height,$matrix_rectangle_b_max_height" >> "statistics/newrun_parameters_$time.csv"
  echo "Shared Parameters for matrix experiments"
  echo "Enter total set of files:"
  read matrix_total_set_of_files
  echo "matrix_total_set_of_files,$matrix_total_set_of_files" >> "statistics/newrun_parameters_$time.csv"
  echo "Enter distribution max:"
  read matrix_distribution_max
  echo "matrix_distribution_max,$matrix_distribution_max" >> "statistics/newrun_parameters_$time.csv"
  echo "Executing bubblesort program..."
  ./bubblesort.out $amount_of_random_numbers $distribution_max $total_amount_of_files
  echo "Executing insertionsort program..."
  ./insertionsort.out $amount_of_random_numbers $distribution_max $total_amount_of_files
  echo "Executing mergesort program..."
  ./mergesort.out $amount_of_random_numbers $distribution_max $total_amount_of_files
  echo "Executing quicksort program..."
  ./quicksort.out $amount_of_random_numbers $distribution_max $total_amount_of_files
  echo "Executing stlsort program..."
  ./stlsort.out $amount_of_random_numbers $distribution_max $total_amount_of_files
  echo "Executing squarematrix program..."
  ./squarematrix.out $matrix_square_a_max_width $matrix_square_a_max_height $matrix_square_b_max_width $matrix_square_b_max_height $matrix_total_set_of_files $matrix_distribution_max
  echo "Executing rectanglematrix program..."
  ./rectanglematrix.out $matrix_rectangle_a_max_width $matrix_rectangle_a_max_height $matrix_rectangle_b_max_width $matrix_rectangle_b_max_height $matrix_total_set_of_files $matrix_distribution_max
}

function fc_recompile {
  rm *.out
  g++ -lstdc++fs source/bubblesort.cpp source/SortingAlgorithms.cpp source/SortingUtilities.cpp -o bubblesort.out
  g++ -lstdc++fs source/insertionsort.cpp source/SortingAlgorithms.cpp source/SortingUtilities.cpp -o insertionsort.out
  g++ -lstdc++fs source/mergesort.cpp source/SortingAlgorithms.cpp source/SortingUtilities.cpp -o mergesort.out
  g++ -lstdc++fs source/quicksort.cpp source/SortingAlgorithms.cpp source/SortingUtilities.cpp -o quicksort.out
  g++ -lstdc++fs source/stlsort.cpp source/SortingAlgorithms.cpp source/SortingUtilities.cpp -o stlsort.out
  g++ -lstdc++fs source/squarematrix.cpp source/MatrixAlgorithms.cpp source/MatrixUtilities.cpp -o squarematrix.out
  g++ -lstdc++fs source/rectanglematrix.cpp source/MatrixAlgorithms.cpp source/MatrixUtilities.cpp -o rectanglematrix.out
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

function fc_matrixdisplay {
  python3 graph/graphMatrix.py
}

function fc_sortingdisplay {
  python3 graph/graphSorting.py
}

function fc_help {
  echo -e "\033[1mAvailable options\033[0m"
  echo ""
  echo -e "\033[1mclean\033[0m : Zip and Delete experiment files (input, output and results)"
  echo ""
  echo -e "\033[1mrerun\033[0m : Runs again the experiment with current input files, zipping and deleting output and result files"
  echo ""
  echo -e "\033[1mnewrun\033[0m : Runs new experiment, cleaning the environment and prompting for new parameters"
  echo ""
  echo -e "\033[1mrecompile\033[0m : Deletes current main program and recompiles it"
  echo ""
  echo -e "\033[1mmatrixdisplay\033[0m : Shows graphics for current matrix results"
  echo ""
  echo -e "\033[1msortingdisplay\033[0m : Shows graphics for current sorting results"
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
   matrixdisplay)
    echo "Displaying matrix results"
    fc_matrixdisplay
    ;;
   sortingdisplay)
    echo "Displaying matrix results"
    fc_sortingdisplay
    ;;
   help)
    fc_help
    ;;
   delete)
    fc_delete
    ;;
  *)
    echo "Opción no reconocida"
    exit 1
    ;;
esac