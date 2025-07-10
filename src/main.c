#include "sudoku_reader.h"
#include "sudoku_validator.h"
#include <stdio.h>
#include <stdlib.h>
/**
 *@brief Lit un fichier de sudoku et remplit une structure de grille.
 *@param argc Le nombres d'arguments.
 *@param argv Un pointeur vers le nom du fichier à lire.
 *@return 0 si la lecture est réussie, 1 en cas d'erreur.
 */
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <fichier_sudoku>\n", argv[0]);
    return 1;
  }

  struct sudoku_grid grid;
  read_sudoku_from_file(argv[1], &grid);

  return 0;
}