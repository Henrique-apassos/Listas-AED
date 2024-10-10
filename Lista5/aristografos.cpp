#include <iostream>
#define INF 33554432

using namespace std;

typedef struct no{
	int vertice;
	int peso;
	struct no *proximo;
}No;

class grafo{
	private:
	int n_nos;
	No **listAdj;

	public:
	grafo(int V=0){
		n_nos = V;
		listAdj = nullptr;
		listAdj = new No*[V];
		if(listAdj == nullptr){
			cout << "Erro de Alocacao!\n";
			exit(1);
		}
		for(int i=0; i<V; i++){
			listAdj[i] = nullptr;
		}
	}

	No* criaNo(int, int);
	void addAresta(int, int, int);
	void printGrafo();
	void freeGrafo();
	No* procura(int, int);
	void atualizaPeso(int, int, int);
	void Dijkstra(int, int);
};

class heap {
private:
	int tam;
	int compr;
	No* elem;
public:
	heap(int capacidade) {
        tam = 0;
        compr = capacidade;
        elem = new No[capacidade];
        if (elem == nullptr) {
            cout << "Erro de alocacao!\n";
            exit(1);
        }
    }

    ~heap() {
        delete[] elem;
    }

    int pai(int i) {
        return (i - 1) / 2;
    }

    int esquerda(int i) {
        return 2 * i + 1;
    }

    int direita(int i) {
        return 2 * i + 2;
    }

    void min_Heapfy(int i) {
        int esq = esquerda(i);
        int dir = direita(i);
        int menor = i;

        if (esq < tam && elem[esq].peso < elem[menor].peso) {
            menor = esq;
        }
        if (dir < tam && elem[dir].peso < elem[menor].peso) {
            menor = dir;
        }

        if (menor != i) {
            swap(elem[i], elem[menor]);
            min_Heapfy(menor);
        }
    }

    void insert(No novoNo) {
        if (tam == compr) {
            cout << "Heap cheio!\n";
            return;
        }

        tam++;
        int i = tam - 1;
        elem[i] = novoNo;

        // Subir o novo nó para a posição correta
        while (i != 0 && elem[pai(i)].peso > elem[i].peso) {
            swap(elem[i], elem[pai(i)]);
            i = pai(i);
        }
    }

    No tira_min() {
        if (tam <= 0) {
            cout << "Heap vazio!\n";
            return { -1, INF, nullptr };  // Retorna um nó inválido
        }
        if (tam == 1) {
            tam--;
            return elem[0];
        }

        // Guarda o nó de menor peso (raiz)
        No raiz = elem[0];
        elem[0] = elem[tam - 1];
        tam--;
        min_Heapfy(0);

        return raiz;
    }

    bool vazio() {
        return tam == 0;
    }
};

int main(){
    int quadras, ruas, eventos;
    int A, B, minutos;
    cin >> quadras >> ruas >> eventos;
	grafo Grafo(quadras);
    for(int i=0; i<ruas; i++){
        cin >> A >> B >> minutos;
        Grafo.addAresta(A, B, minutos);
    }
	for(int i=0; i<eventos; i++){
		int comando;
		cin >> comando;
		switch(comando){
			case 1:
				cin >> A >> B >> minutos;
				Grafo.atualizaPeso(A, B, minutos);
			break;
			case 2:
				cin >> A >> B;
				Grafo.Dijkstra(A, B);
			break;
		}
	}

    Grafo.freeGrafo();
    return 0;
}

No* grafo::criaNo(int v, int p){
	No* novoNo = nullptr;
	novoNo = new No;
	if(novoNo == nullptr){
		cout << "Erro de alocacao!!\n";
		exit(1);
	}
	novoNo->vertice = v;
	novoNo->proximo = nullptr;
	novoNo->peso = p;
	return novoNo;
}

void grafo::addAresta(int u, int v, int p) {
    // Adiciona v em u
    No* novoNo = criaNo(v, p);
    novoNo->proximo = listAdj[u];
    listAdj[u] = novoNo;

    /*
    // Adiciona u em v (grafo não-direcionado)
    No* novono = criaNo(u, p);
    novono->proximo = listAdj[v];
    listAdj[v] = novono;
    */
}


void grafo::printGrafo() {
    for (int i = 0; i < n_nos; i++) {
        No* temp = listAdj[i];
        cout << "Vertice " << i << ":";
        while (temp != nullptr) {
            cout << " -> " << temp->vertice << "(" << temp->peso << ")";
            temp = temp->proximo;
        }
        cout << "\n";
    }
}


void grafo::freeGrafo(){
	for(int i=0; i<n_nos; i++){
		No* temp = listAdj[i];
		while(temp != nullptr){
			No* prox = temp->proximo;
			delete temp;
			temp = prox;
		}
	}
	delete[] listAdj;
}

No* grafo::procura(int u, int v){
	No* temp = listAdj[u];

	while(temp != nullptr && temp->vertice != v)
		temp = temp->proximo;

	return temp;
}

void grafo::atualizaPeso(int origem, int destino, int nPeso){
	No* atualizar = procura(origem, destino);

	if(atualizar != nullptr){
		atualizar->peso = nPeso;
	}
    else{
        addAresta(origem, destino, nPeso);
    }
}

void grafo::Dijkstra(int origem, int destino) {
    int pesos[n_nos];
    int antecessor[n_nos];

    for (int i = 0; i < n_nos; i++) {
        pesos[i] = INF;
        antecessor[i] = -1;
    }

    pesos[origem] = 0;

    heap fila(n_nos);  // Inicializando o heap com capacidade para n_nos

    No noInicial;
    noInicial.vertice = origem;
    noInicial.peso = 0;
    fila.insert(noInicial);

    while (!fila.vazio()) {
        No u = fila.tira_min();  // Pega o vértice com menor peso
        int verticeU = u.vertice;
        int pesoU = u.peso;
        

        if (verticeU == destino) break;  // Se já alcançamos o destino, podemos sair

        No *temp = listAdj[verticeU];
        while (temp != nullptr) {
            int v = temp->vertice;
            int pesoAresta = temp->peso;
            int ref = pesos[verticeU] + pesoAresta;

            if (ref < pesos[v]) {
                pesos[v] = ref;
                antecessor[v] = verticeU;

                No novoNo;
                novoNo.vertice = v;
                novoNo.peso = ref;
                fila.insert(novoNo);  // Insere o vértice v com o novo peso
            }
            temp = temp->proximo;
        }
    }

    if (pesos[destino] == INF) {
        cout << "-1\n";  // Não há caminho possível
        return;
    } 
    
    cout << pesos[destino] << "\n";
}

