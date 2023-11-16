#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

#define ESC_KEY 27
#define START_GAME_KEY 49
#define INSTRUCTIONS_KEY 50
#define CREDITS_KEY 51
#define HARD_MODE_KEY 100
#define MEDIUM_MODE_KEY 109
#define EASY_MODE_KEY 102

#define ARROW_UP_KEY 72
#define ARROW_DOWN_KEY 80
#define ARROW_LEFT_KEY 75
#define ARROW_RIGHT_KEY 77

#define COLS 49
#define ROWS 11

#define LAB_COLS 41
#define LAB_ROWS 9

#define STARTING_X 3
#define STARTING_Y ROWS / 2

#define WALL 219 // player cannot go through walls
#define ____ 32 // this is used as "whitespace" in the screen, the area where the player can move into
#define WON 197 // if players reach this tile they win the game
#define WON_CHARACTER -59 // for some reason the won character above gets detected as this character when on the screen
#define PLAYER 79 // represents the player

char screen[ROWS][COLS];

typedef enum {
	FALSE,
	TRUE
} bool;

typedef struct {
	int x, y;
} position_t;

void finish_game() {
	system("cls");
	printf("Tchau!\n");
	exit(0);
}

void instructions() {
	system("cls");

	printf("|----------------------------------------------------------------|\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|  INSTRUÇÕES                                                    |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|  Use o teclado para movimentar o jogador                       |\n");
	printf("|  Seu objetivo é levar o jogador ao final do                    |\n");
	printf("|  labirinto antes que o tempo acabe.                            |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|----------------------------------------------------------------|\n");
	printf("|        Aperte qualquer tecla para voltar ao menu               |\n");
	printf("|----------------------------------------------------------------|\n");

	_getch();
	return;
}

void credits() {
	system("cls");

	printf("|----------------------------------------------------------------|\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|  CRÉDITOS                                                      |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|  Ana Clara Coquelete Lemos e Silva  23018086-2                 |\n");
	printf("|  Fábio Augusto Romanini             23000510-2                 |\n");
	printf("|  Matheus Bolonhini Costa            23016374-2                 |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|                                                                |\n");
	printf("|----------------------------------------------------------------|\n");
	printf("|        Aperte qualquer tecla para voltar ao menu               |\n");
	printf("|----------------------------------------------------------------|\n");

	_getch();
	return;
}

