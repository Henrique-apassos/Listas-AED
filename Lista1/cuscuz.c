#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int valor;
    char nipe;
} Carta;

typedef struct{
    Carta topo;
    int tam;
    Carta *elementos; // Alocacao dinamica
} Pilha;

typedef struct{
    int tamanho;
    Carta base;
    Carta *elementos; // Alocacao dinamica
} Fila;

bool pilhaVazia(Pilha conj);
Pilha push(Pilha conj, Carta elem);
Pilha pop(Pilha conj);

bool filaVazia(Fila fila);
Fila fpush(Fila fila, Carta carta);
Fila fpop(Fila fila);


int main(){
    int jogadores, rodada = 0;
    bool round = false;
    char jog[4];
    Pilha cuscuz = {0};
    scanf("%d", &jogadores);
    Carta cartar[jogadores];
    Fila mao[jogadores];
    for (int i = 0; i < jogadores; i++) {
    mao[i].tamanho = 0;
    mao[i].elementos = NULL;
    }


    while(strcmp(jog, "END") != 0){
        scanf(" %s", jog);
        if(strcmp(jog, "DEA") == 0){
            // Adicionar as cartas
            for(int i = 0; i< jogadores; i++){
                scanf(" %d %c", &cartar[i].valor, &cartar[i].nipe);
                mao[i] = fpush(mao[i], cartar[i]);
            }
            round = false;
        }
        else if(strcmp(jog, "RND") == 0){
            // Fazer a jogada
            bool empate = false;
            int win = -1;
            Carta maiorC = {0,'0'};
           if (jogadores == 2) {
        // Primeiros jogadores
        if (mao[0].base.valor == mao[1].base.valor) {
            if (mao[0].base.nipe == mao[1].base.nipe) {
                empate = true;
            } 
            else if (mao[0].base.nipe > mao[1].base.nipe) {
                maiorC = mao[0].base;
                win = 0;
            } 
            else {
                maiorC = mao[1].base;
                win = 1;
            }
            } 
            else if (mao[0].base.valor > mao[1].base.valor) {
                maiorC = mao[0].base;
                win = 0;
            } 
            else {
                maiorC = mao[1].base;
                win = 1;
            }
            } 
        else {
            maiorC = mao[0].base;
            win = 0;
            for (int i = 1; i < jogadores; i++) {
                if (maiorC.valor == mao[i].base.valor) {
                    if (maiorC.nipe < mao[i].base.nipe) {
                        maiorC = mao[i].base;
                        win = i;
                        empate = false;
                    } 
                    else if (maiorC.nipe == mao[i].base.nipe) {
                        empate = true;
                    }
                } 
                else if (maiorC.valor < mao[i].base.valor) {
                    maiorC = mao[i].base;
                    win = i;
                    empate = false;
                }
            }
            }
        
            // Adicionar todas as cartas jogadas na rodada à pilha 'cuscuz'
            for (int i = 0; i < jogadores; i++) {
                cuscuz = push(cuscuz, mao[i].base);
                mao[i] = fpop(mao[i]);
            }
            if(empate == true){
                printf("%d -1\n", rodada);
            }
            else{
                printf("%d %d\n", rodada, win);
            }
            round = true;
            rodada++;
        }
        else if(round == true && strcmp(jog,"PRT") == 0){
            // Mostrar ultima jogada
            int n = jogadores;
            if(cuscuz.tam < jogadores){
                n = cuscuz.tam;
            }
            printf("%d%c", cuscuz.elementos[cuscuz.tam -1].valor, cuscuz.elementos[cuscuz.tam -1 ].nipe);
            for(int i=1; i<n; i++){
                printf(" %d%c", cuscuz.elementos[cuscuz.tam -1 -i].valor, cuscuz.elementos[cuscuz.tam -1 -i].nipe);
            }
            printf("\n");
            round = false;
        }
    }
    for(int i = 0; i < jogadores; i++){
        if(mao[i].elementos != NULL){
            free(mao[i].elementos);
        }
    }
    if(cuscuz.elementos != NULL){
        free(cuscuz.elementos);
    }
    
    return 0;
}

bool pilhaVazia(Pilha conj){
    return conj.tam == 0? true : false;
}

Pilha push(Pilha conj, Carta elem){
    if(pilhaVazia(conj) == true){
        conj.tam = 1;
        conj.elementos = (Carta*)calloc(1,sizeof(Carta));
        if(conj.elementos == NULL){
            printf("Erro de alcacao \n");
            exit(1);
        }
        conj.elementos[0] = elem;
        conj.topo = elem;
        return conj;
    }
    else{
        conj.tam++;
        Carta* temp = realloc(conj.elementos, conj.tam*sizeof(Carta));
        if(temp == NULL){
            printf("Erro de alcocacao \n");
         exit(1);
        }
        conj.elementos = temp;
        conj.elementos[conj.tam-1] = elem;
        return conj;
    }
}   

Pilha pop(Pilha conj) {
    if (pilhaVazia(conj)) {
        return conj;
    } else {
        if (conj.tam > 1) {
            conj.tam--;
            Carta* temp = realloc(conj.elementos, conj.tam * sizeof(Carta));
            if (temp == NULL) {
                printf("Erro de alocação!\n");
                exit(1);
            }
            conj.elementos = temp;
        }
        else {
            conj.tam = 0;
            free(conj.elementos);
            conj.elementos = NULL;
            conj.topo.valor = 0;
            conj.topo.nipe = '0';
        }
        return conj;
    }
}

bool filaVazia(Fila fila){
    return fila.tamanho == 0? true : false;
}

Fila fpush(Fila fila, Carta carta){
    if(filaVazia(fila) == true){
        fila.tamanho = 1;
        // Adicionar a primeira carta (base)
        fila.elementos = (Carta*) malloc(sizeof(Carta));
        if(fila.elementos == NULL){
            printf("Erro de Alocacao ");
            exit(1);
        }
        fila.elementos[0] = carta;
        fila.base = carta;
        return fila;
    }
    else{
        fila.tamanho++;
        Carta* temp = realloc(fila.elementos, fila.tamanho*sizeof(Carta));
        if(temp == NULL){
            printf("Erro de alocacao ");
            exit(1);
        }
        fila.elementos = temp;
        fila.elementos[fila.tamanho-1] = carta;
        return fila;
    }
}

Fila fpop(Fila fila){
    if(filaVazia(fila)){
        return fila;
    }
    else if(fila.tamanho == 1){
        free(fila.elementos);
        fila.tamanho--;
        fila.base.nipe = '0';
        fila.base.valor = 0;
        return fila;
    }
    else{
        Carta* temp = NULL;
        fila.tamanho--;
        fila.base = fila.elementos[1];
        
        temp = (Carta*) malloc(fila.tamanho*sizeof(Carta));
        if(temp == NULL){
            printf("Erro de Alocacao");
            exit(1);
        }
        for(int i = 0; i< fila.tamanho; i++){
            temp[i] = fila.elementos[i+1];
        }
        free(fila.elementos);
        fila.elementos = temp;
        
        return fila;
    }
}