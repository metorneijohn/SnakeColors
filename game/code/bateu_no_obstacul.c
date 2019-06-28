#include "../header/header.h"

int bateu_no_obstaculo(snake * snake1){
  for(int i=0;i<10;i++){
    if (((snake1->head_X==obstaculo[i].X) && (snake1->head_Y==obstaculo[i].Y)))
    return 1;
  }
  return 0;
}
