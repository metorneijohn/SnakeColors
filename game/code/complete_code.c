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

#define SOUND_PICK_UP      "aplay -r 44100 -q ~/Desktop/game/audio/pickup.wav"
#define SOUND_GAME_OVER    "aplay -r 48000 -q ~/Desktop/game/audio/gameover.wav"

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

int main()
{
     char option;
      int aux;
      srand(time(NULL));
      /* struct init */
    do{
      int gameover=0;
      snake snake1;
      snake1.speed = 150000;
      snake_pos pos1;
      food food1;
      snake_init(&snake1);
      food_init(&food1);


      /* set initial field */

      system("clear");
      system("stty -echo");
      system("tput civis");
      snake_place(&snake1,&pos1);
      set_borders();
      food_print(&food1);



      /* use system call to make terminal send all keystrokes directly to stdin */

      system ("/bin/stty raw");


      /* while snake not got collided into itself */

      while(!(game_over(&snake1,&pos1))&&(!(gameover)))
      {

          /* while key not pressed */

          while (!kbhit())
          {
                 usleep(snake1.speed);
                 snake_move(&snake1,&pos1,&food1,&score);
                 if(level>=2)
                   gameover=bateu_no_obstaculo(&snake1);
                 if (game_over(&snake1,&pos1)||(gameover))
                 {
                     system (SOUND_GAME_OVER);
                     break;
                 }

          }
          /* store previous direction and fetch a new one */

          snake1.prev_direction=snake1.direction;
          aux=getchar();
          if(aux == down || aux ==right || aux == up || aux == left ){
            if(level>=3)
             GLOBAL_MOVE++;
                if(GLOBAL_MOVE >= 5){
                    gotoxy(food1.X,food1.Y);
                    printf(" ");
                    GLOBAL_MOVE = 0;
                    food_init(&food1);
                    food_print(&food1);
        }
            snake1.direction=aux;
          }




     }
      /* use system call to set terminal behaviour to more normal behaviour */
      system ("/bin/stty cooked");
      system("stty echo");
      system("clear");

      print_game_over();
      printf("\n\n Final score: %d \n\n", score);

    printf("Deseja jogar novamente?[s/n]\n");
    scanf("%c", &option);
    score=0;
    level=1;
    GLOBAL_MOVE=0;
    }while(option != 'n');


      return 0;

}




void snake_init(snake *snake1)
{
    snake1->symbol='.';
    snake1->size=10;
    snake1->direction=right;
    snake1->prev_direction=right;
    snake1->tail_X=5;
    snake1->tail_Y=5;
    snake1->head_X=snake1->tail_X+snake1->size-1;
    snake1->head_Y=5;
}


void snake_place(snake *snake1, snake_pos *pos1)
{
    int i;
    for (i=0; i<snake1->size; ++i)
    {
        gotoxy(snake1->tail_X,snake1->tail_Y);
        printf("%c",snake1->symbol);
        pos1->X[i]=snake1->tail_X;
        pos1->Y[i]=snake1->tail_Y;
        snake1->tail_X+=1;
    }

}

void set_borders()
{
    int i;
    for (i=0; i<vertical; ++i)
    {
        gotoxy(0,i);
        printf("X");
        gotoxy(horizontal,i);
        printf("X");
    }

    for (i=0; i<horizontal; ++i)
        {
            gotoxy(i,0);
            printf("X");
            gotoxy(i,vertical);
            printf("X");
        }
}



void snake_move(snake *snake1, snake_pos *pos1, food *food1, int *score)
{
    move_head(snake1,pos1);

    if (!((snake1->head_X==food1->X) && (snake1->head_Y==food1->Y)))
    {
        move_tail(snake1,pos1);
    }
    else
    {

        snake1->size++;
        snake1->speed -= 2500;
        *score=*score+1;
        color_iterator = (color_iterator +1) % 7;
        system(SOUND_PICK_UP);
        if(*score>=10)
         level=2;
        if(*score>=20)
          level=3;
        if(level==2){
            obstaculo_init();
            obstaculo_print();
          }
        //do{
        food_init(food1);
        //}while(food1->X == horizontal || food1->Y == vertical || food1->X == 0 || food1->Y == 0);
        food_print(food1);
    }
}



