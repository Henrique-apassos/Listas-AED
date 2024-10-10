#include <iostream>
#include <string>

using namespace std;

string PegaMaior(string maiorLista, string lista);

int main(){
    string lista, maiorLista;

    while(getline(cin, lista)){
        maiorLista = PegaMaior(maiorLista, lista);
    }

    cout << maiorLista << endl;
    return 0;
}

string PegaMaior(string maiorLista, string lista){
    if(lista.size() > maiorLista.size()){
        maiorLista = lista;
    }
    return maiorLista;
}