#include <stdio.h>
#include <stdbool.h>

#define NTURNS 12

int current_turn = 0;

void draw_board(void);
void draw_row(bool current);

int main(void) {
    draw_board();
    return 0;
}

void draw_board(void){
    printf("  ________________\r\n");

    for(int i = 0; i < NTURNS; i++){
        draw_row(i == current_turn);
    }

    printf(" |---------|------|\r\n");
    printf(" |*********|      |\r\n");
    printf(" |_________|______|\r\n");
}

void draw_row(bool current){
    if(current) printf(">");
    else printf(" ");

    printf("| . . . . | .... |\r\n");
}