#ifndef THREADS_PARAMETERS_H
#define THREADS_PARAMETERS_H

#include <pthread.h>

/**
 * @brief Structure qui contient les paramètres pour les threads de validation
 * d'un Sudoku.
 */
struct thread_parameters {
  int duplicate_row[10];
  int duplicate_col[10];
  int thread_id;
  int *results;
  int error_count;
  struct sudoku_grid *grid;
  int duplicate_value[10];
};

#endif