void menu() {
	int option;
	while (TRUE) {
		system("cls");
		printf("|----------------------------------------------------------------|\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("| ESCAPE DO LABIRINTO                                            |\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|----------------------------------------------------------------|\n");	
		printf("|                                                                |\n");
		printf("|  1 - Jogar                                                     |\n");
		printf("|  2 - Instruções                                                |\n");
		printf("|  3 - Créditos                                                  |\n");
		printf("|                                                                |\n");
		printf("|----------------------------------------------------------------|\n");
		printf("|        Aperte qualquer esc para sair                           |\n");
		printf("|----------------------------------------------------------------|\n");
		option = _getch();

		switch (option) {
			case START_GAME_KEY:
				return;
			case INSTRUCTIONS_KEY:
				instructions();
				break;
			case ESC_KEY:
				finish_game();
			case CREDITS_KEY:
				credits();
		}
	}
}

typedef enum DIFFICULTY {
	EASY,
	MEDIUM,
	HARD
} difficulty_t;

difficulty_t difficulty_selection() {
	int option;
	while (TRUE) {
		system("cls");
		printf("|----------------------------------------------------------------|\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|  NÍVEL DE DIFICULDADE                                          |\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|                                                                |\n");
		printf("|  F - Fácil                                                     |\n");
		printf("|  M - Médio                                                     |\n");
		printf("|  D - Difícil                                                   |\n");
		printf("|                                                                |\n");
		printf("|----------------------------------------------------------------|\n");
		printf("|                   Aperte esc para sair                         |\n");
		printf("|----------------------------------------------------------------|\n");
		option = _getch();
		switch (option) {
			case EASY_MODE_KEY:
				return EASY;
			case MEDIUM_MODE_KEY:
				return MEDIUM;
			case HARD_MODE_KEY:
				return HARD;
		}
	}
}

// how to generate new labirinths:
// https://www.dcode.fr/maze-generator
// 20 x 5
// remove upper and lower walls, since the screen is already boxed
void populate_labirinth(difficulty_t difficulty) {
	char hard[LAB_ROWS][LAB_COLS] = {
		{____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,WALL,____,WALL,____,____,____,____,____,____,____,WALL,____,WALL,____,WALL,____,____,____,____,____,____,____,WALL},
		{WALL,WALL,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL},
		{WALL,____,WALL,____,WALL,____,WALL,____,____,____,____,____,____,____,WALL,____,WALL,____,WALL,____,____,____,____,____,WALL,____,WALL,____,WALL,____,____,____,____,____,WALL,____,____,____,WALL,____,WALL},
		{WALL,____,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,____,WALL},
		{WALL,____,WALL,____,____,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,WALL},
		{WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL},
		{WALL,____,WALL,____,WALL,____,____,____,WALL,____,____,____,____,____,____,____,WALL,____,WALL,____,____,____,WALL,____,WALL,____,____,____,WALL,____,WALL,____,WALL,____,____,____,WALL,____,WALL,____,WALL},
		{WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL},
		{WALL,____,____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,WALL,____,____,____,____,____,WALL,____,____,WON ,WALL}
	};
	
	char easy[LAB_ROWS][LAB_COLS] = {
		{ ____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,WALL,____,____,____,____,____,WALL,____,WALL,____,WALL,____,____,____,WALL,____,____,____,____,____,____,____,____,____,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,WALL,____,WALL,WALL,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,____,____,____,____,WALL,____,WALL,____,____,____,____,____,WALL,____,____,____,____,____,____,____,WALL,____,WALL,____,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,WALL,____,____,____,WALL,____,____,____,WALL,____,WALL,____,____,____,WALL,____,WALL,____,____,____,____,____,WALL,____,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,WALL,WALL,____,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,WALL,____,____,____,WALL,____,____,____,WALL,____,____,____,WALL,____,____,____,____,____,____,____,____,____,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL},
		{ ____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,WALL,____,WALL,____,WALL,____,____,____,____,____,WON }
	};
		
	char medium[LAB_ROWS][LAB_COLS] = {
		{____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,____,____,____,____,WALL,____,WALL,____,____,____,WALL,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,WALL},
		{____,____,____,____,____,____,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL},
		{____,____,____,____,____,____,WALL,WALL,WALL,____,____,____,WALL,____,WALL,____,____,____,____,____,____,____,WALL,____,____,____,____,____,____,____,WALL,____,____,____,WALL,____,WALL,____,____,____,WALL},
		{____,____,____,____,____,____,WALL,____,WALL,WALL,WALL,____,____,____,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL},
		{____,____,____,____,____,____,____,____,____,____,WALL,WALL,WALL,WALL,WALL,____,____,____,WALL,____,____,____,____,____,WALL,____,WALL,____,____,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL},
		{____,____,____,____,____,____,WALL,WALL,WALL,____,WALL,____,____,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL},
		{____,____,____,____,____,____,WALL,____,WALL,____,WALL,____,WALL,____,____,____,WALL,____,____,____,WALL,____,____,____,WALL,____,WALL,____,WALL,____,WALL,____,WALL,____,____,____,____,____,____,____,WALL},
		{____,____,____,____,____,____,WALL,____,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,WALL,WALL,____,WALL,____,WALL,____,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL,WALL,WALL,____,WALL},
		{____,____,____,____,____,____,____,____,____,____,____,____,WALL,____,WALL,____,WALL,____,____,____,____,____,WALL,____,____,____,____,____,____,____,WALL,____,____,____,____,____,____,____,WALL,____,WON }
	};
	
	int x, y;
	char (*selected_lab)[LAB_COLS];  // Pointer to an array of LAB_COLS chars

    switch (difficulty) {
        case EASY:
            selected_lab = easy;
            break;
        case MEDIUM:
            selected_lab = medium;
            break;
        case HARD:
            selected_lab = hard;
            break;
    }

    for (y = 0; y < LAB_ROWS; y++) {
        // Use memcpy to copy the entire row
        memcpy(&screen[1 + y][8], selected_lab[y], LAB_COLS);
    }
}

// draws the boxing around the screen
void populate_screen() {
	int x, y;
	for (x = 0; x < COLS; x++) {
   		screen[0][x] = WALL;
	}
    for (y = 1; y < ROWS-1; y++) {
    	screen[y][0] = WALL;
    	screen[y][1] = WALL;
    	for (x = 2; x < COLS-2; x++) {
    		screen[y][x] = ____;
		}
    	screen[y][COLS-1] = WALL;
    	screen[y][COLS-2] = WALL;
	}
	
	for (x = 0; x < COLS; x++) {
   		screen[ROWS-1][x] = WALL;
	}
}

bool won(int y, int x) {
//	return TRUE;
	return screen[y][x] == WON_CHARACTER;
}

// decides if a given tile is playabe
bool blank_or_won(int y, int x) {
	return screen[y][x] == ____ || won(y, x);
}

// decides if the command inputed by the player is valid,
// given the player current position
bool valid_movement(int movement, position_t *player) {
	switch (movement) {
		case ARROW_UP_KEY:
			return player->y > 1 && blank_or_won(player->y-1, player->x);
		case ARROW_DOWN_KEY:
			return player->y < ROWS-2 && blank_or_won(player->y+1, player->x);
		case ARROW_LEFT_KEY:
			return player->x > 2 && blank_or_won(player->y, player->x-1);
		case ARROW_RIGHT_KEY:
			return player->y < COLS-3 && blank_or_won(player->y, player->x+1);
	}
}

void move_up(position_t *player) {
	screen[player->y][player->x] = ____;
	player->y = player->y-1;
	if (won(player->y, player->x)) return;
	screen[player->y][player->x] = PLAYER;
}

void move_down(position_t *player) {
	screen[player->y][player->x] = ____;
	player->y = player->y+1;
	if (won(player->y, player->x)) return;
	screen[player->y][player->x] = PLAYER;
}

void move_left(position_t *player) {
	screen[player->y][player->x] = ____;
	player->x = player->x-1;
	if (won(player->y, player->x)) return;
	screen[player->y][player->x] = PLAYER;
}

void move_right(position_t *player) {
	screen[player->y][player->x] = ____;
	player->x = player->x+1;
	if (won(player->y, player->x)) return;
	screen[player->y][player->x] = PLAYER;
}

int calculate_points(int steps, difficulty_t diff) {
	int bonus_from_steps = 0;
    switch (diff) {
        case EASY:
            bonus_from_steps = (98)  > steps ? 
            	(int) ((1 - ((double) steps / 98)) * 485)
				: 0;
            break;
        case MEDIUM:
            bonus_from_steps = (91)  > steps ? 
            	(int) ((1 - ((double) steps / 91)) * 485)
				: 0;
            break;
        case HARD:
            bonus_from_steps = (97)  > steps ? 
            	(int) ((1 - ((double) steps / 97)) * 485)
				: 0;
            break;
    } 

	return ((int) diff * 100) + bonus_from_steps;
}

int main () {
	setlocale(LC_ALL, "Portuguese");

	while (TRUE) {
		
		menu();
		
		difficulty_t diff = difficulty_selection();
		
		populate_screen();
		populate_labirinth(diff);
		
		position_t player;
		player.y = STARTING_Y;
		player.x = STARTING_X;
		
		screen[STARTING_Y][STARTING_X] = PLAYER;
		
		int steps = 0; 
			
	    while (TRUE) {
			
			int ch; // used by _getch
			int x, y;
			system("cls");
			
			// prints current screen
			setlocale(LC_ALL, "C");
		    for (y = 0; y < ROWS; y++) {
		    	for (x = 0; x < COLS; x++) {
		    		printf("%c", screen[y][x]);
				}
				printf("\n");
				
			}
			setlocale(LC_ALL, "Portuguese");
			
			printf("\nPassos: %d", steps);
	
			printf("\n\n\nDigite esc para voltar ao menu principal.");
	
			if (_getch() == ESC_KEY) break;
			
			if (ch == 0 || ch == 224) {
	        	int extra = _getch ();
				if (extra == ARROW_UP_KEY && valid_movement(ARROW_UP_KEY, &player)) {
					move_up(&player);
				}
				if (extra == ARROW_DOWN_KEY && valid_movement(ARROW_DOWN_KEY, &player)) {
					move_down(&player);
				}
				if (extra == ARROW_LEFT_KEY && valid_movement(ARROW_LEFT_KEY, &player)) {
					move_left(&player);
				}
				if (extra == ARROW_RIGHT_KEY && valid_movement(ARROW_RIGHT_KEY, &player)) {
					move_right(&player);
				}
			}
	
			if (won(player.y, player.x)) {
				system("cls");
	    		printf("Você ganhou!\n");
	    		printf("Pontos: %d\n", calculate_points(steps, diff));
	    		sleep(1);
	    		break;
			}
			steps++;
	    }   
	}
}
