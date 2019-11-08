#include <stdio.h>
#include <stdlib.h>
#define qtde_colunas 32
#define qtde_linhas 24

typedef struct{
    //Centro da objeto
    int x, y, tamanho;
    char caractere;
}objeto;

void inicializa_objeto(objeto *b, int x, int tamanho, char caractere){
    b->x = x;
    b->y = qtde_linhas/2;
    b->tamanho = tamanho;
    b->caractere = caractere;
}

void preencher_matriz(char matriz[qtde_linhas][qtde_colunas], objeto barra1, objeto barra2, objeto bola){
    //Limpa
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
    //Preenche pra cima
    for (int k = barra1.y; k < barra1.y + barra1.tamanho/2; ++k) {
        matriz[k][barra1.x] = barra1.caractere;
        matriz[k][barra2.x] = barra2.caractere;
    }
    //Preenche pra baixo
    for (int k = barra1.y; k >= barra1.y - barra1.tamanho/2; --k) {
        matriz[k][barra1.x] = barra1.caractere;
        matriz[k][barra2.x] = barra2.caractere;
    }
    //Taca a bola
    matriz[bola.y][bola.x] = bola.caractere;
}

void printar_matriz(char matriz[qtde_linhas][qtde_colunas]){
    for (int i = 0; i < qtde_linhas; ++i) {
        for (int j = 0; j < qtde_colunas; ++j) {
            printf("[%c]", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char matriz[qtde_linhas][qtde_colunas];
    objeto barra1, barra2, bola;
    inicializa_objeto(&barra1, 2, 4, 124);
    inicializa_objeto(&barra2, qtde_colunas -3, 4, 124);
    inicializa_objeto(&bola, qtde_colunas/2, 1, 79);
    int n = 0;
    while(n < 5){
        system("clear");
        preencher_matriz(matriz, barra1, barra2, bola);
        printar_matriz(matriz);
        n++;
    }
    return 0;
}
