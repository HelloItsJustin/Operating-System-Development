#include <arch/i686/vga_text.h>
#include <stdint.h>
#include "stdio.h"
#include "string.h"      // ✅ your custom kernel string.h
#include <stdbool.h>

extern char getchr();

char board[3][3];
char currentPlayer = 'X';

void draw_board() {
    VGA_clrscr();
    printf("Tic Tac Toe (Player vs Player)\n\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            char cell = board[row][col];
            printf(" %c ", cell ? cell : ' ');
            if (col < 2) printf("|");
        }
        printf("\n");
        if (row < 2) printf("---+---+---\n");
    }
}

bool check_win(char player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;
    return false;
}

bool is_full() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (!board[r][c]) return false;
    return true;
}

int get_digit_input(const char* prompt) {
    while (true) {
        printf("%s", prompt);
        char ch = 0;
        while ((ch = getchr()) == 0);  // wait for valid input

        if (ch >= '1' && ch <= '3') {
            putc(ch);  // echo the char
            return ch - '1';  // convert to 0-indexed
        }

        printf("\nInvalid input. Please enter 1-3.\n");
    }
}

void prompt_move() {
    int row = -1, col = -1;

    while (true) {
        printf("\n\nPlayer %c's turn\n", currentPlayer);
        row = get_digit_input("Enter row (1-3): ");
        col = get_digit_input("\nEnter col (1-3): ");

        if (board[row][col] == 0) {
            board[row][col] = currentPlayer;
            break;
        }

        printf("\n\nCell already occupied. Try again.\n");
    }
}

void tic_tac_toe_main() {
    memset(board, 0, sizeof(board));
    currentPlayer = 'X';

    while (true) {
        draw_board();
        prompt_move();

        if (check_win(currentPlayer)) {
            draw_board();
            printf("\nPlayer %c wins!\n", currentPlayer);
            break;
        }

        if (is_full()) {
            draw_board();
            printf("\nIt's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printf("\n\nPress any key to exit...");
    while (!getchr());  // wait for any key
}