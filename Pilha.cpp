#include <iostream>
#include <cstdlib>
#include "Pilha.h"

using namespace std;

// construtor
Pilha::Pilha(int tamanho)
{
    vetorInteiro = new int[tamanho];
}

// destrutor
Pilha::~Pilha()
{
    delete [] vetorInteiro;
}

void Pilha::empilha(int val)
{
    vetorInteiro[tam] = val;
    tam++;
}

int Pilha::desempilha()
{

    if(tam != 0)
        tam--;
    else
    {
        cout << "ERRO: Pilha vazia!" << endl;
        exit(1);
    }
}

int Pilha::getTopo()
{
    if(tam != 0)
        return vetorInteiro[tam];
    else
    {
        cout << "Pilha vazia!" << endl;
        exit(1);
    }
}

bool Pilha::vazia()
{
    if(tam == 0)
        return(true);
    else
        return(false);
}

int Pilha::tamanho(){
    return tam;
}

bool Pilha::contemNaPilha(int val){
    for (int i = 0; i < tam; i++) {
        if(vetorInteiro[i]==val) return true;
    }
    return false;
}
