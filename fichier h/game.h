// game.h
#ifndef GAME_H
#define GAME_H

#include "boat.h"

/**
 * @file game.h
 * @brief Definition of GameBoard and Game structures, and related functions.
 */

/**
 * @enum CaseType
 * @brief Represents the type of a case on the game board.
 */
enum CaseType {
    WATER, /**< Water */
    WATER_SHOT, /**< Water shot */
    BOAT, /**< Boat */
    WRECK /**< Wreck */
};

/**
 * @struct GameBoard
 * @brief Represents the game board with a matrix of CaseType.
 */
struct GameBoard {
    enum CaseType** matrix; /**< 2D matrix representing the game board */
    int size; /**< Size of the game board */
};

/**
 * @struct Game
 * @brief Represents the game with two game boards and arrays of boats.
 */
struct Game {
    struct GameBoard* player1Board; /**< Game board for player 1 */
    struct GameBoard* computerBoard; /**< Game board for player 2 */
    struct Boat** player1Boats; /**< Array of boats for player 1 */
    struct Boat** computerBoard; /**< Array of boats for player 2 */
};

/**
 * @brief Creates a new game with the specified board size and number of boats.
 * @param boardSize Size of the game board.
 * @param numBoats Number of boats for each player.
 * @return A pointer to the created game.
 */
struct Game* createGame(int boardSize, int numBoats);

/**
 * @brief Places boats randomly on the game board.
 * @param game Pointer to the game structure.
 * @param boats Array of boat pointers.
 * @param numBoats Number of boats to place.
 */
void placeRandomBoats(struct Game* game, struct Boat** boats, int numBoats);

/**
 * @brief Displays the game board.
 * @param board Pointer to the game board structure.
 * @param showShots If true, display shots; otherwise, display boats.
 */
void displayBoard(struct GameBoard* board, bool showShots);

/**
 * @brief Performs a player's turn.
 * @param game Pointer to the game structure.
 * @param opponentBoard Pointer to the opponent's game board.
 */
void playerTurn(struct Game* game, struct GameBoard* opponentBoard);

/**
 * @brief Performs the computer's turn.
 * @param game Pointer to the game structure.
 * @param playerBoard Pointer to the player's game board.
 */
void computerTurn(struct Game* game, struct GameBoard* playerBoard);

/**
 * @brief Plays the game, sequencing turns until there is a winner.
 * @param game Pointer to the game structure.
 */
void playGame(struct Game* game);

/**
 * @brief Cleans up resources allocated for the game.
 * @param
 */
#endif 