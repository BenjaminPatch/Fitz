//
// Created by benpa on 17-Aug-18.
//

#ifndef FITZ_H_FITZ_H
#define FITZ_H_FITZ_H

int process_user_invocation(int result);
void new_game(char tileFile[], char p1Type[], char p2Type[],
              char height[], char width[]);
void h_move(struct GameData gameData, Tile tiles[], int mostRecentMove[]);
void type_1_move(struct GameData gameData, Tile tiles[], int mostRecentMove[]);
void type_2_move(struct GameData gameData, Tile tiles[],
                 int mostRecentT2Move[], int mostRecentMove[]);
int check_win_state(struct GameData gameData, Tile tiles[]);
int check_win_state2(struct GameData gameData, Tile tiles[]);
void save_game(struct GameData gameData, char fileName[]);
void play_game(struct GameData gameData, Tile tiles[]);
void play_saved_game(char** args, char* tileFile, char* p1Type, char* p2Type);

#endif //TILEANDGAMEDATA_H_FITZ_H
