#ifndef FITZ_3_C_STARTPROGRAMVALIDATION_H
#define FITZ_3_C_STARTPROGRAMVALIDATION_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int check_user_input(int argc, char** argv);
int validate_tile_file(char* fileName);
int validate_save_file(char* fileName);
int save_file_params(FILE* saveFile);


#endif //FITZ_3_C_STARTPROGRAMVALIDATION_H
