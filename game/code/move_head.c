#include "../header/heander.h"

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
