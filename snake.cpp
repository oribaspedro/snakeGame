#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

#include "Fila.h"

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


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
    no *P = snake;
    while (P != NULL) {
        tabuleiro[P->posx][P->posy] = P->info;
        P = P->link;
    }

    system("clear"); 

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            char c = tabuleiro[i][j];
            switch (c) {
                case '.':
                    cout << "\033[32m" << setw(2) << c << "\033[0m"; 
                    break;
                case 'O':
                    cout << "\033[31m" << setw(2) << c << "\033[0m"; 
                    break;
                case '@':
                    cout << "\033[34m" << setw(2) << c << "\033[0m"; 
                    break;
                case '#':
                    cout << "\033[33m" << setw(2) << c << "\033[0m"; 
                    break;
                default:
                    cout << setw(2) << c;
            }
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
            break;
        case 'a':
            P->posy -= 1;
            break;
        case 's':
            P->posx += 1;
            break;
        case 'd':
            P->posy += 1;
            break;
    }
    
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
    
    cout << "\033[32m";
    cout << R"(

    ╔═══════════════════════╗
    ║   🐍  SNAKE GAME  🎮  ║
    ╚═══════════════════════╝

    )" << "\033[0m";

    cout << "\n\033[36mBem-vindo ao jogo!\033[0m\n\n";
    cout << "Use as teclas \033[33mw\033[0m, \033[33ma\033[0m, \033[33ms\033[0m, \033[33md\033[0m para se mover pelo tabuleiro.\n";
    cout << "Coma as \033[35msementes (@)\033[0m para crescer e evite bater nas paredes ou em si mesmo!\n\n";
    cout << "\033[37mAperte qualquer tecla para iniciar...\033[0m\n";
    
    if (getch()){
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

    imprimeTabuleiro(tabuleiro, cobra, &ultPosx, &ultPosy);

    char direcaoAtual = 'd'; 

    while(rodarJogo) {
        if (kbhit()) { 
            comando = getch();
            if (comando == 'w' || comando == 'a' || comando == 's' || comando == 'd') {
                direcaoAtual = comando;
            }
        }
    
        ultPosx = cobra->posx;
        ultPosy = cobra->posy;
        cobra = atualizarPosicoes(tabuleiro, cobra, direcaoAtual, &ultPosx, &ultPosy);
    
        // Verifica colisões
        if(tabuleiro[cobra->posx][cobra->posy] == '#' || tabuleiro[cobra->posx][cobra->posy] == 'O') {
            rodarJogo = false;
        } else if(tabuleiro[cobra->posx][cobra->posy] == '@') {
            cobra = insereFila(cobra, 'O', ultPosx, ultPosy);
            geradorAlimento(tabuleiro);
        } else {
            tabuleiro[ultPosx][ultPosy] = '.';
        }  
    
        imprimeTabuleiro(tabuleiro, cobra, &ultPosx, &ultPosy);
        usleep(60000);
        }
    }
    system("clear"); // ou "cls" no Windows

            cout << "\033[31m"; // vermelho
            cout << R"(
        
           ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ 
          ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
          ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝
          ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║▄▄ ██║██║   ██║██╔══╝  ██╔══██╗
          ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝╚██████╔╝███████╗██║  ██║
           ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚══▀▀═╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝
        
                             💥 Você meteu o focinho onde não devia! 💥
                                       🎮 Fim de Jogo 🎮
        
        )" << "\033[0m";

}