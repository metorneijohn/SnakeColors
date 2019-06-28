#include "../header/header.h"

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
