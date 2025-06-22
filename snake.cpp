#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

#include "Fila.h"

char getch() {
    termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    char tabuleiro[30][30], comando;
    no *cobra;
    bool rodarJogo = true;
    int ultPosx, ultPosy;

    cobra = inicializaFila(cobra);
    cobra = insereFila(cobra, '0', 15, 15);

    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            if(i == 0 || j == 0 || i == 29 || j == 29) {
                tabuleiro[i][j] = '#';
            } else {
                tabuleiro[i][j] = '.';
            }
        }
    }

    tabuleiro[cobra->posx][cobra->posy] = cobra->info;
    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            cout << tabuleiro[i][j];
        }
        cout << "\n";
    }
    while(rodarJogo) {
        comando = getch();
        system("cls||clear");
        ultPosx = cobra->posx;
        ultPosy = cobra->posy;
        switch(comando) {
            case 'w':
                cobra->posx -= 1;
                break;
            case 'a':
                cobra->posy -= 1;
                break;
            case 's':
                cobra->posx += 1;
                break;
            case 'd':
                cobra->posy += 1;
                break;
        }
        tabuleiro[ultPosx][ultPosy] = '.';
        tabuleiro[cobra->posx][cobra->posy] = cobra->info;
        for(int i = 0; i < 30; i++) {
            for(int j = 0; j < 30; j++) {
                cout << tabuleiro[i][j];
            }
            cout << "\n";
        }
    }
}