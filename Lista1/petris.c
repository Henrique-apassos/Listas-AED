#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int topo;
    int tam;
    int *elementos; // Alocacao dinamica
} Pilha;

typedef struct lista{
    int pos;
    Pilha elementos;
    struct lista *proximo;
} Lista;

bool pilhaVazia(Pilha conj);
Pilha push(Pilha conj, int elem);
Pilha pop(Pilha conj);

void addInicio(Lista **lista, int col, int elem);
void addFim(Lista **lista, int col, int elem);
void addMeio(Lista **lista, int col, int elem, int ant);
void imprimir(Lista *list, int num);
Lista* remover(Lista **lista, int id);
Lista* buscar(int id, Lista* listas);
Lista* inserir(int col, int elem, Lista *listas);
Lista* limpeza(Lista *lista);
void esvaziar(Lista **lista);


int main(){
    char fim[4], *p;
    p = fim;
    int qnt, elem, col;
    Lista *listas;

    scanf("%d", &qnt);

    for(int i=0; i<qnt; i++){
        listas = NULL;
        scanf(" %s", fim);
        while(strcmp(fim,"END") != 0){
            if(p[1] != '\0'){
                col = (((p[0]-'0')*10) + (p[1]-'0'));
            }
            else
                col = *p - '0';
            //printf("%d \n", col);
            scanf("%d", &elem);
            listas = inserir(col, elem, listas);
            listas = limpeza(listas);

            scanf(" %s", fim);
        }
        imprimir(listas, i);
        esvaziar(&listas);
    }

    return 0;
}

bool pilhaVazia(Pilha conj){
    return conj.tam == 0? true : false;
}

Pilha push(Pilha conj, int elem){
    if(pilhaVazia(conj) == true || conj.elementos == NULL){
        conj.tam = 1;
        conj.elementos = (int*)calloc(1,sizeof(int));
        if(conj.elementos == NULL){
            printf("Erro de alcacao 1\n");
            exit(1);
        }
        conj.elementos[0] = elem;
        conj.topo = elem;
    }
    else{
        conj.tam++;
        int* temp = realloc(conj.elementos, conj.tam * sizeof(int));
        if(temp == NULL){
            printf("Erro de alcocacao 2\n");
         exit(1);
        }
        conj.elementos = temp;
        conj.elementos[conj.tam-1] = elem;
        conj.topo = elem;
    }
    return conj;
}   

Pilha pop(Pilha conj) {
    if (pilhaVazia(conj)) {
        return conj;
    } 
    else {
        if (conj.tam > 1) {
            conj.tam--;
            int* temp = realloc(conj.elementos, conj.tam * sizeof(int));
            if (temp == NULL) {
                printf("Erro de alocação!\n");
                exit(1);
            }
            conj.elementos = temp;
            conj.topo = conj.elementos[conj.tam - 1];
        } 
        else {
            conj.tam = 0;
            free(conj.elementos);
            conj.elementos = NULL;
            conj.topo = 0;
        }
        return conj;
    }
}

void addInicio(Lista **lista, int col, int elem){
    Lista *novo = NULL;
    novo = (Lista*) malloc(sizeof(Lista));
    if(novo == NULL){
        printf("Erro de alcocacao 3");
        exit(1);
    }
    novo->pos = col;
    novo->elementos.elementos = NULL;
    novo->elementos.tam = 0;
    novo->elementos = push(novo->elementos, elem);
    novo->proximo = *lista;
    *lista = novo;
}

void addFim(Lista **lista, int col, int elem){
    Lista *novo = NULL, *aux = NULL;
    novo = (Lista*) malloc(sizeof(Lista));
    if(novo == NULL){
        printf("Erro de alcocacao 4");
        exit(1);
    }
    novo->pos = col;
    novo->elementos.elementos = NULL;
    novo->elementos.tam = 0;
    novo->elementos = push(novo->elementos, elem);
    novo->proximo = NULL;
    if(*lista == NULL){
        *lista = novo;
    }
    else{
        aux = *lista;
        while(aux->proximo != NULL)
            aux = aux->proximo;
        aux->proximo = novo;
    }
}

