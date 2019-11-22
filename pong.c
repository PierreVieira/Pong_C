#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma ide diagnostic ignored "cert-msc32-c"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define qtde_colunas 64
#define qtde_linhas 48
#define MOV_BAIXO 2
#define MOV_CIMA 8
#define TIME_SLEEP 50000
#define TAMANHO_BARRA 10

char matriz[qtde_linhas][qtde_colunas];
int baixo1 = 1; //true
int baixo2 = 0; //false
int velocidade_bolaX = 1;
int velocidade_bolaY = 1;
int pontuacao1, pontuacao2;

typedef struct{
    int x, y; //Centro da objeto
    int tamanho;
    char caractere;
}objeto;

void printar_matriz(){
    for (int i = 0; i < qtde_linhas; ++i) {
        for (int j = 0; j < qtde_colunas; ++j) {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

void printa_pontuacao(){
    printf("PONTUAÇÃO A: %d                                    PONTUAÇÃO B: %d\n", pontuacao1, pontuacao2);
}

void limpaMatriz(){
    for (int i = 0; i < qtde_linhas; ++i) {
        for (int j = 0; j < qtde_colunas; ++j) {
            if(i == 0  || i == qtde_linhas-1 || j == 0 || j == qtde_colunas-1){
                matriz[i][j] = '*';
            }
            else {
                matriz[i][j] = ' ';
            }
        }
    }
}

void sorteiaInicioBarra(objeto *b){
    do{
        b->y = rand()%qtde_linhas + TAMANHO_BARRA/2;
    }while(b->y== 0);
}

void sorteiaInicioBola(objeto *b){
    b->y = rand()%20+20;
}

void inicializa_barra(objeto *b, int x, int tamanho, char caractere){
    b->x = x;
    sorteiaInicioBarra(b);
    b->tamanho = tamanho;
    b->caractere = caractere;
}

void inicializa_bola(objeto *b, int x, int tamanho, char caractere){
    b->x = x;
    sorteiaInicioBola(b);
    b->tamanho = tamanho;
    b->caractere = caractere;
}

void preencheMatrizCimaBarra(objeto barra){
    for (int k = barra.y; k < barra.y + barra.tamanho/2; ++k) {
        matriz[k][barra.x] = barra.caractere;
    }
}

void preencheMatrizBaixoBarra(objeto barra){
    for (int k = barra.y; k >= barra.y - barra.tamanho/2; --k) {
        matriz[k][barra.x] = barra.caractere;
    }
}

void preencheMatrizBola(objeto bola){
    matriz[bola.y][bola.x] = bola.caractere;
}

void preencher_matriz(objeto barra1, objeto barra2, objeto bola){
    limpaMatriz();
    
    preencheMatrizCimaBarra(barra1);
    preencheMatrizBaixoBarra(barra1);
    
    preencheMatrizCimaBarra(barra2);
    preencheMatrizBaixoBarra(barra2);
    
    preencheMatrizBola(bola);
}

void movimentaBarra(objeto *barra, int movimento){
    switch (movimento){
        case MOV_CIMA:
            barra->y--; //Movimenta para cima
            break;
        case MOV_BAIXO:
            barra->y++; //Movimenta para baixo
            break;
        case 0:
            break;
        default :
            printf("Sorteou errado\n");
            exit(0);
    }
}

void movimentaBola(objeto *bola){
    if(bola->y <= 1){ //se a bola bateu na borda superior
        velocidade_bolaY *= -1;
    }
    else if(bola->y >= qtde_linhas - 2){//se a bola bateu na borda inferior
        velocidade_bolaY *= -1;
    }
    bola->y += velocidade_bolaY;
    bola->x += velocidade_bolaX;
}

int movimentoBarra1(objeto barra){
    if (barra.y + barra.tamanho/2 - barra.tamanho + 1 <= 2){ //Se a barra está encostando na base superior
        baixo1 = 1;//Movimenta para baixo
    }
    else if(barra.y - barra.tamanho/2 + barra.tamanho - 1 >= qtde_linhas-2) {//Se a barra está encostando na base inferior
        baixo1 = 0;//Movimenta para cima
    }
    if(baixo1){
        return MOV_BAIXO;
    }
    return MOV_CIMA;
}

int movimentoBarra2(objeto barra){
    if (barra.y + barra.tamanho/2 - barra.tamanho + 1 <= 2){ //Se a barra está encostando na base superior
        baixo2 = 1;//Movimenta para baixo
    }
    else if(barra.y - barra.tamanho/2 + barra.tamanho - 1>= qtde_linhas-2) {//Se a barra está encostando na base inferior
        baixo2 = 0;//Movimenta para cima
    }
    if(baixo2){
        return MOV_BAIXO;
    }
    return MOV_CIMA;
}

void colisao(objeto *bola, objeto *barra){
    if  ((bola->y <= barra->y + barra->tamanho/2) &&
         (bola-> y >= barra->y - barra->tamanho/2) &&
         (bola-> x == barra->x)){
        velocidade_bolaX *= -1;
    }
}

int gol(objeto *bola){
    if(bola->x <= 0){
        pontuacao2++;
        return 1;
    }
    else if(bola->x >= qtde_colunas-1){
        pontuacao1++;
        return 1;
    }
    return 0;
}

int main() {
    pontuacao1 = pontuacao2 = 0;
    objeto barra1, barra2, bola;
    int movimento_barra1, movimento_barra2;
    srand(time(NULL));
    printf("LOADING...\n");
    usleep(TIME_SLEEP);
    inicializa_barra(&barra1, 2, TAMANHO_BARRA, 124);
    srand(time(NULL));
    usleep(TIME_SLEEP);
    inicializa_barra(&barra2, qtde_colunas -3, TAMANHO_BARRA, 124);
    srand(time(NULL));
    usleep(TIME_SLEEP);
    inicializa_bola(&bola, qtde_colunas/2, 1, 79);
    while(1){
        preencher_matriz(barra1, barra2, bola);
        printar_matriz();
        printa_pontuacao();
        movimento_barra1 = movimentoBarra1(barra1);
        movimento_barra2 = movimentoBarra2(barra2);
        movimentaBarra(&barra1, movimento_barra1);
        movimentaBarra(&barra2, movimento_barra2);
        movimentaBola(&bola);
        if(gol(&bola)){
            inicializa_bola(&bola, qtde_colunas/2, 1, 79);
            velocidade_bolaX *= -1;
        }
        colisao(&bola, &barra1);
        colisao(&bola, &barra2);
        usleep(TIME_SLEEP);
        printf("\033c");
    }
}
#pragma clang diagnostic pop
#pragma clang diagnostic pop