void move_tail(snake *snake1, snake_pos *pos1)
{
    int i;

    // remove last cell of tail
    gotoxy(pos1->X[0],pos1->Y[0]);
    printf(" ");


    // update new tail position
    for (i=0; i<snake1->size; ++i)
    {
        pos1->X[i]=pos1->X[i+1];
        pos1->Y[i]=pos1->Y[i+1];
    }
}



void move_head(snake *snake1, snake_pos *pos1)
{
    switch (snake1->direction)
        {
            case right:
                if (snake1->prev_direction==left)
                {
                    snake1->head_X--;
                }else
                    snake1->head_X++;
                    break;

            case left:
                if (snake1->prev_direction==right)
                {
                    snake1->head_X++;
                }else
                    snake1->head_X--;
                    break;


            case up:
                if (snake1->prev_direction==down)
                {
                    snake1->head_Y++;
                }else
                    snake1->head_Y--;
                    break;


            case down:
                if (snake1->prev_direction==up)
                {
                    snake1->head_Y--;
                }else
                    snake1->head_Y++;
                    break;


            default:
                break;
        }


        // update tail position
        pos1->X[snake1->size]=snake1->head_X;
        pos1->Y[snake1->size]=snake1->head_Y;

        gotoxy(pos1->X[snake1->size],pos1->Y[snake1->size]);
        printf( "%s%c",snake_color[color_iterator],snake1->symbol);
}



void food_init(food *food1)
{
    do{
        food1->X=(rand()%(horizontal) + 1);
        food1->Y=(rand()%(vertical) + 1);
    }while(food1->X == horizontal || food1->Y == vertical || food1->X <= 1 || food1->Y <= 1);
    food1->symbol='O';

}


void food_print(food *food1)
{
    gotoxy(food1->X,food1->Y);
    printf("%s",snake_color[(color_iterator+1)%7]);
    printf("%c",food1->symbol);
    gotoxy(0,vertical+1);
    printf(ANSI_COLOR_RESET "SCORE=%d Level=%d",score, level);
    printf("%s",snake_color[color_iterator]);
}


void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}



int game_over(snake *snake1, snake_pos *pos1)
{
    int i;

    for (i=0; i<snake1->size-1; ++i)
    {
        if ((pos1->X[i]==snake1->head_X) && (pos1->Y[i]==snake1->head_Y))
        {
            return 1;
        }
    }


    if ((snake1->head_X==horizontal) || (snake1->head_X==1) || (snake1->head_Y==vertical) || (snake1->head_Y==1))
        {
            return 1;
        }


    return 0;
}



int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);


    ch = getchar();




  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}


void obstaculo_init(){

      do{

          obstaculo[score-10].X=(rand()%(horizontal) + 1);
          obstaculo[score-10].Y=(rand()%(vertical) + 1);
      }while(obstaculo[score-10].X == horizontal || obstaculo[score-10].Y == vertical || obstaculo[score-10].X <= 2 || obstaculo[score-10].Y <= 2);
      obstaculo[score-10].symbol='8';

}
void obstaculo_print(){

  gotoxy(obstaculo[score-10].X,obstaculo[score-10].Y);
  printf("%c",obstaculo[score-10].symbol);
}

int bateu_no_obstaculo(snake * snake1){
  for(int i=0;i<10;i++){
    if (((snake1->head_X==obstaculo[i].X) && (snake1->head_Y==obstaculo[i].Y)))
    return 1;
  }
  return 0;
}


