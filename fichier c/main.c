// main.c#include "game.h"
#include "boat.c" 
#include "game.c"
#include <stdlib.h>
#include <stdbool.h>


// Fonction principale
int main() {
    // Initialiser le jeu avec 5 bateaux et une taille de plateau de 10x10
    struct Game* game = (struct Game*)malloc(sizeof(struct Game));
    game->numBoats = 5;
    game->playerBoard = createGameBoard(10);
    game->computerBoard = createGameBoard(10);
    game->playerBoats = (struct Boat**)malloc(game->numBoats * sizeof(struct Boat*));
    game->computerBoats = (struct Boat**)malloc(game->numBoats * sizeof(struct Boat*));

    // Lancer le jeu
// Fonction principale pour séquencer l'ensemble du jeu
    printf("Bienvenue dans la Bataille Navale contre l'ordinateur!\n\n");

    // Initialiser les plateaux et placer les bateaux
    placeRandomBoats(game, game->playerBoats, game->numBoats);
    placeRandomBoats(game, game->computerBoats, game->numBoats);

    // Afficher le plateau du joueur (pour test)
    printf("Plateau du joueur :\n");
    displayBoard(game->playerBoard, false);

    // Jouer le jeu jusqu'à ce qu'un joueur gagne
    while (true) {
        printf("\nTour du joueur :\n");
        playTurn(game, game->computerBoard, true);
        displayBoard(game->computerBoard, true);

        // Vérifier si le joueur a gagné
        if (hasPlayerWon(game->computerBoats, game->numBoats)) {
            printf("Félicitations! Vous avez gagné!\n");
                        // Vérifier si l'ordinateur a gagné
            if (hasPlayerWon(game->playerBoats, game->numBoats)) {
                printf("L'ordinateur a gagné! Meilleure chance la prochaine fois.\n");
                break;
            }

            printf("\nTour de l'ordinateur :\n");
            playTurn(game, game->playerBoard, false);
            displayBoard(game->playerBoard, true);

            // Vérifier si l'ordinateur a gagné
            if (hasPlayerWon(game->playerBoats, game->numBoats)) {
                printf("L'ordinateur a gagné! Meilleure chance la prochaine fois.\n");
                break;
            }
        }
    }

    // Libérer la mémoire
    destroyGameBoard(game->playerBoard);
    destroyGameBoard(game->computerBoard);

    for (int i = 0; i < game->numBoats; ++i) {
        free(game->playerBoats[i]);
        free(game->computerBoats[i]);
    }

    free(game->playerBoats);
    free(game->computerBoats);
    free(game);

    return 0;
}
