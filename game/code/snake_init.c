#include "../header/header.h"

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

