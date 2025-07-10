#!/usr/bin/env bats
load 'bats-support/load'
load 'bats-assert/load'


@test "Valid sudoku is accepted with correct formatting" {
  run ./sudoku_validator test/data/valid.txt
  [ "$status" -eq 0 ]
  
  assert_line --index 0 "Résultat pour le sudoku 1:"
  assert_line --index 1 "  Bravo! Votre sudoku est valide"
}

@test "Missing a lines" {
  run ./sudoku_validator test/data/invalid_nb_line.txt
  [ "$status" -eq 0 ]
  assert_line --index 0 "Résultat pour le sudoku 1:"
  assert_line --index 1 "  Bravo! Votre sudoku est valide"
  assert_line --index 2 "Résultat pour le sudoku 2:"
  assert_line --index 3 "  Erreur: le nombre de lignes dans le sudoku est invalide: 8 (doit être 9)"
}

@test "Too many lines" {
  run ./sudoku_validator test/data/invalid_too_many_lines.txt
  [ "$status" -eq 0 ]
  assert_line --index 0 "Résultat pour le sudoku 1:"
  assert_line --index 1 "  Bravo! Votre sudoku est valide"
  assert_line --index 2 "Résultat pour le sudoku 2:"
  assert_line --index 3 "  Erreur: le nombre de lignes dans le sudoku est invalide: 10 (doit être 9)"
}

@test "Invalid token" {
  run ./sudoku_validator test/data/invalid_token.txt
  [ "$status" -eq 0 ]
  assert_line --index 0 "Résultat pour le sudoku 1:"
  assert_line --index 1 "  Bravo! Votre sudoku est valide"
  assert_line --index 2 "Résultat pour le sudoku 2:"
  assert_line --index 3 "  Erreur: la valeur à la position (4,2): 'X' n'est pas un integer"
}

@test "invalid number of columns" {
  run ./sudoku_validator test/data/invalid_nb_column.txt
  [ "$status" -eq 0 ]
  assert_line --index 0 "Résultat pour le sudoku 1:"
  assert_line --index 1 "  Bravo! Votre sudoku est valide"
  assert_line --index 2 "Résultat pour le sudoku 2:"
  assert_line --index 3 "  Erreur: le nombre de colonnes dans le sudoku est invalide: 8 (doit être 9) à la ligne 1"
  assert_line --index 4 "  Erreur: le nombre de colonnes dans le sudoku est invalide: 10 (doit être 9) à la ligne 3"
}

@test "invalid integer" {
  run ./sudoku_validator test/data/invalid_integer.txt
  [ "$status" -eq 0 ]
  assert_line --index 0 "Résultat pour le sudoku 1:"
  assert_line --index 1 "  Erreur: la case (7,5): -2 (doit être entre 1 et 9)"
  assert_line --index 2 "Résultat pour le sudoku 2:"
  assert_line --index 3 "  Erreur: la case (2,6): 10 (doit être entre 1 et 9)"
}

@test "invalid multiples errors" {
  run ./sudoku_validator test/data/invalid_multiple_errors.txt
  [ "$status" -eq 0 ]
  assert_line --index 0 "Résultat pour le sudoku 1:"
  assert_line --index 1 "  Erreur: la valeur à la position (5,4): 'a' n'est pas un integer"
  assert_line --index 2 "  Erreur: le nombre de colonnes dans le sudoku est invalide: 8 (doit être 9) à la ligne 5"
  assert_line --index 3 "  Erreur: la valeur à la position (6,4): 'b' n'est pas un integer"
  assert_line --index 4 "  Erreur: la case (8,2): -5 (doit être entre 1 et 9)"
  assert_line --index 5 "  Erreur: le nombre de colonnes dans le sudoku est invalide: 8 (doit être 9) à la ligne 9"
  assert_line --index 6 "  Erreur: le nombre de lignes dans le sudoku est invalide: 10 (doit être 9)"
}

