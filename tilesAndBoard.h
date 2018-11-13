#ifndef FITZ_3_C_TILES_H
#define FITZ_3_C_TILES_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tileAndGameData.h"

/*
 * Tile-related functions.
 */
int tile_counter(char fileName[]);
void print_tile_file(Tile tiles[], int noOfTiles);
void load_tile_file(char fileName[], int noOfTiles, Tile tiles[]);
void print_tile(Tile tile);
void place_tile(struct GameData gameData, Tile tile, int row, int col);
Tile rotate_tile(Tile tiles[], int index, int rotation);
Tile clear_tile(Tile tile);
void load_save_file(char* input, char** args);

/*
 * Board-related functions.
 */
void print_current_board(struct GameData gameData);
void make_new_board(char** board, int height, int width);

#endif //FITZ_3_C_TILES_H
