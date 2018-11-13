#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "tileAndGameData.h"
#include "startProgramValidation.h"
#include "tilesAndBoard.h"
#include "gameInput.h"
#include "fitz.h"

//Plays game or displays tile file depeding on user input.
int main(int argc, char** argv) {
    int inputResult = check_user_input(argc, argv);

    if (inputResult) {
        return process_user_invocation(inputResult);
    }
    if (argc == 2) {
        int tileNum = tile_counter(argv[1]);
        Tile tilesToPrint[tileNum];
        load_tile_file(argv[1], tileNum, tilesToPrint);
        print_tile_file(tilesToPrint, tileNum);
    }
    if (argc == 6) {
        new_game(argv[1], argv[2], argv[3], argv[4], argv[5]);
    } else if(argc == 5) {
        char** args = malloc(sizeof(char*) * 900);
        for (int i = 0; i < 70; ++i) {
            args[i] = malloc(sizeof(char) * 900);
        }
        load_save_file(argv[4], args);
        play_saved_game(args, argv[1], argv[2], argv[3]);
    }
    return 0;
}

/*
 * Depending on results of the invoking check, print appropriate message
 * to stderr, and return correct value.
 */
int process_user_invocation(int result) {
    if (result == INCORRECT_ARG_COUNT) {
        fprintf(stderr, "Usage: fitz tilefile "
		"[p1type p2type [height width | filename]]\n");
        return 1;
    }
    if (result == TILE_FILE_NULL) {
        fprintf(stderr, "Can't access tile file\n");
        return 2;
    }
    if (result == BAD_TILE_FILE) {
        fprintf(stderr, "Invalid tile file contents\n");
        return 3;
    }
    if (result == INVALID_PLAYER_TYPE) {
        fprintf(stderr, "Invalid player type\n");
        return 4;
    }
    if (result == INVALID_DIM) {
        fprintf(stderr, "Invalid dimensions\n");
        return 5;
    }
    if (result == SAVE_FILE_NULL) {
        fprintf(stderr, "Can't access save file\n");
        return 6;
    }
    if (result == BAD_SAVE_FILE) {
        fprintf(stderr, "Invalid save file contents\n");
        return 7;
    }
    return 0;
}

/*
 * Puts the current game's details into a file according to spec requirements.
 * Makes possible to load a saved game.
 */
