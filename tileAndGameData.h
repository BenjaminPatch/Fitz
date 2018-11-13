//
// Created by benpa on 08-Aug-18.
//

#ifndef ASS1_TILESTRUCT_H
#define ASS1_TILESTRUCT_H

typedef struct {
    char coords[5][5];
} Tile;

typedef enum ExitCode {
    INCORRECT_ARG_COUNT = 1,
    TILE_FILE_NULL = 2,
    BAD_TILE_FILE = 3,
    INVALID_PLAYER_TYPE = 4,
    INVALID_DIM = 5,
    SAVE_FILE_NULL = 6,
    BAD_SAVE_FILE = 7,
    EOF_WHILE_WAITING = 10
} ExitCode;

struct GameData {
    int nextPlayer;
    int height;
    int width;
    char** board;
    int noOfTiles;
    int currentTile;
    char p1Type;
    char p2Type;
    //Tile tiles[];
} gameData;
#endif //ASS1_TILESTRUCT_H
