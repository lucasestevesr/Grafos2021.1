#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

Grafo::Grafo(int ordem, bool direcionado, bool aresta_ponderado, bool no_ponderado) {
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->aresta_ponderado = aresta_ponderado;
    this->no_ponderado = no_ponderado;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->num_arestas = 0;

    for(int i = 0; i < ordem; i++){
        this->inserirNo(i);
    }
}

Grafo::~Grafo() {
    No* prox_no = this->primeiro_no;

    while (prox_no != nullptr) {
        prox_no->removerTodasArestas();
        No* aux_no = prox_no->getProxNo();
        delete prox_no;
        prox_no = aux_no;
    }
}

int Grafo::getOrdem() {
    return this->ordem;
}

int Grafo::getNumArestas() {
    return this->num_arestas;
}

bool Grafo::getDirecionado() {
    return this->direcionado;
}

bool Grafo::getArestaPonderado() {
    return this->aresta_ponderado;
}

bool Grafo::getNoPonderado() {
    return this->no_ponderado;
}

No* Grafo::getPrimeiroNo() {
    return this->primeiro_no;
}

No* Grafo::getUltimoNo() {
    return this->ultimo_no;
}

No* Grafo::getNo(int id) {
    if(this->primeiro_no != nullptr) {
        for (No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            if(no->getId() == id) {
                return no;
            }
        }
    }
    return NULL;
}

bool Grafo::existeNo(int id) {
    if(this->primeiro_no != nullptr) {
        for (No* no = this->primeiro_no; no != nullptr ; no = no->getProxNo()) {
            if(no->getId() == id) {
                return true;
            }
        }
    }
    return false;
}

void Grafo::inserirNo(int id) {
    No* no = new No(id);

    if(this->primeiro_no == nullptr){
        this->primeiro_no = no;
        this->ultimo_no = no;
    }else{
        this->ultimo_no->setProxNo(no);
        this->ultimo_no = no;
    }
}

void Grafo::removerNo(int id) {
    if(existeNo(id)) {
        No* node = this->getPrimeiroNo();
        No* temp = nullptr;

        while(node->getId() != id) {
            temp = node;
            node = node->getProxNo();
        }

        if(temp != nullptr)
            temp->setProxNo(node->getProxNo());
        else
            this->primeiro_no = node->getProxNo();

        if(node == this->ultimo_no)
            this->ultimo_no = temp;

        if(node->getProxNo() == this->ultimo_no)
            this->ultimo_no = node->getProxNo();

        No* aux = this->getPrimeiroNo();

        while(aux != nullptr) {
            aux->removerAresta(node->getId(), this->direcionado, node);
            aux = aux->getProxNo();
        }

        delete node;
        this->ordem--;
    }
}

void Grafo::inserirAresta(int id, int id_alvo, float peso) {
    No* no_origem = this->getNo(id);
    no_origem->inserirAresta(id_alvo, peso);
    if(!this->direcionado) {
        No* no_alvo = this->getNo(id_alvo);
        no_alvo->inserirAresta(id, peso);
    }
}

void Grafo::imprimir() {
    cout << "Funcao imprimir Grafo: " << endl;
    if(this->primeiro_no != nullptr) {
        for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            cout << "No: "  << no->getId() << endl;
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
                if(!aresta->getDirecionado() || this->direcionado){
                    cout << no->getId()  << " " << aresta->getIdAlvo() << endl;
                }
            }
        }
    }else {
        cout << "Grafo vazio" << endl;
    }
}

void Grafo::salvarDot() {
    std::ofstream saida("saida.dot");

    if(!saida.is_open()){
        std::cerr << "Erro na abertura do arquivo" << std::endl;
    }

    if(this->primeiro_no != nullptr) {
        if(this->direcionado) {
            saida << "digraph {" << std::endl;
        }else {
            saida << "strict graph {" << std::endl;
        }
        for(No* no = this->primeiro_no; no != nullptr; no = no->getProxNo()) {
            for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
                if(this->direcionado) {
                    saida << "\t" << no->getId()  << " -> " << aresta->getIdAlvo() << ";" << std::endl;
                }else {
                    saida << "\t" << no->getId()  << " -- " << aresta->getIdAlvo() << ";" << std::endl;
                }
            }
        }
        saida << "}" << std::endl;
    }else {
        saida << "Erro: Grafo vazio" << std::endl;
    }
}

// Funcionalidades do trabalho
void Grafo::fechoTD(int id) {
    if(this->direcionado) {

    }else {
        cout << "Erro: O grafo nao e direcionado!" << endl;
    }
}

void Grafo::buscaProf(int id) {
    list<int> listaVisitados;
    listaVisitados.push_back(id);

    auxBuscaProf(&listaVisitados, id);

    Grafo* grafo = new Grafo(listaVisitados.size(), 0, 0, 0);

    // imprimindo lista
    list<int>::iterator it;
    cout << "imprimindo lista" << endl;
    while(!listaVisitados.empty()) {
        grafo->inserirNo(listaVisitados.back());
//        cout << listaVisitados.back() << endl;
        listaVisitados.pop_back();
    }
    grafo->salvarDot();
    cout << "fim imprimindo lista" << endl;
}

void Grafo::auxBuscaProf(list<int>* listaVisitados, int id) {
    No* no = this->getNo(id);

    for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()) {
        if(!auxBuscaLista(listaVisitados, aresta->getIdAlvo())){
            listaVisitados->push_back(aresta->getIdAlvo());
            auxBuscaProf(listaVisitados, aresta->getIdAlvo());
        }
    }
}

bool Grafo::auxBuscaLista(list<int>* listaVisitados, int id) {
    list<int>::iterator it;
    for(it = listaVisitados->begin(); it!=listaVisitados->end();it++){
        if(*it == id) {
            return true;
        }
    }
    return false;
}