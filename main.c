#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void print_field(int ballX, int ballY, int first_racket, int second_racket, int first_player_point, int second_player_point);
void move_ball(int* ballX, int* ballY, int* direction);
void check_ball(int* ballX, int* ballY, int first_racket, int second_racket, int* first_player_point, int* second_player_point, int* direction);
void move_racket(int* first_racket, int* second_racket);

int main() {
    int ballX = 40;
    int ballY = 12;

    int first_racket = 12;
    int second_racket = 12;

    int first_player_point = 0;
    int second_player_point = 0;

    int direction = 2;

    while (first_player_point < 5 && second_player_point < 5) {
        system("cls");
        print_field(ballX, ballY, first_racket, second_racket, first_player_point, second_player_point);
        move_racket(&first_racket, &second_racket);
        move_ball(&ballX, &ballY, &direction);
        check_ball(&ballX, &ballY, first_racket, second_racket, &first_player_point, &second_player_point, &direction);
        Sleep(50);
    }
    print_field(-1, -1, first_racket, second_racket, first_player_point, second_player_point);
    if (first_player_point == 1) {
        printf("Player 1 won!");
    } else {
        printf("Player 2 won!");
    }
    return 0;
}

void print_field(int ballX, int ballY, int first_racket, int second_racket, int first_player_point, int second_player_point) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if (i == ballY && j == ballX) {
                printf("*");
            } else if ((i == first_racket || i == first_racket + 1 || i == first_racket - 1) && j == 0) {
                printf("]");
            } else if ((i == second_racket || i == second_racket + 1 || i == second_racket - 1) && j == 79) {
                printf("[");
            } else if (i == 0 || i == 24) {
                printf("-");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\t\t     Player 1: %d\t\t  Player 2: %d", first_player_point, second_player_point);
    printf("\n\n");
}

void move_ball(int* ballX, int* ballY, int* direction) {
    if (*ballY == 1 && *direction == 1) {
        *direction = 3;
    } else if (*ballY == 1 && *direction == 2) {
        *direction = 4;
    } else if (*ballY == 23 && *direction == 3) {
        *direction = 1;
    } else if (*ballY == 23 && *direction == 4) {
        *direction = 2;
    }

    if (*direction == 1) {
        (*ballX)--;
        (*ballY)--;
    } else if (*direction == 2) {
        (*ballX)++;
        (*ballY)--;
    } else if (*direction == 3) {
        (*ballX)--;
        (*ballY)++;
    } else if (*direction == 4) {
        (*ballX)++;
        (*ballY)++;
    }
}

void check_ball(int* ballX, int* ballY, int first_racket, int second_racket, int* first_player_point, int* second_player_point, int* direction) {
    if ((*ballY == first_racket || *ballY == first_racket + 1 || *ballY == first_racket - 1) && *ballX == 1 && *direction == 1) {
        *direction = 2;
    } else if ((*ballY == first_racket || *ballY == first_racket + 1 || *ballY == first_racket - 1) && *ballX == 1 && *direction == 3) {
        *direction = 4;
    } else if ((*ballY == second_racket || *ballY == second_racket + 1 || *ballY == second_racket - 1) && *ballX == 78 && *direction == 2) {
        *direction = 1;
    } else if ((*ballY == second_racket || *ballY == second_racket + 1 || *ballY == second_racket - 1) && *ballX == 78 && *direction == 4) {
        *direction = 3;
    } else if (*ballX <= 0) {
        (*second_player_point)++;
        *ballX = 40;
        *ballY = 12;

        if (*direction == 2 || *direction == 4) {
            *direction = 3;
        } else if (*direction == 1 || *direction == 3) {
            *direction = 4;
        }
    } else if (*ballX >= 79) {
        (*first_player_point)++;
        *ballX = 40;
        *ballY = 12;

        if (*direction == 2 || *direction == 4) {
            *direction = 3;
        } else if (*direction == 1 || *direction == 3) {
            *direction = 4;
        }
    }
}

void move_racket(int* first_racket, int* second_racket) {
    if (_kbhit()) {
        switch(_getch()) {
            case 'a':
                if (*first_racket - 1 > 1) {
                    (*first_racket)--;
                }
                break;
            case 'z':
                if (*first_racket + 1 < 23) {
                    (*first_racket)++;
                }
                break;
            case 'k':
                if (*second_racket - 1 > 1) {
                    (*second_racket)--;
                }
                break;
            case 'm':
                if (*second_racket + 1 < 23) {
                    (*second_racket)++;
                }
                break;
            case 'q':
                system("cls");
                print_field(-1, -1, *first_racket, *second_racket, 0, 0);
                printf("Game over");
                exit(0);
        }
    }
}