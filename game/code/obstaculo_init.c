#include "../header/header.h"


void obstaculo_init(){

      do{

          obstaculo[score-10].X=(rand()%(horizontal) + 1);  
          obstaculo[score-10].Y=(rand()%(vertical) + 1);    
      }while(obstaculo[score-10].X == horizontal || obstaculo[score-10].Y == vertical || obstaculo[score-10].X <= 2 || obstaculo[score-10].Y <= 2);
      obstaculo[score-10].symbol='8';   

}
