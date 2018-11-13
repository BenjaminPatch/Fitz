CFLAGS = -Wall -pedantic -Wextra -Wundef -std=c99  -g
obj = $(src:.c=.o)
.PHONY: clean


.DEFAULT: all
all: fitz.o gameInput.o startProgramValidation.o tilesAndBoard.o fitz

debug: CFLAGS += -g

clean:
	rm -rf test

fitz.o:	fitz.c
	gcc $(CFLAGS) -c fitz.c -o fitz.o

gameInput.o: gameInput.c
	gcc $(CFLAGS) -c gameInput.c -o gameInput.o

startProgramValidation.o: startProgramValidation.c
	gcc $(CFLAGS) -c startProgramValidation.c -o startProgramValidation.o

tilesAndBoard.o: tilesAndBoard.c
	gcc $(CFLAGS) -c tilesAndBoard.c -o tilesAndBoard.o

fitz: tilesAndBoard.o startProgramValidation.o gameInput.o fitz.o
	gcc $(CFLAGS) -o fitz fitz.o gameInput.o startProgramValidation.o tilesAndBoard.o

clean:
	rm -f *.o

