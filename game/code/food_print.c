#include "../header/header.h"

void food_print(food *food1)
{
    gotoxy(food1->X,food1->Y);                                  
    printf("%s",snake_color[(color_iterator+1)%7]);             
    printf("%c",food1->symbol);
    gotoxy(0,vertical+1);
    printf(ANSI_COLOR_RESET "SCORE=%d Level=%d",score, level);
    printf("%s",snake_color[color_iterator]);
}
