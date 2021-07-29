#include "No.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

No::No(int id) {
    this->id = id;
    this->peso = 0;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->prox_no = nullptr;
};

No::~No(){
    Aresta* prox_aresta = this->primeira_aresta;

    while(prox_aresta != nullptr){
        Aresta* aux_aresta = prox_aresta->getProxAresta();
        delete prox_aresta;
        prox_aresta = aux_aresta;
    }

    free(prox_aresta);
};

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

bool No::existeAresta(int id_alvo) {
    if(this->primeira_aresta != nullptr){
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta()){
            if(aux->getIdAlvo() == id_alvo){
                return true;
            }
        }
    }
    return false;
}

void No::inserirAresta(int id_alvo, float peso) {
    if(!existeAresta(id_alvo)) {
        if(this->primeira_aresta != nullptr) {
            Aresta* aresta = new Aresta(id_alvo, this->id, peso);
            this->ultima_aresta->setProxAresta(aresta);
            this->ultima_aresta = aresta;
        }else {
            this->primeira_aresta = new Aresta(id_alvo, this->id, peso);
            this->ultima_aresta = this->primeira_aresta;
        }
    }
}

void No::removerTodasArestas() {
    if(this->primeira_aresta != nullptr) {
        Aresta* prox_aresta = this->primeira_aresta;

        while(prox_aresta != nullptr){
            Aresta* aux_aresta = prox_aresta->getProxAresta();
            delete prox_aresta;
            prox_aresta = aux_aresta;
        }
    }
    this->primeira_aresta = this->ultima_aresta = nullptr;
}

int No::removerAresta(int id, bool direcionado, No* no_alvo){
    if(this->existeAresta(id)) {
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

Aresta* No::getArestaEntre(int id_alvo) {
    for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta()) {
        if(aux->getIdAlvo() == id_alvo) {
            return aux;
        }
    }
    return nullptr;
}

bool No::existeArestaEntre(int id_alvo) {
    for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta()) {
        if(aux->getIdAlvo() == id_alvo) {
            return true;
        }
    }
    return false;
}

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