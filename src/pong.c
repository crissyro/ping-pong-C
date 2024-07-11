#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define RACKET_SIZE 3
#define WIN_SCORE 21

void draw(int xBall, int yBall, int yRacket1, int yRacket2, int score1, int score2) {
    printf("\033[H\033[J"); // ANSI escape code for cleaning screen

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == xBall && y == yBall) {
                printf("o"); // ball
            } else if (x == 2 && y >= yRacket1 && y < yRacket1 + RACKET_SIZE) {
                printf("#"); 
            } else if (x == WIDTH - 3 && y >= yRacket2 && y < yRacket2 + RACKET_SIZE) {
                printf("#"); 
            } else if (x == 0 || x == WIDTH - 1 || x == WIDTH / 2) {
                printf("|"); // borders
            } else if (y == 0 || y == HEIGHT - 1) {
                printf("-"); 
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Racket 1 -- \'a\'-\'z\'   Racket 2 -- \'k\'-\'m\'\n");
    printf("Scores: player 1 = %d | Player 2 = %d\n", score1, score2);
    printf("Press to exit - \'q\'\n");
}

void game() {
    // placement ball
    int xBall = WIDTH / 2;
    int yBall = HEIGHT / 2;
    // change moving of ball
    int dxBall = 1;
    int dyBall = 1;
    // placement of rackets
    int yRacket1 = HEIGHT / 2 - 1;
    int yRacket2 = HEIGHT / 2 - 1;
    // scores of players
    int score1 = 0;
    int score2 = 0;

    while (score1 < WIN_SCORE && score2 < WIN_SCORE) {

        draw(xBall, yBall, yRacket1, yRacket2, score1, score2);

        char inputSymbol;
        inputSymbol = getchar();

        while (getchar() != '\n'); 

        if (inputSymbol == ' ') continue;
    
        if (inputSymbol == 'q' || inputSymbol == 'Q') break;

        if ((inputSymbol == 'a' || inputSymbol == 'A') && yRacket1 > 1) yRacket1--;

        else if ((inputSymbol == 'z' || inputSymbol == 'Z') && yRacket1 < HEIGHT - RACKET_SIZE - 1) yRacket1++;

        else if ((inputSymbol == 'k' || inputSymbol == 'K') && yRacket2 > 1) yRacket2--;

        else if ((inputSymbol == 'm' || inputSymbol == 'M') && yRacket2 < HEIGHT - RACKET_SIZE - 1) yRacket2++;
        
        xBall += dxBall;
        yBall += dyBall;

        if (yBall == 1  || yBall == HEIGHT - 2) dyBall = -dyBall;
        
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

    if (score1 >= WIN_SCORE) printf("Player 1 is winner ☺️!!!\n");

    else if (score2 >= WIN_SCORE) printf("Player 2 is winner ☺️!!!\n");

    else printf("Stop game with Q\n");
}

int main() {

    game();

    return 0;
}