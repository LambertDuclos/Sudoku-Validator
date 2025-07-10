# Sudoku validator

Ce programme fait la validation de grilles sudoku, et ce, en utilisant le "multithreading".

## Compilation et exécution

1. Le programme utilise `gcc` pour compiler le code source.

2. Vous devez être dans le dossier tp1 pour compiler avec Make et faire la commande `$make` dans la console. Cela va créer l'exécutable `sudoku_validator`.

3. Pour exécuter le programme, il faut faire la commande `$./sudoku_validator <fichier_sudoku>`. Le programme prend en argument un fichier texte contenant le ou les sudokus. Remplacer `<fichier_sudoku>` par votre fichier contenant vos sudokus.

## Particularité

- La structure du fichier de sudoku, pour être lue sans erreur, doit avoir la même structure que le fichier `test.txt` fourni par le professeur. Chaque sudoku est séparé par une ligne vide et chaque valeur est séparée par un espace. Par exemple:

```
7 9 2 1 5 4 3 8 6
6 4 3 8 2 7 1 5 9
8 5 1 3 9 6 7 2 4
2 6 5 9 7 3 8 4 1
4 8 9 5 6 1 2 7 3
3 1 7 4 8 2 9 6 5
1 3 6 7 4 8 5 9 2
9 7 4 2 1 5 6 3 8
5 2 8 6 3 9 4 1 7
```
``` 
Résultat pour le sudoku 1:
    Bravo! Votre sudoku est valide
```

- Un sudoku valide à 9 lignes et 9 colonnes. 

- Chaque valeur doit être un integer entre 1 et 9. Autrement, le programme affichera une erreur.

- Pour qu'un sudoku soit valide, il ne doit pas y avoir de doublons dans chaque ligne, colonne et sous-grille.

- Une sous-grille est de taille 3x3. Il y en a 9. Leur numérotation est de 1 à 9 et se fait de gauche à droite et de la première rangée de 3 lignes à la dernière.

- Si le sudoku est valide, le message "Bravo, Votre sudoku est valide" sera affiché.
