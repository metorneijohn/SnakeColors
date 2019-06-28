#if !defined HEADER_H 
#define HEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>
#include <time.h>



#define vertical 30
#define horizontal 80
#define down 115
#define up 119
#define left 97
#define right 100
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define SOUND_PICK_UP      "aplay -r 44100 -q ~/Área de trabalho/game/audio/pickup.wav"
#define SOUND_GAME_OVER    "aplay -r 48000 -q ~/Área de trabalho/game/audio/gameover.wav"
int GLOBAL_MOVE = 0;


char snake_color[6][6]={ANSI_COLOR_BLUE,ANSI_COLOR_RED,ANSI_COLOR_GREEN,ANSI_COLOR_MAGENTA,ANSI_COLOR_CYAN,ANSI_COLOR_YELLOW};
int color_iterator=0;
void set_borders(void);

typedef struct Snake
{
    char symbol;
    int size;
    char direction;
    char prev_direction;
    int tail_X;
    int tail_Y;
    int head_X;
    int head_Y;
    int speed;

}snake;


typedef struct snake_pos
{
    int Y[vertical*horizontal];
    int X[vertical*horizontal];

}snake_pos;



typedef struct food
{
    int X;
    int Y;
    char symbol;

}food;



void snake_init(snake *snake1);
void food_init(food *food1);
void gotoxy(int,int);
void snake_place(snake *snake1, snake_pos *pos1);
void snake_move(snake *snake1, snake_pos *pos1, food *food1, int*);
void move_tail(snake *snake1, snake_pos *pos1);
void move_head(snake *snake1, snake_pos *pos1);
void food_print(food *food1);
int game_over(snake *snake1, snake_pos *pos1);
void print_game_over(void);
void set_borders();
void print_score(int*);
int kbhit(void);
void obstaculo_print();
void obstaculo_init();
int bateu_no_obstaculo(snake *snake1);
 int score=0;
int level=1;
food obstaculo[10];


#endif
