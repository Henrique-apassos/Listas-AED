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
	void Prim();
	void freeGrafo();
};

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
	grafo Grafo(m);
	int inicio, destino, peso;

	for(int i=0; i<n; i++){
		cin >> inicio >> destino >> peso;
		Grafo.addAresta(inicio, destino, peso);
	}

	Grafo.Prim();
    
	Grafo.freeGrafo();
    return 0;
}

No* grafo::criaNo(int v, int p){
	No* novoNo = nullptr;
	novoNo = (No*)malloc(sizeof(No));
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

    // Adiciona u em v (grafo não-direcionado)
    No* novono = criaNo(u, p);
    novono->proximo = listAdj[v];
    listAdj[v] = novono;
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

void grafo::Prim() {
    int pesos[n_nos];
    int arvore[n_nos];
    bool marcado[n_nos];
	int peso_total = 0;

    for (int i = 0; i < n_nos; i++) {
		
        pesos[i] = INF;
        arvore[i] = -1;
        marcado[i] = false;
    }

	pesos[0] = 0;

	for(int arestas=0; arestas < n_nos; arestas++){
		int u = -1;
		int pesoMin = INF;

		for(int v=0; v<n_nos; v++){
			if(!marcado[v] && pesos[v] < pesoMin){
				pesoMin = pesos[v];
				u = v;
			}
		}

		if(u == -1){
			cout << "Grafo desconexo\n";
			return;
		}
		
		marcado[u] = true;

		No* temp = listAdj[u];
		while(temp != nullptr){
			int v = temp->vertice;
			int ref = temp->peso;

			if(!marcado[v] && ref < pesos[v]){
				pesos[v] = ref;
				arvore[v] = u;
			}
			temp = temp->proximo;
		}
	}

	for(int i=1; i<n_nos; i++){
		peso_total += pesos[i];
	}

	cout << peso_total << "\n";
}