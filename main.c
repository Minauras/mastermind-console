#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NTURNS 12
#define NPEGS 4

int current_turn = -1;
bool game_ended = false;
char board[NTURNS][NPEGS];
char hints[NTURNS][NPEGS];
char solution[NPEGS];

void init_game(void);
void draw_board(void);
void draw_row(int turn);
void get_guess(void);
void flush_input(void);
void get_hints(void);
int compare_hints(const void * a, const void * b);

int main(void) {
    init_game();

    draw_board();

    for(current_turn = 0; current_turn < NTURNS; current_turn++){
        get_guess();
        get_hints();
        draw_board();
        if(game_ended) return 0;
    }

    game_ended = 1;
    draw_board();

    return 0;
}

void init_game(void){
    // Reset board and hints
    for(int i = 0; i < NTURNS; i++){
        for(int j = 0; j < NPEGS; j++){
            board[i][j] = '.';
            hints[i][j] = '.';
        }
    }

    // Choose random solution
    srand(time(NULL));
    for(int i = 0; i < NPEGS; i++){
        solution[i] = 'A' + (rand() % 6);
    }
}

void draw_board(void){
    system("cls");

    printf("MASTERMIND\r\n");
    printf("Find the code of 4 A-F letters\r\n");
    printf("\t* - correct letter in the correct place\r\n");
    printf("\tO - correct letter in the wrong place\r\n");
    printf("\t- - wrong letter\r\n");
    printf("The hints are not necessarily given in order\r\n");
    
    printf("  ________________\r\n");

    for(int i = 0; i < NTURNS; i++){
        draw_row(i);
    }

    printf(" |---------|------|\r\n");
    if(game_ended){
        printf(" |*%c*%c*%c*%c*|      |\r\n", solution[0], solution[1], solution[2], solution[3]);
    }
    else{
        printf(" |*********|      |\r\n");
    }
    printf(" |_________|______|\r\n");
}

void draw_row(int turn){
    if(turn == current_turn + 1) printf(">");
    else printf(" ");

    printf("| %c %c %c %c | %c%c%c%c |\r\n",
            board[turn][0], board[turn][1], board[turn][2], board[turn][3],
            hints[turn][0], hints[turn][1], hints[turn][2], hints[turn][3]);
}

void get_guess(void){
    int valid_input = 0;
    while(!valid_input){
        printf("Input your guess: ");
        
        valid_input = 1;
        // A valid input is 4 A-F characters
        if(scanf("%c%c%c%c", &board[current_turn][0], &board[current_turn][1], &board[current_turn][2], &board[current_turn][3]) == NPEGS){
            for(int i = 0; i < NPEGS; i++){
                if(board[current_turn][i] < 'A' || board[current_turn][i] > 'F'){
                    valid_input = 0;
                    break;
                }
            }
        }
        else{
            valid_input = 0;
        }
        flush_input();
    }
}

void flush_input(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void get_hints(void){
    char hints_ordered[NPEGS];
    bool board_checked[NPEGS] = {false};
    bool solution_checked[NPEGS] = {false};

    // Check correctness
    for(int i = 0; i < NPEGS; i++){
        if(board[current_turn][i] == solution[i]){
            hints_ordered[i] = '*';
            board_checked[i] = true;
            solution_checked[i] = true;
        }
    }

    // For those non-checked, check misplaced-ness
    for(int i = 0; i < NPEGS; i++){
        if(!board_checked[i]){
            for(int j = 0; j < NPEGS; j++){
                if(!solution_checked[j]){
                    if(board[current_turn][i] == solution[j]){
                        hints_ordered[i] = 'O';
                        board_checked[i] = true;
                        solution_checked[j] = true;
                        break;
                    }
                }
            }
        }
    }

    // For the remaining, state wrongness
    for(int i = 0; i < NPEGS; i++){
        if(!board_checked[i]){
            hints_ordered[i] = '-';
        }
    }

    // Right now the hints are ordered, so let's unorder them by sorting them by type
    qsort(hints_ordered, NPEGS, sizeof(char), compare_hints);

    // Finally, let's output the hints
    for(int i = 0; i < NPEGS; i++){
        hints[current_turn][i] = hints_ordered[i];
    }
}

int compare_hints(const void * a, const void * b){
    char x = *(char*) a;
    char y = *(char*) b;

    if(x == y)
        return 0;
    if(x == '*' || (x == 'O' && y == '-'))
        return -1;

    return 1;
}