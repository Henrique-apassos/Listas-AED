#include <iostream>

using namespace std;


void iniciaMatriz(int ***matriz, int linhas, int colunas);
void freeMatriz(int ***matriz, int linhas);

int main(){
    int comandos, tam, rParedes;
    cin >> comandos;
    for(int k=0; k<comandos; k++){
        int Q;
        int remover;
        cin >> tam >> rParedes >> Q;
        int **labirinto = nullptr;
        iniciaMatriz(&labirinto, tam, tam);
        for(int i= 0; i<rParedes; i++){
            cin >> remover;
        }

        freeMatriz(&labirinto, tam);
    }
    return 0;
}

void iniciaMatriz(int ***matriz, int linhas, int colunas){
    if(*matriz == nullptr){
        *matriz = (int **) malloc(linhas * sizeof(int *));
        if(*matriz == nullptr){
            cout << "Erro de Alocacao!\n";
            exit(1);
        }
        for(int i=0; i < linhas; i++){
            (*matriz)[i] = (int *) malloc(colunas * sizeof(int));
            if((*matriz)[i] == nullptr){
                cout << "Erro de alocacao!\n";
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