void save_game(struct GameData gameData, char fileName[]) {
    FILE* file = fopen(fileName, "a");
    if (file == NULL) {
        fprintf(stderr, "Unable to save game\n");
        exit(1);
    }
    fprintf(file, "%d ", gameData.currentTile); 
    fprintf(file, "%d ", gameData.nextPlayer);
    fprintf(file, "%d ", gameData.height);
    fprintf(file, "%d\n", gameData.width);
    for (int row = 0; row < gameData.height; row++) {
        for (int col = 0; col < gameData.width; col++) {
            fprintf(file, "%c", gameData.board[row][col]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}  

/*
 * When instruction to load and play a saved game is called,
 * start it by calling this function.
 */
void play_saved_game(char** args, char* tileFile, char* p1Type, char* p2Type) {
    int noOfTiles = 0;
    int count = 0;
    struct GameData gameData;
    gameData.p1Type = *p1Type;
    gameData.p2Type = *p2Type;
    gameData.nextPlayer = atoi(args[1]);
    gameData.currentTile = atoi(args[0]);
    gameData.height = atoi(args[2]);
    gameData.width = atoi(args[3]);
    char** board = malloc(sizeof(char*) * (gameData.height));
    for (int i = 0; i < gameData.height; ++i) {
	board[i] = malloc(sizeof(char) * gameData.width);
    }
    for (int i = 0; i < gameData.height; i++) {
	for (int j = 0; j < gameData.width; j++) {
	    if (args[4][count] == '\n') {
		count++;
	    }
	    board[i][j] = args[i + 4][j];
	    count++;
	}
    }
    gameData.board = board;
    noOfTiles = tile_counter(tileFile);
    Tile tiles[noOfTiles];
    gameData.noOfTiles = noOfTiles;
    load_tile_file(tileFile, noOfTiles, tiles);
    play_game(gameData, tiles);
}
    
 
/*
 * Main game function. Continuously loops until user input breaks loop
 * or game ends.
 */
void play_game(struct GameData gameData, Tile tiles[]) {
    int* mostRecentMove = malloc(sizeof(int) * 2);
    mostRecentMove[0] = -2;
    mostRecentMove[1] = -2;
    int* mostRecentT2Move = malloc(sizeof(int) * 2);
    mostRecentT2Move[0] = -2;
    mostRecentT2Move[1] = -2;
    gameData.nextPlayer ^= 1;
    while(1) {
	gameData.nextPlayer ^= 1;
	if (!check_win_state2(gameData, tiles)) {
	    print_current_board(gameData);
	    if (gameData.nextPlayer == 1) {
		printf("Player * wins\n");
		break;
	    } else {
		printf("Player # wins\n");
		break;
	    }
	}
	print_current_board(gameData);
	if (gameData.nextPlayer == 0) {
	    if (gameData.p1Type == 'h') {
		print_tile(tiles[gameData.currentTile]);
		h_move(gameData, tiles, mostRecentMove);
		fflush(stdout);
	    } else if(gameData.p1Type == '1') {
		type_1_move(gameData, tiles, mostRecentMove);
	    } else if (gameData.p1Type == '2') {
		type_2_move(gameData, tiles,
			mostRecentT2Move, mostRecentMove);
	    }
	} else if (gameData.nextPlayer == 1) {
	    if (gameData.p2Type == 'h') {	
		print_tile(tiles[gameData.currentTile]);
		h_move(gameData, tiles, mostRecentMove);
		fflush(stdout);
	    } else if(gameData.p2Type == '1') {
		type_1_move(gameData, tiles, mostRecentMove);
	    } else if (gameData.p2Type == '2') {
		type_2_move(gameData, tiles, mostRecentT2Move, mostRecentMove);
	    }
	}

	if (gameData.currentTile == gameData.noOfTiles - 1) {
	    gameData.currentTile = 0;
	} else {
	    gameData.currentTile++;
	}
    }
}

/*
 * Human move function. 
 * Asks for input, checks input.
 * Place a tile or save game.
 */
void h_move(struct GameData gameData, Tile tiles[], int mostRecentMove[]) {
    char input[70];
    Tile tileBeingPlaced;
    int* sizeOfInput = malloc(sizeof(int) * 3);
    while (1) {
	if (gameData.nextPlayer == 0) {
	    printf("Player *] ");
   	} else {
	    printf("Player #] ");
   	}
    	if(fgets(input, 70, stdin) == NULL) {
	    fprintf(stderr, "End of input\n");
	    exit(10);
	}
	if (!is_input_valid(input)) {
	    continue;
	}
	if (is_input_valid(input) == 2) {
	    char* saveFile = malloc(sizeof(char) * 70);
	    parse_save_input(saveFile, input);
	    save_game(gameData, saveFile);
	    free(saveFile);
	}
	size_of_input(input, sizeOfInput);
	char* firstInput = malloc(sizeof(char) * 70);
	char* secondInput = malloc(sizeof(char) * 70);
	char* thirdInput = malloc(sizeof(char) * 70);
	memset(firstInput, '\0', 70);
	memset(firstInput, '\0', 70);
	memset(firstInput, '\0', 70);
	parse_input(input, sizeOfInput, firstInput, secondInput, thirdInput);
	tileBeingPlaced = rotate_tile(tiles, gameData.currentTile, 
		atoi(thirdInput));
	if (!is_move_valid(gameData, tileBeingPlaced, atoi(firstInput),
		atoi(secondInput))) {
	    continue;
	}
	place_tile(gameData, tileBeingPlaced, atoi(firstInput),
		atoi(secondInput));
	tileBeingPlaced = clear_tile(tileBeingPlaced);
    	mostRecentMove[0] = atoi(firstInput);
	mostRecentMove[1] = atoi(secondInput);
    	free(firstInput);
	free(secondInput);
	free(sizeOfInput);
	break;
    }
}

/*
 * Automatic move based on player of type 1.
 */
void type_1_move(struct GameData gameData, Tile tiles[], 
	int mostRecentMove[]) {
    int r = mostRecentMove[0];
    int c = mostRecentMove[1];
    int angle = 0;
    Tile tile;
    for (int i = 0; i < 4; i++) {
	tile = rotate_tile(tiles, gameData.currentTile, angle);
	while (1) {
	    if (is_move_valid(gameData, tile, r, c)) {
		if (gameData.nextPlayer == 0) {
		    printf("Player * => %d %d rotated %d\n", r, c, angle);
		} else if (gameData.nextPlayer == 1) {
		    printf("Player # => %d %d rotated %d\n", r, c, angle);
		}
		place_tile(gameData, tile, r, c);
		mostRecentMove[0] = r;
		mostRecentMove[1] = c;
		return;
	    }
	    c++;
	    if (c > (gameData.width + 1)) {
		c = -2;
		r++;
	    }
	    if (r > (gameData.height + 1)) {
		r = -2;
	    }
	    if (r == mostRecentMove[0] && c == mostRecentMove[1]) {
		break;
	    }
	}
	angle += 90;
    }

}

/*
 * Automatic move based on player of type 2.
 */
void type_2_move(struct GameData gameData, Tile tiles[],
	int mostRecentT2Move[], int mostRecentMove[]) {
    int r = mostRecentT2Move[0];
    int c = mostRecentT2Move[1];    
    int angle;
    Tile tile;
    while (1) {
	angle = 0;
	for (int i = 0; i < 4; i++) {
	    tile = rotate_tile(tiles, gameData.currentTile, angle);
	    if (is_move_valid(gameData, tile, r, c)) {
		if (gameData.nextPlayer == 1) {
		    printf("Player # => %d %d rotated %d\n", r, c, angle);
		} else {
		    printf("Player * => %d %d rotated %d\n", r, c, angle);
		}
		place_tile(gameData, tile, r, c);
		mostRecentMove[0] = r;
		mostRecentMove[1] = c;
		mostRecentT2Move[0] = r;
		mostRecentT2Move[1] = c;
		return;
	    }
	    angle += 90;
	}
	if (gameData.nextPlayer == 0) {
	    c++;
	    if (c > gameData.width + 2) {
		c = -2;
		r++;
	    }
	    if (r > gameData.height + 2) {
		r = -2;
	    }
	    if (r == mostRecentT2Move[0] && c == mostRecentT2Move[1]) {
		break;
	    }
	} else {
	    c--;
	    if (c < -2) {
		c = gameData.width + 2;
		r--;
	    }
	    if (r < -2) {
		r = gameData.height + 2;
	    }
	    if (r == mostRecentT2Move[0] && c == mostRecentT2Move[1]) {
		break;
	    }
	}			
    }
}

/*
 * Inisialises new game and plays it.
 */
void new_game(char tileFile[], char p1Type[], char p2Type[], 
	char height[], char width[]) {
    int noOfTiles = 0;
    struct GameData gameData;
    gameData.p1Type = *p1Type;
    gameData.p2Type = *p2Type;
    gameData.nextPlayer = 0;
    gameData.currentTile = 0;
    gameData.height = atoi(height);
    gameData.width = atoi(width);
    char** board = malloc(sizeof(char*) * (atoi(height)));
    for (int i = 0; i < atoi(height); ++i) {
	board[i] = malloc(sizeof(char) * (atoi(width)));
    }
    make_new_board(board, atoi(height), atoi(width));
    gameData.board = board;
    noOfTiles = tile_counter(tileFile);
    Tile tiles[noOfTiles];
    gameData.noOfTiles = noOfTiles;
    load_tile_file(tileFile, noOfTiles, tiles);
    play_game(gameData, tiles);
}


/*
 * Checks if the next tile to be played can be placed or not.
 * i.e. checks if board is in a win state.
 */
int check_win_state2(struct GameData gameData, Tile tiles[]) {
    int angle = 0;
    Tile tileBeingTested;
    for (int rot = 0; rot < 4; rot++) {
	tileBeingTested = rotate_tile(tiles, gameData.currentTile, angle);
	for (int i = -2; i < gameData.height + 2; i++) {
	    for (int j = -2; j < gameData.width + 2; j++) {
		if (is_move_valid(gameData, tileBeingTested, i, j)) { 
		    return 1;
		}
	    }
	}
	angle += 90;
    }
    return 0;
}