void addMeio(Lista **lista, int col, int elem, int ant){
    Lista *novo = NULL, *aux = NULL;
    novo = (Lista*) malloc(sizeof(Lista));
    if(novo == NULL){
        printf("Erro de alcocacao 5");
        exit(1);
    }
    novo->pos = col;
    novo->elementos.elementos = NULL;
    novo->elementos.tam = 0;
    novo->elementos = push(novo->elementos, elem);
    // Primeira lista?
    if(*lista == NULL){
        novo->proximo = NULL;
        *lista = novo;
    }
    else{
        aux = *lista;
        while(aux->pos != ant && aux->proximo != NULL)
            aux = aux->proximo;
        novo->proximo = aux->proximo;
        aux->proximo = novo;

    }
}

void imprimir(Lista *list, int num){
    printf("caso %d:", num);

    while(list != NULL){
        //printf(" p%d", list->pos);
        printf(" %d", list->elementos.topo);
        list = list->proximo;
    }
    
    if(list == NULL)
        printf("\n");
}

Lista* remover(Lista **lista, int id){
    Lista *del = NULL, *aux = NULL;
    if(*lista != NULL){
        if((*lista)->pos == id){
            del = *lista;
            *lista = del->proximo;
        }
        else{
            aux = *lista;
            while(aux->proximo != NULL && aux->proximo->pos != id)
                aux = aux->proximo;
            if(aux->proximo != NULL){
                del = aux->proximo;
                aux->proximo = del->proximo;
            }
        }
    }

    return del;
}

Lista* buscar(int id, Lista *listas){
    Lista *q = NULL;
    q = listas;
    while(q != NULL && q->pos != id){
        q = q->proximo;
    }
    return q; // retorna nulo se nao encontrar
}

Lista* inserir(int col, int elem, Lista *listas){
    Lista* ref = NULL;
    ref = buscar(col, listas);
    if(listas == NULL){
        // Primeira lista
        listas = (Lista*) malloc(sizeof(Lista));
        if(listas == NULL){
            printf("Erro de alocacao 6");
            exit(1);
        }
        listas->pos = col;
        listas->elementos.elementos = NULL;
        listas->elementos = push(listas->elementos, elem);
        listas->proximo = NULL;
        return listas;
    }
    else if(ref == NULL){
        // Criar nova lista
        Lista* aux = NULL;
        int n;
        aux = listas;
        while(aux->proximo != NULL && aux->pos < col){
            aux = aux->proximo;
        }
        if(col > aux->pos && aux->proximo == NULL){
            n = aux->pos;
            n++;
            if(col == n){
                addFim(&listas, col, elem);
            }
            else
                return listas;
        }
        else{
            if(col == 0){
                addInicio(&listas, col, elem);

            }
            else
                addInicio(&listas, col, elem);
        }
        return listas;
    }
    else{
        // Adicionar a uma lista ja existente
        if(ref->elementos.topo == elem){
            ref->elementos = pop(ref->elementos);
        }
        else{
            ref->elementos = push(ref->elementos, elem);
        }
        return listas;
    }
}

Lista* limpeza(Lista *lista){
    Lista *aux = NULL;
    int col = 1;
    aux = lista;
    while(aux != NULL){
        if(pilhaVazia(aux->elementos) == true){
            
            aux = remover(&lista, aux->pos);
            aux = aux->proximo;
        }
        else{
            aux = aux->proximo;
        }
    }

    
    aux = lista;
    while(aux != NULL){
        aux->pos = col++;
        aux = aux->proximo;
    }
    return lista;
}

void esvaziar(Lista **lista){
    Lista *aux = NULL, *temp = NULL;
    aux = *lista;

    while(aux != NULL){
        if(pilhaVazia(aux->elementos) == false);
        free(aux->elementos.elementos);

        temp = aux;
        aux = aux->proximo;

        free(temp);
    }

    *lista = NULL;
}