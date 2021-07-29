#ifndef TEORIADOSGRAFOS_PILHAENCAD_H
#define TEORIADOSGRAFOS_PILHAENCAD_H

#include "No.h"
using namespace std;

class Pilha
{
private:

    int *vetorInteiro;                /// ponteiro p/ o No do topo
    int tam=0;

public:
    Pilha(int tamanho);
    ~Pilha();
    int getTopo();           /// retorna valor do No do topo
    void empilha(int val);   /// insere No no topo
    int desempilha();        /// elimina No do topo
    bool vazia();            /// verifica se est� vazia
    bool contemNaPilha(int val);
    int tamanho();
};
#endif //TEORIADOSGRAFOS_PILHAENCAD_H
