//game.cs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "boat.h" 
#include "game.h"

// Enumeration pour le type de case du plateau
enum CellType {
    WATER,
    WATER_SHOT,
    BOAT,
    WRECK
};

// Structure pour chaque bateau
struct Boat {
    int size;
    int x, y;  // Position de référence
    char orientation;
};

// Structure pour le plateau de jeu
struct GameBoard {
    enum CellType** cells;
    int size;
};

// Structure pour le jeu
struct Game {
    struct GameBoard* playerBoard;
    struct GameBoard* computerBoard;
    struct Boat** playerBoats;
    struct Boat** computerBoats;
    int numBoats;
};

// Fonction pour créer un bateau
struct Boat* createBoat(int size, int x, int y, char orientation) {
    struct Boat* boat = (struct Boat*)malloc(sizeof(struct Boat));
    if (boat != NULL) {
        boat->size = size;
        boat->x = x;
        boat->y = y;
        boat->orientation = orientation;
    }
    return boat;
}

// Fonction pour vérifier si un bateau est encore en vie
bool isBoatAlive(struct Boat* boat) {
    return boat->size > 0;
}

// Fonction pour créer un plateau de jeu
struct GameBoard* createGameBoard(int size) {
    struct GameBoard* board = (struct GameBoard*)malloc(sizeof(struct GameBoard));
    if (board != NULL) {
        board->size = size;

        // Allouer de la mémoire pour les cellules
        board->cells = (enum CellType**)malloc(size * sizeof(enum CellType*));
        for (int i = 0; i < size; ++i) {
            board->cells[i] = (enum CellType*)malloc(size * sizeof(enum CellType));
            for (int j = 0; j < size; ++j) {
                board->cells[i][j] = WATER;
            }
        }
    }
    return board;
}

// Fonction pour libérer la mémoire d'un plateau de jeu
void destroyGameBoard(struct GameBoard* board) {
    for (int i = 0; i < board->size; ++i) {
        free(board->cells[i]);
    }
    free(board->cells);
    free(board);
}

// Fonction pour afficher un plateau de jeu
void displayBoard(struct GameBoard* board, bool showShots) {
    printf("  ");
    for (int i = 0; i < board->size; ++i) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < board->size; ++i) {
        printf("%2d", i + 1);
        for (int j = 0; j < board->size; ++j) {
            if (showShots && board->cells[i][j] == WATER_SHOT) {
                printf(" X");  // Tir à l'eau
            } else if (!showShots && board->cells[i][j] == BOAT) {
                printf(" O");  // Bateau
            } else {
                printf(" .");  // Eau
            }
        }
        printf("\n");
    }
}

// Fonction pour placer les bateaux de manière aléatoire
void placeRandomBoats(struct Game* game, struct Boat** boats, int numBoats) {
    srand((unsigned int)time(NULL));

    int boardSize = game->playerBoard->size;
    int numBoats = game->numBoats;

    for (int i = 0; i < numBoats; ++i) {
        int x = rand() % boardSize;
        int y = rand() % boardSize;
        char orientation = (rand() % 2 == 0) ? 'H' : 'V';  // Horizontal ou vertical

        boats[i] = createBoat(3, x, y, orientation);  // Taille du bateau par défaut : 3

        // TODO : Assurez-vous que les bateaux ne se touchent pas
    }
}

// Fonction pour effectuer un tir
void performShot(struct GameBoard* targetBoard, int x, int y) {
    if (targetBoard->cells[x][y] == BOAT) {
        targetBoard->cells[x][y] = WRECK;
    } else {
        targetBoard->cells[x][y] = WATER_SHOT;
    }
}

// Fonction pour séquencer un tour de jeu (joueur ou ordinateur)
void playTurn(struct Game* game, struct GameBoard* targetBoard, bool isPlayer) {
    int x, y;

    if (isPlayer) {
        // Demander à l'utilisateur de saisir les coordonnées
        printf("Entrez les coordonnées (ex. A3) : ");
        char input[3];
        scanf("%s", input);

        // Convertir les coordonnées en indices de tableau
        x = input[1] - '1';
        y = input[0] - 'A';
    } else {
        // Générer des coordonnées aléatoires pour l'ordinateur
        x = rand() % targetBoard->size;
        y = rand() % targetBoard->size;
    }

    // Effectuer le tir
    performShot(targetBoard, x, y);

    // Afficher le résultat du tir
    printf("%s a tiré en %c%d. Résultat : ",
           (isPlayer) ? "Le joueur" : "L'ordinateur", 'A' + y, x + 1);

    if (targetBoard->cells[x][y] == WATER_SHOT) {
        printf("Tir à l'eau!\n");
    } else {
        printf("Touché!\n");
    }
}
