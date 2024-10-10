#include <iostream>
#include <string>

using namespace std;

typedef struct no{
    string nome;
    int pont;

    no *pai;
    no *esquerda;
    no *direita;
} No;

class Arvore {
private:
	No* raiz;

public:
	Arvore(No* no = NULL) {
		raiz = no;
	}
    No* busca_Arvore(No* no, int id);
	No* minimo_Arvore(No* no);
	No* maximo_Arvore(No* no);
	No* sucessor(No* no);
	No* antecessor(No* no);
	void inserir(No* add);
    void freeArvore();
};

int main(){
    int n_comand;
    string comando;
    Arvore tree;

    cin >> n_comand;
    for(int i=0; i<n_comand; i++){
        cin >> comando;
        if(comando == "ADD"){
            No* add = NULL;
            add = new No;
            if(add == NULL){
                cout << "Erro de alocacao \n";
                exit(1);
            }
            add->direita = add->esquerda = add->pai = NULL;
            cin >> add->nome >> add->pont;
            tree.inserir(add);
        }
        if(comando == "PROX"){
            int pont;
            No *antes = NULL, *depois = NULL, *busca = NULL, *ref = NULL;
            cin >> pont;

           	ref = new No;
           	if(ref == NULL){
           	    cout << "Erro de alocacao \n";
           	    exit(1);
           	}
           	ref->pont = -1;
           	busca = tree.busca_Arvore(ref, pont);
			antes = tree.antecessor(busca);
			depois = tree.sucessor(busca);
			delete ref;
			if(antes == NULL && depois == NULL){
				cout << "Apenas " << busca->nome << " existe no sistema...\n";
			}
			else if(depois != NULL && antes == NULL){
				cout << busca->nome << " e o menor! e logo apos vem " << depois->nome << "\n";
			}
			else if(antes != NULL && depois == NULL){
				cout << busca->nome << " e o maior! e logo atras vem " << antes->nome << "\n";
			}
			else{
				cout << busca->nome << " vem apos " << antes->nome << " e antes de " << depois->nome << "\n";
			}
        }
    }

    tree.freeArvore();

    return 0;
}

No* Arvore::busca_Arvore(No* no, int k) {
    if(no->pont == -1){
        no = raiz;
    }
	if (no == NULL || k == no->pont) {
		return no;
	}
	else if (no->pont > k) {
		return busca_Arvore(no->esquerda, k);
	}
	else {
		return busca_Arvore(no->direita, k);
	}
}

No* Arvore::minimo_Arvore(No* no) {
	while (no->esquerda != NULL) {
		no = no->esquerda;
	}
	return no;
}

No* Arvore::maximo_Arvore(No* no) {
	while (no->direita != NULL) {
		no = no->direita;
	}
	return no;
}

No* Arvore::sucessor(No* no) {
	if (no->direita != NULL)
		return minimo_Arvore(no->direita);
	else {
		No* aux = no->pai;
		while (aux != NULL && no == aux->direita) {
			no = aux;
			aux = aux->pai;
		}
		return aux;
	}
}

No* Arvore::antecessor(No* no) {
	if (no->esquerda != NULL)
		return maximo_Arvore(no->esquerda);
	else {
		No* aux = no->pai;
		while (aux != NULL && no == aux->esquerda) {
			no = aux;
			aux = aux->pai;
		}
		return aux;
	}
}

void Arvore::inserir(No *add) {
    No *x = raiz, *y = NULL;
    while (x != nullptr) {
        y = x;
        if (add->pont < x->pont) {
            x = x->esquerda;
        } else if (add->pont > x->pont) {
            x = x->direita;
        } 
        else {
            cout << y->nome << " ja esta no sistema.\n";
            delete add;
            return;
        }
    }
    add->pai = y;
    if (y == NULL) {
        raiz = add; // Arvore era vazia
    } 
    else if (add->pont < y->pont) {
        y->esquerda = add;
    } 
    else {
        y->direita = add;
    }
    cout << add->nome << " inserido com sucesso!\n";
}

void Arvore::freeArvore() {
    if (raiz == NULL)
        return;

    No* nos = raiz;
    No* parent = NULL;

    while (nos != NULL) {
        if (nos->esquerda == NULL) {
            // Se não há filho esquerdo, deletamos o nó atual e movemos para o direito
            No* temp = nos->direita;
            delete nos;
            nos = temp;
        } else {
            // Encontramos o predecessor in-order do nó atual
            No* predecessor = nos->esquerda;
            while (predecessor->direita != NULL && predecessor->direita != nos) {
                predecessor = predecessor->direita;
            }

            if (predecessor->direita == NULL) {
                // Estabelecemos um link temporário do predecessor para nos
                predecessor->direita = nos;
                nos = nos->esquerda;
            } 
            else {
                // Removemos o link temporário e deletamos o nó atual
                predecessor->direita = NULL;
                No* temp = nos->direita;
                delete nos;
                nos = temp;
            }
        }
    }
    raiz = NULL; // Certificamos que a raiz é NULL após deletar todos os nós
}