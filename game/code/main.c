#include "../header/header.h"

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
                     system(SOUND_GAME_OVER);
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
