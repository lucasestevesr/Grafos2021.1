#include "Aresta.h"
#include <iostream>

using namespace std;

// Inicio construtor aresta
Aresta::Aresta(int id_origem, int id_alvo, int id_aux_origem, int id_aux_alvo, float peso, bool aux) {
    this->id_origem = id_origem;
    this->id_alvo = id_alvo;
    this->id_aux_origem = id_aux_origem;
    this->id_aux_alvo = id_aux_alvo;
    this->aux = aux;
    this->peso = peso;
    this->prox_aresta = nullptr;
}
// Fim construtor aresta

// Inicio destrutor aresta
Aresta::~Aresta() {
    // Codigo abaixo deleta todas arestas
    /* if(this->prox_aresta != nullptr) {
        delete this->prox_aresta;
        this->prox_aresta = nullptr;
    } */
    this->prox_aresta = nullptr;
}
// Fim destrutor aresta

// Inicio getters e setters
int Aresta::getIdOrigem() {
    return this->id_origem;
}

int Aresta::getIdAlvo() {
    return this->id_alvo;
}

int Aresta::getIdAuxOrigem() {
    return this->id_aux_origem;
}

int Aresta::getIdAuxAlvo() {
    return this->id_aux_alvo;
}

bool Aresta::getAux() {
    return this->aux;
}

float Aresta::getPeso() {
    return this->peso;
}

Aresta* Aresta::getProxAresta(){
    return this->prox_aresta;
}

void Aresta::setPeso(float peso) {
    this->peso = peso;
}

void Aresta::setProxAresta(Aresta *prox) {
    this->prox_aresta = prox;
}
// Fim getters e setters