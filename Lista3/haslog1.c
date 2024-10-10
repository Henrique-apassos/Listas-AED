#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    unsigned int time;
    unsigned int client;
} Pacote;

Pacote* adiciona(Pacote* vet, unsigned int add_t, unsigned int add_c, int* tam);
int busca(Pacote* vet, int tam, unsigned int buscado);

int main(){
    Pacote *vet = NULL;
    int tam = 0;
    char comando[5];
    scanf("%s", comando);
    while(strcmp(comando, "END") != 0){
        if(strcmp(comando, "NEW") == 0){
            unsigned int t, c;
            scanf("%u %u", &t, &c);
            vet = adiciona(vet, t, c, &tam);
        }
        else if(strcmp(comando, "QRY") == 0){
            unsigned int busc;
            scanf("%u", &busc);
            int pos = busca(vet, tam, busc);
            if(pos == -1){
                printf("-1 -1\n");
            }
            else{
                printf("%u %u\n", vet[pos].client, pos);
            }
        }
        scanf("%s", comando);
    }
    free(vet);
    return 0;
}

Pacote* adiciona(Pacote* vet, unsigned int add_t, unsigned int add_c, int* tam){
    if(vet == NULL){
        vet = (Pacote*) malloc(sizeof(Pacote));
        if(vet == NULL){
            printf("Erro de alocacao! \n");
            exit(1);
        }
        vet->client = add_c;
        vet->time = add_t;
        (*tam)++;
        return vet;
    }
    else{
        (*tam)++;
        Pacote *temp = NULL;
        temp = realloc(vet, *tam*sizeof(Pacote));
        if(temp == NULL){
            printf("Erro de alocacao \n");
            exit(1);
        }
        temp[*tam-1].client = add_c;
        temp[*tam-1].time = add_t;
        vet = temp;
        return vet;
    }
}

int busca(Pacote* vet, int tam, unsigned int buscado){
    int esquerda = 0;
    int direita = tam - 1;

    while(esquerda <= direita){
        int meio = esquerda + (direita - esquerda) / 2;
        if(vet[meio].time == buscado)
            return meio;
        else if(vet[meio].time < buscado)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }
    
    return -1;
}