#include <iostream>
#include <cstdlib>
#define INF 1048576

using namespace std;

struct Ponto{
    int x, y;
};

typedef struct {
    int tamanho;
    Ponto base;
    Ponto* elementos;
} Fila;

bool filaVazia(Fila fila);
Fila fpush(Fila fila, Ponto add);
Fila fpop(Fila fila);


void iniciaMatriz(int ***matriz, int linhas, int colunas);
void freeMatriz(int ***matriz, int linhas);

int bfs(int **matriz, int linhas, int colunas, Ponto inicio, Ponto fim);
bool valido(int x, int y, int linhas, int colunas){
    return x >= 0 && x < linhas && y >= 0 && y < colunas;
}

int main(){
    int linhas, colunas;
    Ponto inicio, fim;

    cin >> linhas >> colunas;
    int **matriz = nullptr;
    iniciaMatriz(&matriz, linhas, colunas);
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            cin >> matriz[i][j];
            if(matriz[i][j] == 2)
                inicio = {i, j};
            else if(matriz[i][j] == 3)
                fim = {i, j};
        }
    }
    int resultado = bfs(matriz, linhas, colunas, inicio, fim);
    if(resultado != -1){
        cout << resultado << "\n";
    }
    else{
        cout << "Labirinto Impossivel\n";
    }
    freeMatriz(&matriz, linhas);
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

bool filaVazia(Fila fila) {
    return fila.tamanho == 0 ? true : false;
}

Fila fpush(Fila fila, Ponto add) {
    if (filaVazia(fila) == true) {
        fila.tamanho = 1;
        // Adicionar a primeira int (base)
        fila.elementos = (Ponto*)malloc(sizeof(Ponto));
        if (fila.elementos == NULL) {
            printf("Erro de Alocacao ");
            exit(1);
        }
        fila.elementos[0] = add;
        fila.base = add;
        return fila;
    }
    else {
        fila.tamanho++;
        Ponto* temp = (Ponto*)realloc(fila.elementos, fila.tamanho * sizeof(Ponto));
        if (temp == NULL) {
            printf("Erro de alocacao ");
            exit(1);
        }
        fila.elementos = temp;
        fila.elementos[fila.tamanho - 1] = add;
        return fila;
    }
}

Fila fpop(Fila fila) {
    if (filaVazia(fila)) {
        return fila;
    }
    else if (fila.tamanho == 1) {
        free(fila.elementos);
        fila.tamanho--;
        fila.base = {0, 0};
        return fila;
    }
    else {
        Ponto* temp = NULL;
        fila.tamanho--;
        fila.base = fila.elementos[1];

        temp = (Ponto*)malloc(fila.tamanho * sizeof(Ponto));
        if (temp == NULL) {
            printf("Erro de Alocacao");
            exit(1);
        }
        for (int i = 0; i < fila.tamanho; i++) {
            temp[i] = fila.elementos[i + 1];
        }
        free(fila.elementos);
        fila.elementos = temp;

        return fila;
    }
}
int bfs(int **matriz, int linhas, int colunas, Ponto inicio, Ponto fim){
    Fila vertices;
    vertices.elementos = nullptr;
    vertices.base = {0, 0};
    vertices.tamanho = 0;
    int dx[] = {-1, 1, 0, 0}; // cima, baixo, esquerda, direita
    int dy[] = {0, 0, -1, 1};
    int **dist = nullptr;
    iniciaMatriz(&dist, linhas, colunas);
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            dist[i][j] = INF;
        }
    }

    dist[inicio.x][inicio.y] = 0;
    vertices = fpush(vertices, inicio);

    while(!filaVazia(vertices)){
        Ponto pivo = vertices.base;
        vertices = fpop(vertices);
        for(int i=0; i<4; i++){
            int nx = pivo.x + dx[i];
            int ny = pivo.y + dy[i];

            if(valido(nx, ny, linhas, colunas) && matriz[nx][ny] != 1 && dist[nx][ny] == INF){
                dist[nx][ny] = dist[pivo.x][pivo.y] + 1;
                vertices = fpush(vertices, {nx, ny});
                if(nx == fim.x && ny == fim.y){
                    int d = dist[nx][ny];
                    free(vertices.elementos);
                    freeMatriz(&dist, linhas);
                    return d;
                }
            }
        }
    }
    freeMatriz(&dist, linhas);
    return -1;
}