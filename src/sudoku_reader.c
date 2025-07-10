#include "sudoku_reader.h"
#include "pthread.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Affiche les résultats de la validation d'un sudoku.
 * @param sudoku_number Le numéro du sudoku.
 * @param result La structure contenant les résultats de la validation.
 */
void print_sudoku_results(int sudoku_number,
                          const struct sudoku_results *result) {
  printf("Résultat pour le sudoku %d:\n", sudoku_number);
  if (result->error_count == 0) {
    printf("  Bravo! Votre sudoku est valide\n");
  } else {
    for (int i = 0; i < result->error_count; i++) {
      printf("  Erreur: %s\n", result->errors[i]);
    }
  }
  printf("\n");
}
/**
 * @brief Vérifie si le nombre de lignes dans le sudoku est valide.
 * @param ligne Le nombre de lignes lues.
 * @param result La structure contenant les résultats de la validation.
 * @param fill_array Indicateur pour remplir la grille.
 */
void check_row_count(int ligne, struct sudoku_results *result,
                     bool *fill_array) {
  if (ligne != 9) {
    snprintf(
        result->errors[result->error_count++], 256,
        "le nombre de lignes dans le sudoku est invalide: %d (doit être 9)",
        ligne);

    *fill_array = false;
  }
}

/**
 * @brief Traite la fin d'un sudoku, valide les lignes, colonnes et
 * sous-grilles, et affiche les résultats.
 * @param ligne Le nombre de lignes lues.
 * @param nb_sudoku Le compteur de sudokus traités.
 * @param fill_array Indicateur pour remplir la grille.
 * @param result La structure contenant les résultats de la validation.
 * @param is_last_sudoku Indicateur si c'est le dernier sudoku à traiter.
 * @param grid La grille de sudoku à valider.
 */
void process_end_of_sudoku(int *ligne, int *nb_sudoku, bool *fill_array,
                           struct sudoku_results *result, bool is_last_sudoku,
                           struct sudoku_grid *grid) {
  (*nb_sudoku)++;

  check_row_count(*ligne, result, fill_array);

  if (grid != NULL && *fill_array && result->error_count == 0) {
    int validation_result[11] = {0};
    pthread_t thread[11];
    struct thread_parameters param[11];

    for (int i = 0; i < 11; i++) {
      param[i].grid = grid;
      param[i].results = validation_result;
      param[i].thread_id = i;
      param[i].error_count = 0;
      param[i].duplicate_value[0] = 0;
      param[i].duplicate_row[0] = 0;
      param[i].duplicate_col[0] = 0;
    }

    pthread_create(&thread[0], NULL, validate_rows, &param[0]);
    pthread_create(&thread[1], NULL, validate_columns, &param[1]);

    for (int i = 2; i < 11; i++) {
      pthread_create(&thread[i], NULL, validate_subgrid, &param[i]);
    }

    for (int i = 0; i < 11; i++) {
      pthread_join(thread[i], NULL);
    }

    if (!validation_result[0]) {
      for (int i = 0; i < param[0].error_count; i++) {
        snprintf(result->errors[result->error_count++], 256,
                 "la valeur: %d a un doublon à la ligne: %d",
                 param[0].duplicate_value[i], param[0].duplicate_row[i] + 1);
      }
    }
    if (!validation_result[1]) {
      for (int i = 0; i < param[1].error_count; i++) {
        snprintf(result->errors[result->error_count++], 256,
                 "la valeur: %d a un doublon à la colonne: %d",
                 param[1].duplicate_value[i], param[1].duplicate_col[i] + 1);
      }
    }
    for (int i = 2; i < 11; i++) {
      if (!validation_result[i]) {
        for (int j = 0; j < param[i].error_count; j++) {
          snprintf(result->errors[result->error_count++], 256,
                   "la valeur: %d a un doublon dans la sous-grille: %d",
                   param[i].duplicate_value[j], i - 1);
        }
      }
    }
  }

  print_sudoku_results(*nb_sudoku, result);

  if (!is_last_sudoku) {
    *ligne = 0;
    *fill_array = true;
    result->error_count = 0;
  }
}

void read_sudoku_from_file(const char *filename, struct sudoku_grid *grid) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Erreur en ouvrant le fichier");
    return;
  }

  char buffer[256];
  int ligne = 0;
  int nb_sudoku = 0;
  bool fill_array = true;
  struct sudoku_results current_result = {0};

  while (fgets(buffer, sizeof(buffer), file)) {
    int only_whitespace = true;
    for (int i = 0; buffer[i] != '\0'; i++) {
      if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\r' &&
          buffer[i] != '\n') {
        only_whitespace = false;
        break;
      }
    }

    if (only_whitespace) {
      if (ligne > 0) {
        process_end_of_sudoku(&ligne, &nb_sudoku, &fill_array, &current_result,
                              false, grid);
      }
      continue;
    } else {
      ligne++;
      if (ligne > 9) {
        fill_array = false;
      }
    }

    int colonne = 0;
    char *token = strtok(buffer, " \t\r\n");
    while (token) {
      char *endptr;
      long value = strtol(token, &endptr, 10);

      if (*endptr != '\0' && colonne < 9) {
        snprintf(current_result.errors[current_result.error_count++], 256,
                 "la valeur à la position (%d,%d): '%s' n'est pas un integer",
                 ligne, colonne + 1, token);
        fill_array = false;
      } else if ((value < 1 || value > 9) && colonne < 9) {

        snprintf(current_result.errors[current_result.error_count++], 256,
                 "la case (%d,%d): %ld (doit être entre 1 et 9)", ligne,
                 colonne + 1, value);
        fill_array = false;
      }

      if (grid != NULL && fill_array && ligne <= 9 && colonne < 9) {
        grid->cells[ligne - 1][colonne] = (int)value;
      }

      colonne++;
      token = strtok(NULL, " \t\r\n");
    }

    if (colonne != 9 && ligne <= 9) {
      snprintf(current_result.errors[current_result.error_count++], 256,
               "le nombre de colonnes dans le sudoku est invalide: %d (doit "
               "être 9) à la ligne %d",
               colonne, ligne);
      fill_array = false;
    }
  }

  if (ligne > 0) {
    process_end_of_sudoku(&ligne, &nb_sudoku, &fill_array, &current_result,
                          true, grid);
  }

  fclose(file);
}
