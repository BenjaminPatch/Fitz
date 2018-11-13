#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "startProgramValidation.h"
#include "tileAndGameData.h"

/*
 * Checks the user input and returns the correct variable based on
 * the required exit status
 */
int check_user_input(int argc, char** argv) {
    if (argc != 6 && argc != 5 && argc != 2) {
	return INCORRECT_ARG_COUNT;
    }
    FILE* fileTest = fopen(argv[1], "r");
    if (fileTest == NULL) {
        return TILE_FILE_NULL;
    } else if (!validate_tile_file(argv[1])) {
        return BAD_TILE_FILE;
    }
    if (argc == 6) {
        fclose(fileTest);
        for (int i = 0; i < (int)strlen(argv[4]); i++) {
            if (!isdigit(argv[4][i])) {
                return INVALID_DIM;
            }
        }
        for (int i = 0; i < (int)strlen(argv[5]); i++) {
            if (!isdigit(argv[5][i])) {
                return INVALID_DIM;
            }
        }
        if (atoi(argv[4]) < 1) {
            return INVALID_DIM;
        } 
	if (atoi(argv[5]) < 1) {
            return INVALID_DIM;
        }
    }
    if (argc == 5) {
        FILE* fileTest = fopen(argv[4], "r");
        if (fileTest == NULL) {
            return SAVE_FILE_NULL;
        }
        if (!validate_save_file(argv[4])) {
            return BAD_SAVE_FILE;
        }
    }
    if (argc > 2) {
        if (strlen(argv[2]) != 1 || strlen(argv[3]) != 1) {
            return INVALID_PLAYER_TYPE;
        } else if (argv[2][0] != 'h' && argv[2][0] != '1' 
		&& argv[2][0] != '2') {
            return INVALID_PLAYER_TYPE;
        } else if (argv[3][0] != 'h' && argv[3][0] != '1' 
		&& argv[3][0] != '2') {
            return INVALID_PLAYER_TYPE;
        }
    }
    return 0;
}

/*
 * Validates the tile file, making sure all tiles are 5x5 and contain valid
 * elements.
 */
int validate_tile_file(char* fileName) {
    int row = 0;
    int col = 0;
    FILE* file = fopen(fileName, "r");
    int cha;

    while (1) {
        while (1) {
            cha = fgetc(file);
            if (cha == '\n') {
                if(col != 5) {
                    return 0;
                }
                col = 0;
                row++;
                break;
            }
            col++;
        }
        if (row == 5) {
            cha = fgetc(file);
            row = 0;
            if (cha != '\n' && cha != EOF) {
                return 0;
            }
            if (cha == EOF) {
                if (col != 0) {
                    return 0;
                }
                break;
            }
        }
    }

    return 1;
}

/*
 * Checks each of the parameters in the save file 
 * meet with the spec requirements
 */
int validate_save_file(char* fileName) {
    FILE* saveFile = fopen(fileName, "r");
    int lenCount = 0;
    int cha;
    char params[4][70];
    int widthCount = 0;
    int heightCount = 0;
    return save_file_params(saveFile);
    rewind(saveFile);
    for (int i = 0; i < 4; i++) {
        while (1) {
            cha = fgetc(saveFile);
            if (cha == ' ' || cha == '\n') {
                params[i][lenCount + 1] = '\0';
                break;
            }
            params[i][lenCount] = cha;
            lenCount++;
        }
        lenCount = 0;
    }
    while (1) {
        while (1) {
            cha = fgetc(saveFile);
            if (cha != '.' && cha != '*' && cha != '#' && cha != '\n'
		    && cha != EOF) {
                return 0;
            }
            if (cha == '\n' || cha == EOF) {
                if (widthCount != atoi(params[3]) && cha != '\n' 
			&& cha != EOF) {
		    return 0;
                }
                widthCount = 0;
                break;
            }
            widthCount++;
        }
        if (cha == EOF) {
            if (heightCount != atoi(params[2])) { 
                return 0;
            }
            break;
        }
        heightCount++;
    }
    return 1;
}

/*
 * Counts parameters of saveFile.
 * Should be 4.
 */
int save_file_params(FILE* saveFile) {
    int paramCount;
    int cha;
    while(1) {
	cha = fgetc(saveFile);
	if (cha == '\n') {
	    paramCount += 1;
	    break;
	} else if (cha == ' ') {
	    paramCount += 1;
	} else if (!isdigit(cha)) {
	    return 0;
	}
    }
    if (paramCount != 4) {
        return 0;
    }
    return 1;
}
