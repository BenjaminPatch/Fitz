#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tilesAndBoard.h"
#include "tileAndGameData.h"

/* 
 * Loads a save file to be played.
 */
void load_save_file(char fileName[], char** args) {
    FILE* file = fopen(fileName, "r");
    int cha;
    int i = 0;
    int j = 0;
    while ((cha = fgetc(file)) != EOF) {
	if (cha == ' ' || cha == '\n') {
	    i += 1;
	    j = 0;
	} else {
	    args[i][j] = cha;
	    j += 1;
	}
    }
}
	
/* Each tile is 6 strings (except last is 5)
 * so count lines, +1, and divide by 6.
 */
int tile_counter(char fileName[]) {
    int noOfTiles = 0;
    int cha;
    FILE* file;
    file = fopen(fileName, "r");

    while ((cha = fgetc(file)) != EOF) {
        if (cha == '\n') {
            noOfTiles += 1;
        }
    }

    noOfTiles += 1;
    noOfTiles /= 6;
    return noOfTiles;
}

/*
 * loads the tile file "fileName" and stores it in array of Tiles "tiles".
 */
void load_tile_file(char fileName[], int noOfTiles, Tile tiles[]) {
    int cha;
    FILE* file;
    file = fopen(fileName, "r");

    for (int i = 0; i < noOfTiles; i++) {
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                cha = fgetc(file);
                if (cha == '\n') {
                    cha = fgetc(file);
                }
                tiles[i].coords[row][col] = cha;
            }
        }
        cha = fgetc(file);
    }
}

/*
 * Prints each tile in the given tile file, along with its rotations.
 */
void print_tile_file(Tile tiles[], int noOfTiles) {
    Tile tileRow[4];
    for (int count = 0; count < noOfTiles; count++) {
        tileRow[0] = tiles[count];
        tileRow[1] = rotate_tile(tiles, count, 90);
        tileRow[2] = rotate_tile(tiles, count, 180);
        tileRow[3] = rotate_tile(tiles, count, 270);
        for (int row = 0; row < 5; row++) {
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 5; i++) {
                    printf("%c", tileRow[j].coords[row][i]);
                }
                if (j != 3) {
                    printf(" ");
                }
            }
            printf("\n");
        }
        if (count < noOfTiles - 1) {
            printf("\n");
        }
    }
    fflush(stdout);
}

/*
 * prints a tile in tiles[]
 */
void print_tile(Tile tile) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            printf("%c", tile.coords[row][col]);
        }
        printf("\n");
    }
    fflush(stdout);
}

/*
 * Places a tile on board at (row, col).
 */
void place_tile(struct GameData gameData, Tile tile, int row, int col) {
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            if (tile.coords[i + 2][j + 2] == ',') {
                continue;
            }
            if (gameData.nextPlayer == 1) {
                gameData.board[row + i][col + j] = '#';
            } else {
                gameData.board[row + i][col + j] = '*';
            }
        }
    }
}

/*
 * Rotates the tile "tiles[index]".
 */
Tile rotate_tile(Tile tiles[], int index, int rotation) {
    Tile newTile, intTile;
    int rotCount = rotation / 90;
    intTile = tiles[index]; // Intermediate tile.
    if (rotCount == 0) {
        return tiles[index];
    }
    for(; rotCount > 0; rotCount--) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                newTile.coords[j][4 - i] = intTile.coords[i][j];
            }
        }
        intTile = newTile;
    }
    return newTile;
}

/*
 * Clears a tile, to make all the points commas (a.k.a empty).
 */
Tile clear_tile(Tile tile) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tile.coords[i][j] = ',';
        }
    }
    return tile;
}


/*
 * prints a 2d array that represents the game board.
 */
void print_current_board(struct GameData gameData) {
    for (int row = 0; row < gameData.height; row++) {
        for (int col = 0; col < gameData.width; col++) {
            printf("%c", gameData.board[row][col]);
        }
        printf("\n");
    }
    fflush(stdout);
}

/*
 * Makes new board where all the points are "."s.
 */
void make_new_board(char** board, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            board[i][j] = '.';
        }
    }
}
