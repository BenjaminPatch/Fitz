//
// Created by benpa on 17-Aug-18.
//

#ifndef FITZ_3_C_GAMEINPUT_H
#define FITZ_3_C_GAMEINPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tileAndGameData.h"

int is_move_valid(struct GameData gameData, Tile tile, int row, int col);
int is_input_valid(char* input);
void size_of_input(char* input, int* sizeOfInput);
void parse_input(char* input, int* sizeOfInput,
	char* firstInput, char* secondInput, char* thirdInput);
void parse_save_input(char* saveFile, char* input);

#endif //FITZ_3_C_GAMEINPUT_H
