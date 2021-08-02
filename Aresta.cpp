#include "Aresta.h"
#include <iostream>

using namespace std;

// Inicio construtor aresta
Aresta::Aresta(int id_alvo, int id_origem, float peso) {
    this->id_alvo = id_alvo;
    this->id_origem = id_origem;
    this->peso = peso;
    this->direcionado = false;
    this->prox_aresta = nullptr;
}
// Fim construtor aresta

// Inicio destrutor aresta
Aresta::~Aresta() {
    if(this->prox_aresta != nullptr) {
//        delete this->prox_aresta;
        this->prox_aresta = nullptr;
    }
}
// Fim destrutor aresta

// Inicio getters e setters
int Aresta::getIdAlvo() {
    return this->id_alvo;
}

int Aresta::getIdOrigem() {
    return this->id_alvo;
}

float Aresta::getPeso() {
    return this->peso;
}

bool Aresta::getDirecionado() {
    return this->direcionado;
}

Aresta* Aresta::getProxAresta(){
    return this->prox_aresta;
}

void Aresta::setPeso(float peso) {
    this->peso = peso;
}

void Aresta::setDirecionado(bool direcionado) {
    this->direcionado = direcionado;
}

void Aresta::setProxAresta(Aresta *prox) {
    this->prox_aresta = prox;
}
// Fim getters e setters