#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <ctime>
#include <iomanip>
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

void imprimeTabuleiro(char tabuleiro[30][30], no *snake, int *ultPosx, int *ultPosy) {
    no *P;
    P = snake;
    while(P != NULL) {
        tabuleiro[snake->posx][snake->posy] = snake->info;
        P = P->link;
    }
    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            cout << setw(2) << tabuleiro[i][j];
        }
        cout << "\n";
    }
}

no *atualizarPosicoes(char tabuleiro[30][30], no *snake, char comando, int *ultPosx, int *ultPosy) {
    no *P;
    P = snake;
    char aux;

    switch(comando) {
        case 'w':
            P->posx -= 1;
            P = P->link;
            while(P != NULL) {
                aux = P->posx;
                P->posx = *ultPosx;
                *ultPosx = aux;
                switch(P->posy, *ultPosy);
                aux = P->posy;
                P->posy = *ultPosy;
                *ultPosy = aux;
                P = P->link;
            }
            break;
        case 'a':
            P->posy -= 1;
            P = P->link;
            while(P != NULL) {
                aux = P->posx;
                P->posx = *ultPosx;
                *ultPosx = aux;
                switch(P->posy, *ultPosy);
                aux = P->posy;
                P->posy = *ultPosy;
                *ultPosy = aux;
                P = P->link;
            }
            break;
        case 's':
            P->posx += 1;
            P = P->link;
            while(P != NULL) {
                aux = P->posx;
                P->posx = *ultPosx;
                *ultPosx = aux;
                switch(P->posy, *ultPosy);
                aux = P->posy;
                P->posy = *ultPosy;
                *ultPosy = aux;
                P = P->link;
            }
            break;
        case 'd':
            P->posy += 1;
            P = P->link;
            while(P != NULL) {
                aux = P->posx;
                P->posx = *ultPosx;
                *ultPosx = aux;
                switch(P->posy, *ultPosy);
                aux = P->posy;
                P->posy = *ultPosy;
                *ultPosy = aux;
                P = P->link;
            }
            break;
    }
    return snake;
}

void geradorAlimento(char tabuleiro[30][30]) {
    int posx, posy;
    bool posValida = false;

    do {
        posx = rand()%28+1;
        posy = rand()%28+1;
        if(tabuleiro[posx][posy] == '.') {
            posValida = true;
        }
    } while(!(posValida));
    
    tabuleiro[posx][posy] = '@';
}

int main() {
    srand(time(NULL));
    char tabuleiro[30][30], comando;
    no *cobra;
    bool rodarJogo = true;
    int ultPosx = 15, ultPosy = 15, posPontox, posPontoy;

    cobra = inicializaFila(cobra);
    cobra = insereFila(cobra, 'O', 15, 15);

    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            if(i == 0 || j == 0 || i == 29 || j == 29) {
                tabuleiro[i][j] = '#';
            } else {
                tabuleiro[i][j] = '.';
            }
        }
    }
    geradorAlimento(tabuleiro);

    //tabuleiro[cobra->posx][cobra->posy] = cobra->info;
    imprimeTabuleiro(tabuleiro, cobra, &ultPosx, &ultPosy);
    
    /*for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            cout << tabuleiro[i][j];
        }
        cout << "\n";
    }*/
    while(rodarJogo) {
        comando = getch();
        //system("cls||clear");
        ultPosx = cobra->posx;
        ultPosy = cobra->posy;
        cobra = atualizarPosicoes(tabuleiro, cobra, comando, &ultPosx, &ultPosy);
        if(tabuleiro[cobra->posx][cobra->posy] == '#' || tabuleiro[cobra->posx][cobra->posy] == 'O') {
            rodarJogo = false;
        } else if(tabuleiro[cobra->posx][cobra->posy] == '@') {
            cobra = insereFila(cobra, 'O', ultPosx, ultPosy);
            geradorAlimento(tabuleiro);
        } else {
            tabuleiro[ultPosx][ultPosy] = '.';
        }  
        imprimeTabuleiro(tabuleiro, cobra, &ultPosx, &ultPosy);
        //imprimeFila(cobra);
        //tabuleiro[ultPosx][ultPosy] = '.';
        //tabuleiro[cobra->posx][cobra->posy] = cobra->info;
        //for(int i = 0; i < 30; i++) {
        //    for(int j = 0; j < 30; j++) {
        //        cout << tabuleiro[i][j];
        //    }
        //    cout << "\n";
        //}
    }
}