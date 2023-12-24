// boat.h
#ifndef BOAT_H
#define BOAT_H

/**
 * @file boat.h
 * @brief Definition of Boat structure and related functions.
 */

/**
 * @struct Point
 * @brief Represents a point with x and y coordinates.
 */
struct Point {
    int x; /**< x-coordinate */
    int y; /**< y-coordinate */
};

/**
 * @struct Boat
 * @brief Represents a boat with size, reference position, and orientation.
 */
struct Boat {
    int size; /**< Size of the boat */
    struct Point reference; /**< Reference position of the boat */
    char orientation; /**< Orientation of the boat (N, S, E, W) */
};

/**
 * @brief Creates a new boat with the specified parameters.
 * @param size Size of the boat.
 * @param x X-coordinate of the reference position.
 * @param y Y-coordinate of the reference position.
 * @param orientation Orientation of the boat.
 * @return A pointer to the created boat.
 */
struct Boat* createBoat(int size, int x, int y, char orientation);

/**
 * @brief Checks if a boat is still alive.
 * @param boat Pointer to the boat structure.
 * @return True if the boat is still alive, false otherwise.
 */
bool isBoatAlive(struct Boat* boat);

#endif // BOAT_H