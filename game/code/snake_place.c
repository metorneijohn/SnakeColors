#include "../header/header.h"


void snake_place(snake *snake1, snake_pos *pos1)
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
