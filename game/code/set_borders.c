#include "./header/header.c"

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
