#include <iostream>
#include <string>

using namespace std;

int main(){
    int aberta = 0;
    int fechada = 0;
    bool bad = false;
    string frase;
    getline(cin, frase);
    int tam = frase.size();

    for(int i=0; i<tam; i++){
        if(frase[i] == '{'){
            aberta++;
        }
        if(frase[i] == '}'){
            fechada++;
        }
        if(fechada > aberta){
            bad = true;
        }
    }

    if(aberta == fechada && !bad)
        cout << "S" << endl;
    else
        cout << "N" << endl;
        
    return 0;
}