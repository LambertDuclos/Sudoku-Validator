#include "sudoku_validator.h"
#include <stdio.h>
#include <stdlib.h>

void *validate_rows(void *arg) {
  struct thread_parameters *params = (struct thread_parameters *)arg;
  int *result = &(params->results[0]);
  *result = 1;
  params->error_count = 0;

  for (int row = 0; row < 9; row++) {
    int counts[10] = {0};

    for (int col = 0; col < 9; col++) {
      int num = params->grid->cells[row][col];
      if (num >= 1 && num <= 9) {
        counts[num]++;
      }
    }

    for (int val = 1; val <= 9; val++) {
      if (counts[val] > 1 && params->error_count < 10) {
        *result = 0;
        params->duplicate_value[params->error_count] = val;
        params->duplicate_row[params->error_count] = row;
        params->error_count++;
      }
    }
  }
  return NULL;
}

void *validate_columns(void *arg) {
  struct thread_parameters *params = (struct thread_parameters *)arg;
  int *result = &(params->results[1]);
  *result = 1;
  params->error_count = 0;

  for (int col = 0; col < 9; col++) {
    int counts[10] = {0};

    for (int row = 0; row < 9; row++) {
      int num = params->grid->cells[row][col];
      counts[num]++;
    }

    for (int val = 1; val <= 9; val++) {
      if (counts[val] > 1 && params->error_count < 10) {
        *result = 0;
        params->duplicate_value[params->error_count] = val;
        params->duplicate_col[params->error_count] = col;
        params->error_count++;
      }
    }
  }
  return NULL;
}

void *validate_subgrid(void *arg) {
  struct thread_parameters *params = (struct thread_parameters *)arg;
  int subgrid_id = params->thread_id - 2;
  int *result = &(params->results[params->thread_id]);
  *result = 1;
  params->error_count = 0;

  int row_start = (subgrid_id / 3) * 3;
  int col_start = (subgrid_id % 3) * 3;

  int counts[10] = {0};

  for (int row = row_start; row < row_start + 3; row++) {
    for (int col = col_start; col < col_start + 3; col++) {
      int num = params->grid->cells[row][col];
      if (num >= 1 && num <= 9) {
        counts[num]++;
      }
    }
  }

  for (int val = 1; val <= 9; val++) {
    if (counts[val] > 1 && params->error_count < 10) {
      *result = 0;

      params->duplicate_value[params->error_count] = val;
      params->duplicate_row[params->error_count] = row_start;
      params->duplicate_col[params->error_count] = col_start;
      params->error_count++;
    }
  }

  return NULL;
}
