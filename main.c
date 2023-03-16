#include <stdio.h>
#include <stdbool.h>

#define NTURNS 12
#define NPEGS 4

int current_turn = 0;
char board[NTURNS][NPEGS];
char hints[NTURNS][NPEGS];

void init_game(void);
void draw_board(void);
void draw_row(int turn);

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
        draw_row(i);
    }

    printf(" |---------|------|\r\n");
    printf(" |*********|      |\r\n");
    printf(" |_________|______|\r\n");
}

void draw_row(int turn){
    if(turn == current_turn) printf(">");
    else printf(" ");

    printf("| %c %c %c %c | %c%c%c%c |\r\n",
            board[turn][0], board[turn][1], board[turn][2], board[turn][3],
            hints[turn][0], hints[turn][1], hints[turn][2], hints[turn][3]);
}