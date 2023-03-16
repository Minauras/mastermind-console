#include <stdio.h>
#include <stdbool.h>

#define NTURNS 12
#define NPEGS 4

int current_turn = 0;
char board[NTURNS][NPEGS];
char hints[NTURNS][NPEGS];

void init_game(void);
void draw_board(void);
void draw_row(bool current);

int main(void) {
    init_game();

    draw_board();
    return 0;
}

void init_game(void){
    for(int i = 0; i < NTURNS; i++){
        for(int j = 0; j < NPEGS; j++){
            board[i][j] = '.';
            hints[i][j] = '.';
        }
    }
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