void print_game_over(){
    char matriz_G[7][7]={
    {' ','P','P','P','P','P','P'},
    {' ','P',' ',' ',' ',' ',' '},
    {' ','P',' ',' ',' ',' ',' '},
    {' ','P',' ',' ','P','P','P'},
    {' ','P',' ',' ',' ',' ','P'},
    {' ','P',' ',' ',' ',' ','P'},
    {' ','P','P','P','P','P','P'}
};
        char matriz_A[7][7]={
    {' ','A','A','A','A','A','A'},
    {' ','A',' ',' ',' ',' ','A'},
    {' ','A',' ',' ',' ',' ','A'},
    {' ','A','A','A','A','A','A'},
    {' ','A',' ',' ',' ',' ','A'},
    {' ','A',' ',' ',' ',' ','A'},
    {' ','A',' ',' ',' ',' ','A'}
};
           char matriz_M[7][7]={
    {'T','T','T','T','T','T','T'},
    {'T',' ',' ','T',' ',' ','T'},
    {'T',' ',' ','T',' ',' ','T'},
    {'T',' ',' ','T',' ',' ','T'},
    {'T',' ',' ','T',' ',' ','T'},
    {'T',' ',' ','T',' ',' ','T'},
    {'T',' ',' ','T',' ',' ','T'}
};
        char matriz_E[7][7]={
    {' ','A','A','A','A','A','A'},
    {' ','A','A',' ',' ',' ',' '},
    {' ','A','A',' ',' ',' ',' '},
    {' ','A','A','A','A','A','A'},
    {' ','A','A',' ',' ',' ',' '},
    {' ','A','A',' ',' ',' ',' '},
    {' ','A','A','A','A','A','A'}
};
    char matriz_O[7][7]={
    {' ','A','A','A','A','A',' '},
    {' ','A',' ',' ',' ','A',' '},
    {' ','A',' ',' ',' ','A',' '},
    {' ','A',' ',' ',' ','A',' '},
    {' ','A',' ',' ',' ','A',' '},
    {' ','A',' ',' ',' ','A',' '},
    {' ','A','A','A','A','A',' '}
};
    char matriz_V[7][7]={
    {'T',' ',' ',' ',' ',' ','T'},
    {'T',' ',' ',' ',' ',' ','T'},
    {' ','T',' ',' ',' ','T',' '},
    {' ','T',' ',' ',' ','T',' '},
    {' ','T',' ',' ',' ','T',' '},
    {' ',' ','T',' ','T',' ',' '},
    {' ',' ',' ','T',' ',' ',' '}
};
    char matriz_R[7][7]={
    {' ','P','P','P','P','P',' '},
    {' ','P',' ',' ',' ','P',' '},
    {' ','P',' ',' ',' ','P',' '},
    {' ','P','P','P','P',' ',' '},
    {' ','P',' ','P',' ',' ',' '},
    {' ','P',' ',' ','P',' ',' '},
    {' ','P',' ',' ',' ','P',' '}
};

    for(int i=0;i<7;i++){
       for(int j=0;j<7;j++){
           printf("%c",matriz_G[i][j]);
       }
           printf("\n");
      }

    for(int i=0;i<7;i++){
        gotoxy(9,i+1);
       for(int j=0;j<7;j++){
           printf("%c",matriz_A[i][j]);
       }

      }
        for(int i=0;i<7;i++){
        gotoxy(18,i+1);
       for(int j=0;j<7;j++){
           printf("%c",matriz_M[i][j]);
       }

      }
          for(int i=0;i<7;i++){
        gotoxy(27,i+1);
       for(int j=0;j<7;j++){
           printf("%c",matriz_E[i][j]);
       }

      }
      for(int i=0;i<7;i++){
        gotoxy(27+9,i+1);
       for(int j=0;j<7;j++){
           printf("%c",matriz_O[i][j]);
       }
      }
      for(int i=0;i<7;i++){
        gotoxy(27+18,i+1);
       for(int j=0;j<7;j++){
           printf("%c",matriz_V[i][j]);
       }
      }
      for(int i=0;i<7;i++){
        gotoxy(27+27,i+1);
       for(int j=0;j<7;j++){
           printf("%c",matriz_E[i][j]);
       }
      }
      for(int i=0;i<7;i++){
        gotoxy(27+36,i+1);
       for(int j=0;j<7;j++){
           printf("%c",matriz_R[i][j]);
       }

      }
}
