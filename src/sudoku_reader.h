#ifndef SUDOKU_READER_H
#define SUDOKU_READER_H

#include "sudoku_validator.h"

/**
 * @brief Lit un fichier de sudoku et remplit une structure de grille.
 * @param filename Le nom du fichier à lire.
 * @param grid La structure de grille à remplir.
 */
void read_sudoku_from_file(const char *filename, struct sudoku_grid *grid);

#endif