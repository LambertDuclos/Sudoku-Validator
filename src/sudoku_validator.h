#ifndef SUDOKU_VALIDATOR_H
#define SUDOKU_VALIDATOR_H

#include "threads_parameters.h"
#include <stdbool.h>

#define SUDOKU_SIZE 9
#define MAX_ERRORS 100

/**
 * @brief Structure qui représente un sudoku.
 */
struct sudoku_grid {
  int cells[SUDOKU_SIZE][SUDOKU_SIZE];
};

/**
 * @brief Structure qui contient les résultats de la validation d'un sudoku.
 */
struct sudoku_results {
  int error_count;
  char errors[MAX_ERRORS][256];
};

/**
 * @brief Valide les lignes d'une grille de Sudoku.
 * @param arg Pointeur vers les paramètres du thread contenant la grille et les
 * résultats.
 * @return NULL
 */
void *validate_rows(void *arg);

/**
 * @brief Valide les colonnes d'une grille de Sudoku.
 * @param arg Pointeur vers les paramètres du thread contenant la grille et les
 * résultats.
 * @return NULL
 */
void *validate_columns(void *arg);

/**
 * @brief Valide les sous-grilles d'une grille de Sudoku.
 * @param arg Pointeur vers les paramètres du thread contenant la grille et les
 * résultats.
 * @return NULL
 */
void *validate_subgrid(void *arg);
#endif