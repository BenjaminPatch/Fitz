//
// Created by benpa on 17-Aug-18.
//

#include "gameInput.h"
#include "tileAndGameData.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Counts the size of user's turn input.
 * Used for parsing the input.
 */
void size_of_input(char* input, int* sizeOfInput) {
    int firstLength = 0;
    int secondLength = 0;
    int thirdLength = 0;
    while (1) {
        if (input[firstLength] == ' ') {
            break;
        }
        firstLength++;
    }
    while (1) {
        if (input[secondLength + firstLength + 1] == ' ') {
            break;
        }
        secondLength++;
    }
    while (1) {
        if (input[secondLength + firstLength + thirdLength + 3] == '\0') {
            break;
        }
        thirdLength++;
    }
    sizeOfInput[0] = firstLength;
    sizeOfInput[1] = secondLength;
    sizeOfInput[2] = thirdLength;
}

/*
 * Parses the users input for their intended turn.
 */
void parse_input(char* input, int* sizeOfInput,
	char* firstInput, char* secondInput, char* thirdInput) {
    for (int i = 0; i < sizeOfInput[0]; i++) {
        firstInput[i] = input[i];
    }
    for (int i = 0; i < sizeOfInput[1]; i++) {
        secondInput[i] = input[i + sizeOfInput[0] + 1];
    }
    for (int i = 0; i < sizeOfInput[2]; i++) {
        thirdInput[i] = input[i + sizeOfInput[0] + sizeOfInput[1] + 2];
    }
}

/*
 * Checks if user's input is valid
 */
int is_input_valid(char* input) {
    char angle[3];
    int count = 0;
    int wasPreviousSpace = 0;
    int inputLength = strlen(input);
    if (input[0] == 's' && input[1] == 'a' && 
	    input[2] == 'v' && input[3] == 'e') {
	return 2;
    }
    for (int i = 0; i < inputLength - 1; i++) {
        if (!isdigit(input[i]) && input[i] != ' ' && input[i] != '-') {
            return 0;
        }
        if (input[i] == ' ') {
            wasPreviousSpace += 1;
            count++;
        } else {
            wasPreviousSpace = 0;
        }
        if (wasPreviousSpace == 2) {
            return 0; //Returns 0 if there are two spaces in a row.
        }
    }
    angle[0] = input[inputLength - 4];
    angle[1] = input[inputLength - 3];
    angle[2] = input[inputLength - 2];

    if (strcmp(angle, " 90") ||
	    strcmp(angle, "180") || strcmp(angle, "270")) {
        angle[0] = input[inputLength - 2];
        angle[1] = ' ';
        angle[2] = ' ';
        if (strcmp(angle, "0  ")) {
            return 0;
        }
    }
    if (count != 2) {
        return 0;
    } else {
	return 1;
    }
}

/*
 * Parses the users input if they attempt to load saved game.
 */
void parse_save_input(char* saveFile, char* input) {
    int i = 4;

    while (1) {
	if (input[i] == '\0' || input[i] == '\n') {
	    break;
	}
	saveFile[i - 4] = input[i];
	i++;
    }
}

/*
 * Checks if the intended move is valid or not.
 */
int is_move_valid(struct GameData gameData, Tile tile, int row, int col) {
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            if (tile.coords[i + 2][j + 2] == ',') {
                continue;
            }
            if ((row + i > gameData.height - 1) ||
		    (col + j > gameData.width - 1) || 
		    row + i < 0 || col + j < 0) {
                return 0;
            }
            if ((gameData.board[row + i][col + j] == '#') ||
		    (gameData.board[row + i][col + j] == '*')) {
                return 0;
            }
        }
    }
    return 1;
}
