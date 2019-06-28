#include "../header/header.c"

void food_init(food *food1)
{
    do{
        food1->X=(rand()%(horizontal) + 1);
        food1->Y=(rand()%(vertical) + 1);
    }while(food1->X == horizontal || food1->Y == vertical || food1->X <= 1 || food1->Y <= 1); 
    food1->symbol='O';

}
