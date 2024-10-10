#include <stdio.h>
#include <stdlib.h>
#define credMax 25000
#define brinqMax 1000
#define Max(a, b) ((a) > (b)? (a) : (b))

typedef struct{
    int diversao;
    int aborrecimento;
    int custo;
} Brinquedo;

void iniciaMatriz(int ***matriz, int linhas, int colunas){
    if(*matriz == NULL){
        *matriz = (int **) malloc(linhas * sizeof(int *));
        if(*matriz == NULL){
            printf("Erro de Alocacao!\n");
            exit(1);
        }
        for(int i=0; i < linhas; i++){
            (*matriz)[i] = (int *) malloc(colunas * sizeof(int));
            if((*matriz)[i] == NULL){
                free(*matriz);
                printf("Erro de alocacao!\n");
                exit(1);
            }
        }
    }
}
void freeMatriz(int ***matriz, int linhas){
    for(int i=0; i<linhas; i++){
        free((*matriz)[i]);
    }
    free(*matriz);
}

int divertimento(int credito, int brinquedo, Brinquedo briq[], int **mochila) {
    if (credito == 0 || brinquedo < 0) {
        return 0;
    }

    // se já tem na memória
    if (mochila[brinquedo][credito] != -1)
        return mochila[brinquedo][credito];

    int naoPega = divertimento(credito, brinquedo - 1, briq, mochila);
    int pega = naoPega;

    if (briq[brinquedo].custo <= credito) {
        int t = 1;
        int diversaoTotal = 0;
        
        // Tentamos pegar o brinquedo até que a diversão se torne <= 0
        while (1) {
            int F = briq[brinquedo].diversao - (t - 1) * (t - 1) * briq[brinquedo].aborrecimento;
            if (F <= 0) break; // Diversão torna-se nula ou negativa, parar
            
            int custoTotal = t * briq[brinquedo].custo;
            if (custoTotal > credito) break; // Não há créditos suficientes para mais repetições

            diversaoTotal += F; // Soma a diversão obtida nessa repetição
            
            // Chama recursivamente para o próximo brinquedo com os créditos restantes
            pega = Max(pega, diversaoTotal + divertimento(credito - custoTotal, brinquedo - 1, briq, mochila));
            t++;
        }
    }

    return mochila[brinquedo][credito] = pega;
}

int main(){
    // Inicia uma matriz de memoria
    int **mochila = NULL;
    iniciaMatriz(&mochila, brinqMax+1, credMax+1);

    // inicia os elementos como -1
    for(int i=0; i<=brinqMax; i++){
        for(int j=0; j<=credMax; j++){
            mochila[i][j] = -1;
        }
    }
    int brinquedos;
    scanf("%d", &brinquedos);
    Brinquedo brinquedo[brinquedos];
    for(int b=0; b<brinquedos; b++){
        scanf("%d %d %d", &brinquedo[b].diversao, &brinquedo[b].aborrecimento, &brinquedo[b].custo);
    }
    int visitas;
    scanf("%d", &visitas);
    int credito[visitas];
    for(int v=0; v<visitas; v++){
        scanf("%d", &credito[v]);
        printf("%d: %d\n", v, divertimento(credito[v], brinquedos-1, brinquedo, mochila));
    }
    freeMatriz(&mochila, brinqMax+1);
    return 0;
}