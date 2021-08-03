#include "No.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

// Inicio construtor No
No::No(int id) {
    this->id = id;
    this->peso = 0;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->prox_no = nullptr;
};
// Fim construtor No

// Inicio destrutor No
No::~No(){
    Aresta* prox_aresta = this->primeira_aresta;

    // Removendo todas arestas do No
    while(prox_aresta != nullptr){
        Aresta* aux_aresta = prox_aresta->getProxAresta();
        delete prox_aresta;
        prox_aresta = aux_aresta;
    }
};
// Fim destrutor No

// Inicio getters e setters
int No::getId() {
    return this->id;
}

float No::getPeso() {
    return this->peso;
}

int No::getGrauEntrada() {
    return this->grau_entrada;
}

int No::getGrauSaida() {
    return this->grau_saida;
}

Aresta* No::getPrimeiraAresta() {
    return this->primeira_aresta;
}

Aresta* No::getUltimaAresta() {
    return this->ultima_aresta;
}

No* No::getProxNo() {
    return this->prox_no;
}

void No::setPeso(float peso) {
    this->peso = peso;
}

void No::setProxNo(No *prox_no) {
    this->prox_no = prox_no;
}
// Fim getters e setters

// Inicio funcao inserir aresta
void No::inserirAresta(int id_alvo, float peso) {
    // Verifica se a aresta ja nao existe
    if(!existeArestaEntre(id_alvo)) {
        // Verifica se existe outras arestas para este No
        if(this->primeira_aresta != nullptr) {
            // Cria a nova aresta
            Aresta* aresta = new Aresta(id_alvo, this->id, peso);
            // Nova aresta e definida como proxima da antiga ultima
            this->ultima_aresta->setProxAresta(aresta);
            // Ultima aresta recebe a nova aresta
            this->ultima_aresta = aresta;
        }else {
            // Se for a primeira aresta desse No
            this->primeira_aresta = new Aresta(id_alvo, this->id, peso);
            // Cria a aresta e coloca como primeira e ultima
            this->ultima_aresta = this->primeira_aresta;
        }
    }
}
// Fim funcao inserir aresta

// Inicio funcao remover todas arestas
void No::removerTodasArestas() {
    // Verifica se existe aresta para este No
    if(this->primeira_aresta != nullptr) {
        // Cria variavel aux na primeira aresta
        Aresta* prox_aresta = this->primeira_aresta;

        // Enquanto a prox aresta for diferente de null, ou seja, percorre todas
        while(prox_aresta != nullptr){
            // Cria uma aresta aux para nao perder a referencia de onde esta
            Aresta* aux_aresta = prox_aresta->getProxAresta();
            // Apaga a aresta atual
            delete prox_aresta;
            // Alimenta o loop com o aresta auxiliar
            prox_aresta = aux_aresta;
        }
    }
    // Define primeira e ultima aresta como null
    this->primeira_aresta = this->ultima_aresta = nullptr;
}
// Fim funcao remover todas arestas

// Inicio funcao remover aresta
int No::removerAresta(int id, bool direcionado, No* no_alvo){
    if(this->existeArestaEntre(id)) {
        Aresta* aux_aresta = this->primeira_aresta;
        Aresta* ante_aresta = nullptr;

        while(aux_aresta->getIdAlvo() != id) {
            ante_aresta = aux_aresta;
            aux_aresta = aux_aresta->getProxAresta();
        }

        if(ante_aresta != nullptr) {
            ante_aresta->setProxAresta(aux_aresta->getProxAresta());
        }else {
            this->primeira_aresta = aux_aresta->getProxAresta();
        }

        if(aux_aresta == this->ultima_aresta) {
            this->ultima_aresta = ante_aresta;
        }

        if(aux_aresta->getProxAresta() == this->ultima_aresta) {
            this->ultima_aresta = aux_aresta->getProxAresta();
        }

        delete aux_aresta;

        if(direcionado) {
            this->diminuirGrauSaida();
            no_alvo->diminuirGrauEntrada();
        }else {
            this->diminuirGrauSaida();
            this->aumentarGrauEntrada();
            no_alvo->removerAresta(this->id, 1, this);
        }

        return 1;
    }

    return 0;
}
// Fim funcao remover aresta

// Inicio funcao pegar aresta entre No atual e id alvo
Aresta* No::getArestaEntre(int id_alvo) {
    // Verifica se o No tem arestas
    if(this->primeira_aresta != nullptr){
        // Percorre as aresta do No
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta()) {
            // Se alguma de suas aresta ja fizer ligacao com o id parametro
            if(aux->getIdAlvo() == id_alvo) {
                // Retorna a Aresta atual do loop, ou seja, a aresta que liga os Nos
                return aux;
            }
        }
    }
    // Se chegou ate aqui e porque nao existe aresta
    return nullptr;
}
// Fim funcao pegar aresta entre No atual e id alvo

// Inicio funcao de verificar se existe aresta entre o No atual com o id parametro
bool No::existeArestaEntre(int id_alvo) {
    // Verifica se o No tem arestas
    if(this->primeira_aresta != nullptr){
        // Percorre as aresta do No
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta()){
            // Se alguma de suas aresta ja fizer ligacao com o id parametro
            if(aux->getIdAlvo() == id_alvo){
                // Retorna que ja existe aresta
                return true;
            }
        }
    }
    // Se chegou ate aqui e porque nao existe aresta
    return false;
}
// Fim funcao de verificar se existe aresta entre o No atual com o id parametro

// Inicio funcoes aumentar ou diminuir grau de entrada ou saida
void No::aumentarGrauEntrada() {
    this->grau_entrada++;
}

void No::diminuirGrauEntrada() {
    this->grau_entrada--;
}

void No::aumentarGrauSaida() {
    this->grau_saida++;
}

void No::diminuirGrauSaida() {
    this->grau_saida--;
}
// Fim funcoes aumentar ou diminuir grau de entrada ou saida