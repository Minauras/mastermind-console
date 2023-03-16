#include <stdio.h>

#define NTURNS 12

void draw_board(void);

int main(void) {
    draw_board();
    return 0;
}

void draw_board(void){
    printf("  ________________\r\n");

    for(int i = 0; i < NTURNS; i++){
        printf(" | . . . . | .... |\r\n");
    }

    printf(" |---------|------|\r\n");
    printf(" |*********|      |\r\n");
    printf(" |_________|______|\r\n");
}