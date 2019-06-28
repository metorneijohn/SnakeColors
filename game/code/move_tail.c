#include "../heander/heander.h"


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
