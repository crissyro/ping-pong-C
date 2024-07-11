#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define WIN_SCORE 21

void draw(int xBall, int yBall, int yRacket1, int yRacket2, int score1, int score2) {
    clear();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == xBall && y == yBall) {
                mvprintw(y, x, "o"); // ball
            } else if (x == 2 && y >= yRacket1 && y < yRacket1 + RACKET_SIZE) {
                mvprintw(y, x, "#");
            } else if (x == WIDTH - 3 && y >= yRacket2 && y < yRacket2 + RACKET_SIZE) {
                mvprintw(y, x, "#");
            } else if (x == 0 || x == WIDTH - 1 || x == WIDTH / 2) {
                mvprintw(y, x, "|"); // borders
            } else if (y == 0 || y == HEIGHT - 1) {
                mvprintw(y, x, "-");
            }
        }
    }
    mvprintw(HEIGHT, 0, "Racket 1 -- 'a'-'z'   Racket 2 -- 'k'-'m'");
    mvprintw(HEIGHT + 1, 0, "Scores: player 1 = %d | Player 2 = %d", score1, score2);
    mvprintw(HEIGHT + 2, 0, "Press 'q' to exit");
    refresh();
}

void game() {
    int xBall = WIDTH / 2;
    int yBall = HEIGHT / 2;
    int dxBall = 1;
    int dyBall = 1;
    int yRacket1 = HEIGHT / 2 - 1;
    int yRacket2 = HEIGHT / 2 - 1;
    int score1 = 0;
    int score2 = 0;

    while (score1 < WIN_SCORE && score2 < WIN_SCORE) {
        draw(xBall, yBall, yRacket1, yRacket2, score1, score2);

        usleep(65000); 

        int inputSymbol = getch();
        if (inputSymbol != ERR) {
            if (inputSymbol == 'q' || inputSymbol == 'Q') break;
            if ((inputSymbol == 'a' || inputSymbol == 'A') && yRacket1 > 1) yRacket1--;
            else if ((inputSymbol == 'z' || inputSymbol == 'Z') && yRacket1 < HEIGHT - RACKET_SIZE - 1) yRacket1++;
            else if ((inputSymbol == 'k' || inputSymbol == 'K') && yRacket2 > 1) yRacket2--;
            else if ((inputSymbol == 'm' || inputSymbol == 'M') && yRacket2 < HEIGHT - RACKET_SIZE - 1) yRacket2++;
        }

        xBall += dxBall;
        yBall += dyBall;

        if (yBall == 1 || yBall == HEIGHT - 2) dyBall = -dyBall;
        if (xBall == 3 && yBall >= yRacket1 && yBall < yRacket1 + RACKET_SIZE) dxBall = -dxBall;
        if (xBall == WIDTH - 4 && yBall >= yRacket2 && yBall < yRacket2 + RACKET_SIZE) dxBall = -dxBall;

        if (xBall == 0) {
            score2++;
            xBall = WIDTH / 2;
            yBall = HEIGHT / 2;
            dxBall = -dxBall;
        }

        if (xBall == WIDTH - 1) {
            score1++;
            xBall = WIDTH / 2;
            yBall = HEIGHT / 2;
            dxBall = -dxBall;
        }
    }

    clear();
    if (score1 >= WIN_SCORE) mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "Player 1 is the winner ☺️!!!");
    else if (score2 >= WIN_SCORE) mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "Player 2 is the winner ☺️!!!");
    else mvprintw(HEIGHT / 2, WIDTH / 2 - 10, "Game stopped with 'q'");

    refresh();
    usleep(2000000); 
}

int main() {
    initscr();
    cbreak();
    noecho();
    timeout(0);
    curs_set(FALSE);

    game();

    endwin();
    return 0;
}